/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:14:45 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/08 09:53:43 by akurmyza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_symbol(char *line, char c)
{
	int	i;
	int	status;
	int	count;

	i = 0;
	status = 0;
	count = 0;
	while (line[i])
	{
		if (is_quote(line[i]))
			i = skip_until_char(line, i, line[i], 2);
		if (line[i] != c && line[i] != ' ' && !is_quote(line[i]))
			status = 1;
		if (status == 0 && line[i] == c)
			return (-1);
		if (status == 1 && line[i] == c && !is_quote(line[i - 1]) \
		&& !is_quote(line[i + 1]))
		{
			if (!is_empty_line(line + i + 1))
				count++;
			else
				return (-1);
			status = 0;
		}
		i++;
	}
	//printf("%c count:%d\n", c, count);
	return (count);
}

int	is_valid_substring(char **substrings, int j, t_shell *shell)
{
	char	*command;

	command = find_command(substrings[j - 1]);
	if (access(command, 0) == 0 \
	|| access(ft_strjoin("/bin/", command), 0) == 0)
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
				substrings[j++] = ft_strtrim(ft_substr(line, start, i - start + 1), " ");
			else
			substrings[j++] = ft_strtrim(ft_substr(line, start, i - start), " ");
			if (!is_valid_substring(substrings, j, shell))
				return (-1);
			start = i + 1;
		}
		i++;
	}
	return (j);
}

void	launch_pipes(char **substrings ,t_shell *shell, int num_commands)
{
	int		tube[2 * num_commands];
	int		pid;
	int		i;
	int		j;
	int		current_pipe;

	shell->is_pipe = TRUE;
	i = 0;
	while (i < num_commands)
		pipe(tube + i++ * 2);
	i = 0;
	current_pipe = 0;
	while (i < num_commands)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i != num_commands - 1)
				dup2(tube[current_pipe + 1], 1);
			if (i != 0)
				dup2(tube[current_pipe - 2], 0);
			j = 0;
			while (j < 2 * (num_commands))
        		close(tube[j++]);
			launch_commands(substrings[i], shell);
			exit(EXIT_SUCCESS);
		}
		current_pipe += 2;
		i++;
	}
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