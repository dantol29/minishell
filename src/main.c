/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:58:49 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/21 17:30:03 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrl_c(int signum)
{
	(void)signum;
	write(1, "", 1);
}

void	launch_exec(char *line, t_shell *shell, char **envp)
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

char	*find_command(char *line)
{
	int		i;
	int		count_quotes;
	int		count_letters;
	char	*new_cmd;

	i = 0;
	count_quotes = 0;
	count_letters = 0;
	while (line[i] && line[i] != ' ')
	{
		if (line[i] == '\"')
			count_quotes += 1;
		else
			count_letters += 1;
		i++;
	}
	if (count_quotes % 2 != 0)
	{
		printf("minishell: error while looking for matching quote\n");
		return (NULL);
	}
	new_cmd = malloc(sizeof(char) * (count_letters + 2));
	if (!new_cmd)
		return (NULL);
	i = 0;
	count_letters = 0;
	while (line[i] && line[i] != ' ')
	{
		if (line[i] != '\"')
			new_cmd[count_letters++] = line[i];
		i++;
	}
	if (line[i] == ' ')
		new_cmd[count_letters++] = ' ';
	new_cmd[count_letters] = '\0';
	return (new_cmd);
}


void	call_functions(char *line, t_shell *shell, char **envp)
{
	char	*command;

	line = ft_strtrim(line, " ");
	command = find_command(line);
	if (command == NULL || is_empty_line(line))
		return ;
	if (check_pipe_symbol(line))
		call_pipe_function();
	else if (ft_strcmp("echo ", command) == 0 || ft_strcmp("echo", command) == 0)
		check_echo_line(line, shell->env);
	else if (access(ft_strjoin("/usr/bin/", command), 0) == 0)
		launch_exec(line, shell, envp);
	else
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
		call_functions(line, &shell, envp);
		add_history(line);
		printf("minishell");
		line = readline(" $ "); // read user input
	}
	printf("exit\n");
}