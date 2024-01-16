/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:58:49 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/16 16:20:35 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_path(char **envp)
{
	while ((ft_strncmp(*envp, "PATH", 4)) != 0)
		envp++;
	printf("Env path: %s\n", *envp + 5);
	return (*envp + 5);
}

char	*get_path(char **splitted_path, char *command)
{
	char	*tmp;
	char	*cmd;

	while (*splitted_path)
	{
		tmp = ft_strjoin(*splitted_path, "/");
		cmd = ft_strjoin(tmp, command);
		free(tmp);
		if (access(cmd, 0) == 0)
			return(cmd);
		free(cmd);
		splitted_path++;
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell shell;
	(void)argv;
	(void)argc;
	// check if shell is running in interactive mode
	if (isatty(STDIN_FILENO))
	{
		char	cwd[1024];
		char	*line;
		// getcwd - get the current working directory
		getcwd(cwd, sizeof(cwd));
		printf("%s$", cwd);
		line = readline("Enter a command: ");
		printf("You entered: %s\n", line);
		shell.cmd_path = get_path(ft_split(find_path(envp), ':'), line);
		printf("command path: %s\n", shell.cmd_path);
	}
}