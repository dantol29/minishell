/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:58:49 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/26 14:41:18 by akurmyza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_ctrl_c_status;

void	ctrl_c(int signum)
{
	(void)signum;
	g_ctrl_c_status = 130;
	rl_replace_line("\0", 0);
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

int	launch_exec(char *line, char *cmd, char **envp, t_shell *shell)
{
	char	**flags;
	char	*cmd_path;
	int		pid;

	line = skip_command_name(line);
	flags = ft_split(ft_strjoin(ft_strjoin(cmd, " "), find_command(line)), ' ');
	cmd_path = ft_strjoin("/bin/", cmd);
	if (access(cmd_path, 0) == 0)
	{
		pid = fork();
		if (pid == 0)
			execve(cmd_path, flags, envp);
		waitpid(pid, &shell->exit_code, 0);
	}
	else if (access(cmd, 0) == 0)
	{
		pid = fork();
		if (pid == 0)
			execve(cmd, flags, envp);
		waitpid(pid, &shell->exit_code, 0);
	}
	else
		return (FALSE);
	return (TRUE);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*line;

	(void)argv;
	(void)argc;
	shell.exit_code = 0;
	g_ctrl_c_status = 0;
	signal(SIGINT, ctrl_c);
	save_envp(&shell, envp);
	line = readline("minishell$ ");
	while (line != NULL)
	{
		line = ft_strtrim(line, " ");
		line = split_pipes(line);
		if (line)
		{
			launch_commands(line, &shell, envp);
			add_history(line);
		}
		g_ctrl_c_status = 0;
		line = readline("minishell$ ");
	}
	free(line);
	printf("exit\n");
}
