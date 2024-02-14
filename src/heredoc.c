/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:15:21 by akurmyza          #+#    #+#             */
/*   Updated: 2024/02/14 13:11:54 by dtolmaco         ###   ########.fr       */
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

static void	heredoc_read(char *exit_heredoc, t_shell *shell)
{
	char	*get_line;
	int	fd;

	fd = open("tmp_heredoc.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		perror("open");
		shell->exit_code = 1;
		return ;
	}
	while (1)
	{
		get_line = readline("> ");
		get_line = change_env_var(get_line, shell);
		if (get_line == NULL || ft_strcmp(get_line, exit_heredoc) \
		|| g_ctrl_c_status == 130)
		{
			free(get_line);
			close(fd);
			break ;
		}
		write(fd, get_line, ft_strlen(get_line));
		write(fd, "\n", 1);
		free(get_line);
	}
}

char **save_eof_heredoc(char *line, int count)
{
	int		i;
	int		j;
	int		start_eof;
	int		start_heredoc;
	char	**eof_heredoc;

	eof_heredoc = malloc(sizeof(char *) * (count + 1));
	eof_heredoc[count] = NULL;
	i = 0;
	j = 0;
	while (j < count)
	{
		i = skip_until_char(line, i, '<', 0);
		start_heredoc = i;
		if (line[i] && line[i] == '<')
			i += 2;
		i = skip_until_char(line, i, ' ', 1);
		if (!line[i])
		{
			write(2, "heredoc: syntax error\n", 22);
			return (NULL) ;
		}
		start_eof = i;
		i = skip_until_char(line, i, ' ', 0);
		eof_heredoc[j++] = ft_strtrim(ft_substr(line, start_eof, i - start_eof), " ");
	}
	return (eof_heredoc);
}

char	*get_line_without_heredoc(char *line, int start_heredoc, int i)
{
	char	*before_heredoc;
	char	*after_heredoc;

	before_heredoc = ft_substr(line, 0, start_heredoc);
	after_heredoc = ft_substr(line, i, ft_strlen(line) - i);
	line = ft_strjoin(before_heredoc, after_heredoc);
	free(before_heredoc);
	free(after_heredoc);
	return (line);
}

char *remove_heredoc(char *line, char **eof_heredoc)
{
	int		i;
	int		j;
	int		start_heredoc;

	i = 0;
	j = 0;
	while (eof_heredoc[j])
	{
		i = skip_until_char(line, i, '<', 0);
		start_heredoc = i;
		if (line[i] && line[i] == '<')
			i += 2;
		i = skip_until_char(line, i, ' ', 1);
		if (!line[i])
		{
			write(2, "heredoc: syntax error\n", 22);
			return (NULL) ;
		}
		i = skip_until_char(line, i, ' ', 0);
		line = get_line_without_heredoc(line, start_heredoc, i);
		j++;
	}
	return (line);
}

void	set_error(char *line, t_shell *shell)
{
	perror(line);
	shell->exit_code = 1;
}

void	launch_heredoc(char *line, int count, t_shell *shell)
{
	char **eof_heredoc;
	int i;
	int	fd;
	
	i = 0;
	eof_heredoc = save_eof_heredoc(line, count);
	line = remove_heredoc(line, eof_heredoc);
	printf("%s\n", line);
	while (i < count)
	{
		heredoc_read(eof_heredoc[i], shell);
		fd = open("tmp_heredoc.txt", O_RDONLY);
		if (fd == -1)
			return (set_error("open", shell));
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			close(fd);
			return (set_error("Failed to redirect stdin", shell));
		}
		close(fd);
		if (unlink("tmp_heredoc.txt") == -1)
			return (set_error("Failed to delete file", shell));
		i++;	
	}
}

char	*run_heredoc(char *line, char *command, t_shell *shell)
{
	int		count;
	
	(void)command;
	count = check_double_symbol(line, '<');
	if (count == 0 || count == -1)
	{
		if (count == 0)
			return (line);
		write(2, "heredoc: syntax error\n", 22);
		return (NULL);
	}
	launch_heredoc(line, count, shell);
	return (NULL);
}
