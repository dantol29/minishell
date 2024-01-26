/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:15:21 by akurmyza          #+#    #+#             */
/*   Updated: 2024/01/26 11:05:07 by akurmyza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_invalid_heredoc(char *line, int i)
{
	while (line[i])
	{
		if (line[i] == '<')
			return (-1);
		i++;
	}
	return (i);
}

//  expects substring  between pipes and without command
int	is_heredoc(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '<' && line[i + 1] == '<' \
		&& !is_quote(line[i - 1]))
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

static int	heredoc_cat(char *line, int i)
{
	int		start;
	int		j;
	char	*exit_heredoc;
	char	*get_line;
	char	*save_cat[1024];

	j = 0;
	start = i;
	while (line[i] && line[i] != ' ')
		i++;
	exit_heredoc = ft_strjoin(ft_substr(line, start, i - start), "\n");
	write(1, "heredoc> ", 9);
	get_line = get_next_line(0);
	while (get_line != NULL && !ft_strcmp(get_line, exit_heredoc))
	{
		save_cat[j++] = ft_substr(get_line, 0, ft_strlen(get_line));
		free(get_line);
		write(1, "heredoc> ", 9);
		get_line = get_next_line(0);
	}
	start = 0;
	if (is_empty_line(line + i))
	{
		while (start < j)
			printf("%s", save_cat[start++]);
		return (-1);
	}
	return (i);
}

char	*run_heredoc(char *line, char *command)
{
	int		i;
	int		before_heredoc;
	int		heredoc_status;

	heredoc_status = is_heredoc(line);
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
	if (ft_strcmp("cat", command))
	{
		i = heredoc_cat(line, i);
		if (i == -1)
			return (NULL);
	}
	else
		i = heredoc_read(line, i);
	return (ft_strjoin(ft_substr(line, 0, before_heredoc), line + i));
}
