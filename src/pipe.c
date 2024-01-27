/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:14:45 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/27 15:37:56 by dtolmaco         ###   ########.fr       */
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
	printf("%c count:%d\n", c, count);
	return (count);
}

int	is_valid_substring(char *line)
{
	char	*command;

	command = find_command(ft_strtrim(line, " "));
	if (access(command, 0) == 0 \
	|| access(ft_strjoin("/bin/", command), 0) == 0)
		return (TRUE);
	return (FALSE);
}

char	*split_pipes(char *line)
{
	int		pipe_count;
	int		i;
	int		j;
	int		start;
	char	**substrings;

	pipe_count = check_symbol(line, '|');
	if (pipe_count <= 0)
	{
		if (pipe_count == -1)
		{
			printf("syntax error near '|'\n");
			return (NULL);
		}
		return (line);
	}
	substrings = (char **)malloc(sizeof(char *) * (pipe_count + 1));
	if (!substrings)
		return (NULL);
	i = 0;
	j = 0;
	start = i;
	while (line[i])
	{
		if (line[i + 1] == '\0' || \
		(line[i] == '|' && !is_quote(line[i - 1]) && !is_quote(line[i + 1])))
		{
			substrings[j] = (char *)malloc(sizeof(char) * (i - start + 1));
			if (!substrings[j])
				return (NULL);
			if (line[i + 1] == '\0')
				substrings[j++] = ft_substr(line, start, i - start + 1);
			else
				substrings[j++] = ft_substr(line, start, i - start);
			if (!is_valid_substring(substrings[j - 1]))
			{
				printf("%s: command not found\n", ft_strtrim(substrings[j - 1], " "));
				substrings[j] = NULL;
				free_double_array(substrings, j);
				return (NULL);
			}
			start = i + 1;
		}
		i++;
	}
	substrings[j] = NULL;
	return (line);
}
