/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:15:21 by akurmyza          #+#    #+#             */
/*   Updated: 2024/01/24 16:04:50 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_invalid_heredoc(char *line, int i)
{
	while (line[i])
	{
		if (is_quote(line[i]))
			return (-1);
		if (line[i] == '<')
			return (-1);
		i++;
	}
	return (i);
}

//  expects substring  between pipes and without command
int	is_heredoc(char *line, int command_len)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	line = line + command_len;
	while (line[i])
	{
		if (is_quote(line[i]))
			return (-1);
		if (line[i] == '<' && line[i + 1] == '<')
		{
			i += 2;
			if (is_empty_line(line))
				return (-1);
			i = check_invalid_heredoc(line, i);
			if (i == -1)
				return (-1);
			count++;
		}
		i++;
	}
	return (count == 1);
}

static int	heredoc_read(char *line, int i)
{
	int		start;
	char	*exit_heredoc;
	char	*get_line;

	start = i;
	while (line[i] && line[i] != ' ')
		i++;
	exit_heredoc = ft_strjoin(ft_substr(line, start, i - start), "\n");
	write(1, "heredoc> ", 9);
	get_line = get_next_line(0);
	while (get_line != NULL && !ft_strcmp(get_line, exit_heredoc))
	{
		free(get_line);
		write(1, "heredoc> ", 9);
		get_line = get_next_line(0);
	}
	return (i);
}

char	*run_heredoc(char *line, char *command)
{
	int		i;
	int		before_heredoc;
	int		heredoc_status;

	heredoc_status = is_heredoc(line, ft_strlen(command));
	if (!heredoc_status)
		return (line);
	i = 0;
	while (line[i] && line[i] != '<')
		i++;
	before_heredoc = i;
	i += 2;
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i] || heredoc_status == -1)
	{
		printf("heredoc: syntax error\n");
		return (NULL);
	}
	i = heredoc_read(line, i);
	return (ft_strjoin(ft_substr(line, 0, before_heredoc), line + i));
}
