/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:14:45 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/25 12:36:28 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_pipe_symbol(char *line)
{
	int	i;
	int	status;
	int	pipe_count;

	i = 0;
	status = 0;
	pipe_count = 0;
	if (line[0] == '|')
		return (-1);
	while (line[i])
	{
		if (line[i] != '|' && line[i] != ' ' && !is_quote(line[i]))
			status = 1;
		if (status == 1 && line[i] == '|' && !is_quote(line[i - 1]) && !is_quote(line[i + 1]))
		{
			if (!is_empty_line(line + i + 1))
				pipe_count++;
			else
				return (-1);
			status = 0;
		}
		i++;
	}
	printf("pipe count:%d\n", pipe_count);
	return (pipe_count);
}

int is_valid_substring(char *line)
{
	char	*command;

	command = find_command(ft_strtrim(line, " "));
	if (access(command, 0) == 0 \
	|| access(ft_strjoin("/bin/", command), 0) == 0)
		return (TRUE);
	return(FALSE);
}

char	*split_pipes(char *line)
{
	int pipe_count;
	int	i;
	int	j;
	int	start;
	char **substrings;
	
	pipe_count = check_pipe_symbol(line);
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
			if(!is_valid_substring(substrings[j - 1]))
				return (ft_strtrim(substrings[j - 1], " "));
			start = i + 1;
		}
		i++;
	}
	return (line);
}
