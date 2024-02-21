/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:14:45 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/21 21:11:50 by akurmyza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	split_pipes(char *line, char **substrings)
{
	int		i;
	int		j;
	int		start;
	char	*tmp;

	i = 0;
	j = 0;
	start = i;
	while (line[i])
	{
		if (line[i + 1] == '\0' || \
		(line[i] == '|' && !is_quote(line[i - 1]) && !is_quote(line[i + 1])))
		{
			if (line[i + 1] == '\0')
				tmp = ft_substr(line, start, i - start + 1);
			else
				tmp = ft_substr(line, start, i - start);
			substrings[j++] = ft_strtrim(tmp, " ");
			free(tmp);
			start = i + 1;
		}
		i++;
	}
	return (j);
}

static void	exit_pipe(char *substring, int fd, t_shell *shell)
{
	launch_commands(substring, shell);
	if (fd != 0)
		close(fd);
	exit(EXIT_SUCCESS);
}

static void	pipe_loop(char **substrings, int *tube, int num_cmd, t_shell *shell)
{
	int		pid;
	int		i;
	int		current_pipe;
	int		*fd;

	current_pipe = 0;
	fd = heredoc_in_pipe(substrings, num_cmd, shell);
	i = -1;
	while (++i < num_cmd)
	{
		pid = fork();
		if (pid == 0)
		{
			dup_output(tube, current_pipe, num_cmd, i);
			if (fd[i] != 0)
				dup2(fd[i], 0);
			else if (i != 0)
				dup2(tube[current_pipe - 2], 0);
			while (pid < 2 * (num_cmd))
				close(tube[pid++]);
			exit_pipe(substrings[i], fd[i], shell);
		}
		current_pipe += 2;
	}
	free(fd);
}

static void	launch_pipes(char **substrings, t_shell *shell, int num_commands)
{
	int		*tube;
	int		i;
	signal(SIGINT, ctrl_c_child_process);
	tube = malloc(sizeof(int) * (2 * num_commands));
	shell->is_pipe = TRUE;
	i = 0;
	while (i < num_commands)
		pipe(tube + (i++) * 2);
	pipe_loop(substrings, tube, num_commands, shell);
	i = 0;
	while (i < 2 * (num_commands))
		close(tube[i++]);
	i = -1;
	while (++i < num_commands) 
		waitpid(-1, &shell->exit_code, 0);
	shell->exit_code /= 256;
	free(tube);
}

void	manage_pipes(char *line, int pipe_count, t_shell *shell)
{
	int		num_commands;
	char	**substrings;
	printf("MANAGE PIPES\n");
	substrings = (char **)malloc(sizeof(char *) * (pipe_count + 1 + 1));
	substrings[pipe_count + 1] = NULL;
	num_commands = split_pipes(line, substrings);
	if (num_commands != -1)
		launch_pipes(substrings, shell, num_commands);
	free_double_array(substrings);
	return ;
}
