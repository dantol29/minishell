/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:14:45 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/12 23:09:51 by akurmyza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_valid_substring(char **substrings, int j, t_shell *shell)
{
	char	*command;
	char	*path;

	command = find_command(substrings[j - 1]);
	path = get_executable_path(shell, command);
	free(command);
	if (path)
	{
		free(path);
		return (TRUE);
	}
	write(2, substrings[j - 1], ft_strlen(substrings[j - 1]));
	write(2, ": command not found\n", 20);
	shell->exit_code = 127;
	free(path);
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
		waitpid(-1, &shell->exit_code, 0);
	shell->exit_code /= 256;
	free(tube);
}

void	manage_pipes(char *line, t_shell *shell)
{
	//int	is_heredoc;
	int		pipe_count;
	int		num_commands;
	char	**substrings;

	//is_heredoc = (check_double_symbol(line, '<') != -1);
	pipe_count = check_symbol(line, '|');
	if (pipe_count <= 0)
	{
		if (pipe_count == -1)
		{
			write(2, "syntax error near '|'\n", 22);
			shell->exit_code = 1;
			return ;
		}
		shell->is_pipe = FALSE;
		launch_commands(line, shell);
		return ;
	}
	substrings = (char **)malloc(sizeof(char *) * (pipe_count + 1));
	num_commands = split_pipes(line, shell, substrings);
	if (num_commands != -1)
		launch_pipes(substrings, shell, num_commands);
	free_double_array(substrings, pipe_count + 1);
	return ;
}
