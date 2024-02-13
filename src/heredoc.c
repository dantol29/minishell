/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:15:21 by akurmyza          #+#    #+#             */
/*   Updated: 2024/02/13 19:42:49 by akurmyza         ###   ########.fr       */
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
	int	count;

	i = -1;
	count = 0;
	while (line[++i])
	{
		if (is_quote(line[i]))
			i = skip_until_char(line, i, line[i], 2);
		if (line[i] == c && line[i + 1] == c && !is_quote(line[i - 1]) \
		&& !is_quote(line[i + 2]) && line[i + 2] != c && line[i - 1] != c)
		{
			if (is_empty_line(line + i + 2))
				return (-1);
			count++;
		}
	}
	return (count);
}

static void	heredoc_read(char *exit_heredoc)
{
	char	*get_line;

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

	//printf("exit:%s:\n", exit_heredoc);
}

char ** save_eof_heredoc(char *line, int count)
{
	int		i;
	int		j;
	int		start;
	char	**eof_heredoc;


	eof_heredoc = malloc(sizeof(char *) * (count + 1));
	eof_heredoc[count] = NULL;
	i = 0;
	j = 0;
	while (j < count)
	{
		start = i;
		while (line[i] && line[i] != '<')
			i++;
		if (line[i] && line[i] == '<')
			i += 2;
		while (line[i] && line[i] == ' ')
			i++;
		if (!line[i])
		{
			write(2, "heredoc: syntax error\n", 22);
			return (NULL) ;
		}
		start = i;
		while (line[i] && line[i] != ' ')
			i++;
		eof_heredoc[j] = ft_strtrim(ft_substr(line, start, i - start), " ");
		heredoc_read(eof_heredoc[j]);
		i++;
		j++;
	}
	return (eof_heredoc);
}

void	launch_heredoc(char *line, int count)
{
	save_eof_heredoc(line, count);
}

char	*run_heredoc(char *line, char *command, t_shell *shell)
{
	int		count;
	
	(void)command;
	(void)shell;
	count = check_double_symbol(line, '<');
	//printf("count:%d\n", count);
	if (count == 0 || count == -1)
	{
		if (count == 0)
			return (line);
		write(2, "heredoc: syntax error\n", 22);
		return (NULL);
	}
	launch_heredoc(line, count);
	if (g_ctrl_c_status == 130)
		return (NULL);
	return (NULL);
	//return (ft_strjoin(ft_substr(line, 0, before_heredoc), line + i));
}

int	open_tmp_heredoc(char *line, t_shell *shell)
{
	int	new;

	new = 0;
	if (ft_strcmp(line, "<<"))
		new = open("tmp_heredoc.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
	if (new == -1)
	{
		perror("open");
		shell->exit_code = 1;
		return (-1);
	}
	// if (ft_strcmp(redir, ">>"))
	dup2(new, 1);

	return (0);
}