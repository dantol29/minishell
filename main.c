/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:58:49 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/16 14:35:18 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char **argv, char **envp)
{
	// check if shell is running in interactive mode
	if (isatty(STDIN_FILENO))
	{
		char	cwd[1024];
		char	*line;
		// getcwd - get the current working directory
		getcwd(cwd, sizeof(cwd));
		printf("%s$", cwd);
		line = readline("~");
		printf("You entered: %s\n", line);
	}
}