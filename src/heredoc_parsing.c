/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:15:21 by akurmyza          #+#    #+#             */
/*   Updated: 2024/02/18 12:13:49 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	heredoc_read(char *exit_heredoc, t_shell *shell)
{
	char	*get_line;
	int		fd;

	signal(SIGQUIT, SIG_IGN);
	fd = open("tmp_heredoc.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		set_error("open", shell);
		return ;
	}
	while (1)
	{
		get_line = readline("> ");
		if (get_line == NULL || ft_strcmp(get_line, exit_heredoc) \
		|| g_ctrl_c_status == 130)
		{
			free(get_line);
			break ;
		}
		get_line = change_env_var(get_line, shell);
		write(fd, get_line, ft_strlen(get_line));
		write(fd, "\n", 1);
		free(get_line);
	}
}

char	**save_eof_heredoc(char *line, int count)
{
	int		i;
	int		j;
	int		start_eof;
	char	*tmp;
	char	**eof_heredoc;

	eof_heredoc = malloc(sizeof(char *) * (count + 1));
	eof_heredoc[count] = NULL;
	i = 0;
	j = 0;
	while (j < count)
	{
		i = skip_until_char(line, i, '<', 0);
		if (line[i] && line[i] == '<')
			i += 2;
		i = skip_until_char(line, i, ' ', 1);
		start_eof = i;
		i = skip_until_char(line, i, ' ', 0);
		tmp = ft_substr(line, start_eof, i - start_eof);
		eof_heredoc[j++] = ft_strtrim(tmp, " ");
		free(tmp);
	}
	return (eof_heredoc);
}

char	*get_line_without_heredoc(char *line, int start_heredoc, int i)
{
	char	*before_heredoc;
	char	*after_heredoc;
	char	*tmp;
	char	*new;

	before_heredoc = ft_substr(line, 0, start_heredoc);
	after_heredoc = ft_substr(line, i, ft_strlen(line) - i);
	tmp = ft_strtrim(after_heredoc, " ");
	new = ft_strjoin(before_heredoc, tmp);
	free(tmp);
	free(before_heredoc);
	free(after_heredoc);
	free(line);
	return (new);
}

char	*remove_heredoc(char *line, char **eof_heredoc)
{
	int		i;
	int		j;
	int		start_heredoc;
	char	*tmp;

	i = 0;
	j = 0;
	tmp = ft_strdup(line);
	while (eof_heredoc[j])
	{
		i = skip_until_char(tmp, i, '<', 0);
		start_heredoc = i;
		if (tmp[i] && tmp[i] == '<')
			i += 2;
		i = skip_until_char(tmp, i, ' ', 1);
		i = skip_until_char(tmp, i, ' ', 0);
		tmp = get_line_without_heredoc(tmp, start_heredoc, i);
		i = 0;
		j++;
	}
	free(line);
	return (tmp);
}
