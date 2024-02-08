/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:14:45 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/08 15:21:52 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_valid_substring(char **substrings, int j, t_shell *shell)
{
	char	*command;
	char	*path;

	command = find_command(substrings[j - 1]);
	path = get_executable_path(shell, command);
	if (path)
		return (TRUE);
	printf("%s: command not found\n", substrings[j - 1]);
	shell->exit_code = 127;
	free_double_array(substrings, j);
	return (FALSE);
}

int	split_pipes(char *line, t_shell *shell, char **substrings)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	start = i;
	while (line[i])
	{
		if (line[i + 1] == '\0' || \
		(line[i] == '|' && !is_quote(line[i - 1]) && !is_quote(line[i + 1])))
		{
			if (line[i + 1] == '\0')
				substrings[j++] = \
				ft_strtrim(ft_substr(line, start, i - start + 1), " ");
			else
				substrings[j++] = \
				ft_strtrim(ft_substr(line, start, i - start), " ");
			if (!is_valid_substring(substrings, j, shell))
				return (-1);
			start = i + 1;
		}
		i++;
	}
	return (j);
}

void	pipe_loop(char **substrings, int *tube, int num_cmd, t_shell *shell)
{
	int		pid;
	int		i;
	int		j;
	int		current_pipe;

	i = 0;
	current_pipe = 0;
	while (i < num_cmd)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i != num_cmd - 1)
				dup2(tube[current_pipe + 1], 1);
			if (i != 0)
				dup2(tube[current_pipe - 2], 0);
			j = 0;
			while (j < 2 * (num_cmd))
				close(tube[j++]);
			launch_commands(substrings[i], shell);
			exit(EXIT_SUCCESS);
		}
		current_pipe += 2;
		i++;
	}
}

void	launch_pipes(char **substrings, t_shell *shell, int num_commands)
{
	int		*tube;
	int		i;

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
		wait(NULL);
}

void	manage_pipes(char *line, t_shell *shell)
{
	int		pipe_count;
	int		num_commands;
	char	**substrings;

	pipe_count = check_symbol(line, '|');
	if (pipe_count <= 0)
	{
		if (pipe_count == -1)
		{
			printf("syntax error near '|'\n");
			shell->exit_code = 1;
			return ;
		}
		shell->is_pipe = FALSE;
		launch_commands(line, shell);
		return ;
	}
	substrings = (char **)malloc(sizeof(char *) * (pipe_count + 1));
	num_commands = split_pipes(line, shell, substrings);
	if (num_commands == -1)
		return ;
	launch_pipes(substrings, shell, num_commands);
	return ;
}
