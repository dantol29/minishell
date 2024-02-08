/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:15:21 by akurmyza          #+#    #+#             */
/*   Updated: 2024/02/08 11:57:46 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	check_invalid_heredoc(char *line, int i)
{
	while (line[i])
	{
		if (line[i] == '<' || is_quote(line[i]))
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
	i = skip_until_char(line, i, ' ', 0);
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
	if (!is_empty_line(line + i))
		return (i);
	start = 0;
	while (start < j)
		printf("%s", save_cat[start++]);
	return (-1);
}

char	*run_heredoc(char *line, char *command)
{
	int		i;
	int		before_heredoc;

	if (!is_heredoc(line))
		return (line);
	i = 0;
	while (line[i] && line[i] != '<')
		i++;
	before_heredoc = i;
	i = skip_until_char(line, i + 2, ' ', 1);
	if (!line[i] || is_heredoc(line) == -1)
	{
		printf("heredoc: syntax error\n");
		return (NULL);
	}
	if (ft_strncmp("cat", command, 3) == 0)
	{
		i = heredoc_cat(line, i);
		if (i == -1)
			return (NULL);
	}
	else
		i = heredoc_read(line, i);
	return (ft_strjoin(ft_substr(line, 0, before_heredoc), line + i));
}
