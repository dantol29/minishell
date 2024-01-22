/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:58:49 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/22 15:20:23 by akurmyza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrl_c(int signum)
{
	(void)signum;
	write(1, "", 1);
}

int	launch_exec(char *line, t_shell *shell, char **envp)
{
	shell->command = ft_split(line, ' ');
	shell->cmd_path = ft_strjoin("/bin/", shell->command[0]);
	if (access(shell->cmd_path, 0) == 0)
	{
		shell->pid = fork();
		if (shell->pid == 0)
			execve(shell->cmd_path, shell->command, envp);
		waitpid(shell->pid, NULL, 0);
	}
	else if (access(shell->command[0], 0) == 0)
	{
		shell->pid = fork();
		if (shell->pid == 0)
			execve(shell->command[0], shell->command, envp);
		waitpid(shell->pid, NULL, 0);
	}
	else
	{
		printf("minishell: command not found: %s\n", shell->command[0]);
		return (FALSE);
	}
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
	printf("minishell");
	line = readline("$");
	while (line != NULL)
	{
		launch_commands(line, &shell, envp);
		add_history(line);
		printf("minishell");
		line = readline(" $ ");
	}
	printf("exit\n");
}
