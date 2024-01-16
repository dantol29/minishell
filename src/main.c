/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:58:49 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/16 17:03:42 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_path(char **splitted_path, char *command)
{
	char	*tmp;
	char	*cmd;

	while (*splitted_path)
	{
		tmp = ft_strjoin(*splitted_path, "/");
		cmd = ft_strjoin(tmp, command);
		free(tmp);
		if (access(cmd, 0) == 0) // checks for the existence of the file or directory
			return(cmd);
		free(cmd);
		splitted_path++;
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell shell;
	char	cwd[1024];
	char	*line;
	char	*username;
	char	*path;

	(void)argv;
	(void)argc;
	username = getenv("USER"); // get env variable user
	path = getenv("PATH"); // get env variable path
	getcwd(cwd, sizeof(cwd)); // getcwd - get the current working directory
	while (1)
	{
		printf("%s@minishell %s",username, cwd);
		line = readline(" $ "); // read user input
		shell.command = ft_split(line, ' '); // store entered command (use ft_split for flags)
		shell.cmd_path = get_path(ft_split(path, ':'), shell.command[0]);
		if (shell.cmd_path == NULL)
			printf("Command does not exist\n");
		else
			execve(shell.cmd_path, shell.command, envp); // execute command (command path, command with flags, env variables)
	}
}