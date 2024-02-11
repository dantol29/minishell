/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:15:21 by akurmyza          #+#    #+#             */
/*   Updated: 2024/02/11 15:46:22 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrl_c_heredoc(int signum)
{
	(void)signum;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	g_ctrl_c_status = 130;
}

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
	exit_heredoc = ft_substr(line, start, i - start);
	while (1)
	{
		get_line = readline("> ");
		if (get_line == NULL || ft_strcmp(get_line, exit_heredoc) \
		|| g_ctrl_c_status == 130)
		{
			free(get_line);
			break ;
		}
		free(get_line);
	}
	return (i);
}

static int	heredoc_cat(char *line, int i, t_shell *shell)
{
	int		start;
	int		j;
	char	*exit_heredoc;
	char	*get_line;
	char	*save_cat[1024];

	signal(SIGINT, ctrl_c_heredoc);
	j = 0;
	start = i;
	i = skip_until_char(line, i, ' ', 0);
	exit_heredoc = ft_substr(line, start, i - start);
	while (1)
	{
		get_line = readline("> ");
		if (g_ctrl_c_status == 130 || !get_line || ft_strcmp(get_line, exit_heredoc))
		{
			free(get_line);
			break ;
		}
		save_cat[j++] = ft_substr(get_line, 0, ft_strlen(get_line));
		free(get_line);
	}
	if (!is_empty_line(line + i))
		return (i);
	start = 0;
	while (start < j && g_ctrl_c_status != 130)
		printf("%s\n", change_env_var(save_cat[start++], shell));
	return (-1);
}

char	*run_heredoc(char *line, char *command, t_shell *shell)
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
		write(2, "heredoc: syntax error\n", 22);
		return (NULL);
	}
	if (ft_strncmp("cat", command, 3) == 0)
	{
		i = heredoc_cat(line, i, shell);
		if (i == -1)
			return (NULL);
	}
	else
		i = heredoc_read(line, i);
	if (g_ctrl_c_status == 130)
		return (NULL);
	return (ft_strjoin(ft_substr(line, 0, before_heredoc), line + i));
}
