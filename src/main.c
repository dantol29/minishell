/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:58:49 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/21 12:05:43 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrl_c(int signum)
{
	(void)signum;
}

void	parsing(char *line, t_shell *shell, char **envp)
{
	shell->command = ft_split(line, ' '); // store entered command (use ft_split for flags)
	shell->cmd_path = ft_strjoin("/usr/bin/", shell->command[0]); // if commands whtout path (ls, pwd)
	if (access(shell->cmd_path, 0) == 0)
	{
		shell->pid = fork();
		if (shell->pid == 0)
			execve(shell->cmd_path, shell->command, envp); // execute command (command path, command with flags, env variables)
		waitpid(shell->pid, NULL, 0);
	}
	else if (access(shell->command[0], 0) == 0) // if absolute path (/bin/ls, ../bin/ls)
	{
		shell->pid = fork();
		if (shell->pid == 0)
			execve(shell->command[0], shell->command, envp); // execute command (command path, command with flags, env variables)
		waitpid(shell->pid, NULL, 0);
	}
	else
		printf("minishell: command not found: %s\n", shell->command[0]);
}

int check_pipe_symbol(char *line)
{
	int i;

	i = 0;
	while(line[i])
	{
		if (line[i] == '|')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void call_pipe_function(void)
{
	return ;
}

void	call_functions(char *line, t_shell *shell)
{
	if (check_pipe_symbol(line))
		call_pipe_function();
	else if (ft_strncmp("echo ", line, 5) == 0)
	{
		check_input(line + 5, shell->env);
			//parsing(line, &shell, envp);	
	}
	else if (access("gfgfgffg", 0) != 0)
		printf("command not found\n");			//TODO:  add print command, before "command not found" (perror)
}



int	main(int argc, char **argv, char **envp)
{
	t_shell shell;
	char	*line;

	(void)argv;
	(void)argc;
	signal(SIGINT, ctrl_c);
	save_envp(&shell, envp);
	printf("minishell");
	line = readline(" $ "); // read user input
	while (line != NULL)
	{
		call_functions(line, &shell);
		add_history(line);
		printf("minishell");
		line = readline(" $ "); // read user input
	}
	printf("exit\n");
}