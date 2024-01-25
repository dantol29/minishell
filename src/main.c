/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:58:49 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/25 12:40:53 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ctrl_c(int signum)
{
    (void)signum;
	rl_replace_line("\0", 0);
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

int	launch_exec(char *line, char **envp)
{
	char	**command;
	char	*cmd_path;
	int		pid;

	command = ft_split(line, ' ');
	cmd_path = ft_strjoin("/bin/", command[0]);
	if (access(cmd_path, 0) == 0)
	{
		pid = fork();
		if (pid == 0)
			execve(cmd_path, command, envp);
		waitpid(pid, NULL, 0);
	}
	else if (access(command[0], 0) == 0)
	{
		pid = fork();
		if (pid == 0)
			execve(command[0], command, envp);
		waitpid(pid, NULL, 0);
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
		line = readline("minishell$ ");
	}
	free(line);
	printf("exit\n");
}
