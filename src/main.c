/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:58:49 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/18 12:16:30 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrl_c(int signum)
{
	(void)signum;
	write(1, "\n", 1);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell shell;
	char	*line;

	(void)argv;
	(void)argc;
	signal(SIGINT, ctrl_c);
	shell.username = getenv("USER"); // get env variable user
	getcwd(shell.work_dir, sizeof(shell.work_dir)); // getcwd - get the current working directory
	printf("%s@minishell %s", shell.username, shell.work_dir);
	line = readline(" $ "); // read user input
	while (line != NULL)
	{
		shell.command = ft_split(line, ' '); // store entered command (use ft_split for flags)
		shell.cmd_path = ft_strjoin("/usr/bin/", shell.command[0]);
		if (access(shell.cmd_path, 0) == 0) 
		{
			shell.pid = fork();
			if (shell.pid == 0)
				execve(shell.cmd_path, shell.command, envp); // execute command (command path, command with flags, env variables)
			waitpid(shell.pid, NULL, 0);
		}
		else
			printf("minishell: command not found: %s\n", shell.command[0]);
		printf("%s@minishell %s", shell.username, shell.work_dir);
		line = readline(" $ "); // read user input
	}
	printf("exit\n");
}