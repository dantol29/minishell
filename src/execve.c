/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:38:13 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/16 12:46:36 by dtolmaco         ###   ########.fr       */
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
		execve(cmd_path, flags, shell->current_envp);
	waitpid(pid, &shell->exit_code, 0);
	shell->exit_code /= 256;
	free(cmd_path);
	free_double_array(flags);
	if (shell->is_pipe == TRUE)
		exit(shell->exit_code);
	return (TRUE);
}

// void	child_ctrl_c(int signum)
// {
// 	(void)signum;
// 	g_ctrl_c_status = 130;
// 	//write(1, "\n", 1);
// 	//rl_on_new_line();
// 	//rl_replace_line("", 0);
// 	//rl_redisplay();
// }