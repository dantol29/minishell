/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:38:13 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/18 15:04:52 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	**execve_flags(char *line, char *cmd, t_shell *shell)
{
	char	**flags;
	int		flag_count;
	int		i;

	line = skip_command_name(line);
	flag_count = count_flags(line);
	flags = malloc(sizeof(char *) * (flag_count + 2));
	flags[0] = ft_strdup(cmd);
	i = 1;
	while (i <= flag_count)
	{
		flags[i] = find_command(line);
		line = skip_command_name(line);
		if (ft_strcmp(flags[i], "$?") && !ft_strcmp(cmd, "awk"))
			flags[i] = ft_itoa(130);
		else if (!ft_strcmp(cmd, "awk"))
			flags[i] = change_env_var(flags[i], shell);
		i++;
	}
	flags[flag_count + 1] = NULL;
	return (flags);
}

static void	sigquit_handler(int signum)
{
	(void)signum;
	g_ctrl_c_status = 130;
	exit(EXIT_SUCCESS);
}

static void	child(char *cmd_path, char **flags, t_shell *shell)
{
	signal(SIGQUIT, sigquit_handler);
	execve(cmd_path, flags, shell->current_envp);
}

int	launch_exec(char *line, char *cmd, t_shell *shell)
{
	char	**flags;
	char	*cmd_path;
	int		pid;

	update_envp(shell);
	flags = execve_flags(line, cmd, shell);
	cmd_path = get_executable_path(shell, cmd);
	if (!cmd_path)
	{
		free_double_array(flags);
		return (FALSE);
	}
	pid = fork();
	if (pid == 0)
		child(cmd_path, flags, shell);
	waitpid(pid, &shell->exit_code, 0);
	if (shell->exit_code != 131)
		shell->exit_code /= 256;
	free(cmd_path);
	free_double_array(flags);
	if (shell->is_pipe == TRUE)
		exit(shell->exit_code);
	return (TRUE);
}
