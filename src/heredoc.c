/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:15:21 by akurmyza          #+#    #+#             */
/*   Updated: 2024/02/10 18:01:37 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//  finds heredoc or append redirection in a line
int	check_double_symbol(char *line, char c)
{
	int	i;
	int	status;
	int	count;

	i = -1;
	status = 0;
	count = 0;
	while (line[++i])
	{
		if (is_quote(line[i]))
			i = skip_until_char(line, i, line[i], 2);
		if (line[i] != c && line[i] != ' ' && !is_quote(line[i]))
			status = 1;
		if (status == 1 && line[i] == c && line[i + 1] == c && !is_quote(line[i - 1]) \
		&& !is_quote(line[i + 2]) && line[i + 2] != c && line[i - 1] != c)
		{
			if (is_empty_line(line + i + 2))
				return (-1);
			count++;
			status = 0;
		}
	}
	return (count);
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
	while (get_line != NULL && !ft_strcmp(get_line, exit_heredoc) \
	&& g_ctrl_c_status != 130)
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
	while (get_line != NULL && !ft_strcmp(get_line, exit_heredoc) \
	&& g_ctrl_c_status != 130)
	{
		save_cat[j++] = ft_substr(get_line, 0, ft_strlen(get_line));
		free(get_line);
		write(1, "heredoc> ", 9);
		get_line = get_next_line(0);
	}
	if (!is_empty_line(line + i))
		return (i);
	start = 0;
	while (start < j && g_ctrl_c_status != 130)
		printf("%s", save_cat[start++]);
	return (-1);
}

char	*run_heredoc(char *line, char *command)
{
	int		i;
	int		before_heredoc;

	if (check_double_symbol(line, '<') == 0)
		return (line);
	i = 0;
	while (line[i] && line[i] != '<')
		i++;
	before_heredoc = i;
	i = skip_until_char(line, i + 2, ' ', 1);
	if (!line[i] || check_double_symbol(line, '<') == -1)
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
	if (g_ctrl_c_status == 130)
		return (NULL);
	return (ft_strjoin(ft_substr(line, 0, before_heredoc), line + i));
}
