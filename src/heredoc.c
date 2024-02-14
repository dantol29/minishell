/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:15:21 by akurmyza          #+#    #+#             */
/*   Updated: 2024/02/14 11:06:03 by akurmyza         ###   ########.fr       */
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
		printf(":%s:",get_line);
		printf(":%s:", exit_heredoc);
		if (get_line == NULL || ft_strcmp(get_line, exit_heredoc) \
		|| g_ctrl_c_status == 130)
		{
			free(get_line);
			break ;
		}
		write(fd, get_line, ft_strlen(get_line));
		write(fd, "\n", 1);
		free(get_line);
	}
	close(fd);
	//printf("exit:%s:\n", exit_heredoc);
}

char **save_eof_heredoc(char *line, int count, t_shell *shell)
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
		heredoc_read(eof_heredoc[j], shell);
		i++;
		j++;
	}
	return (eof_heredoc);
}

void	launch_heredoc(char *line, int count, t_shell *shell)
{
	char **eof_heredoc;
	int i;
	
	i = 0;
	eof_heredoc = save_eof_heredoc(line, count, shell);
	while (i < count)
	{
		heredoc_read(eof_heredoc[i], shell);
		i++;	
	}
	
}

// void	launch_heredoc(char *line, int count, t_shell *shell)
// {
// 	char **eof_heredoc;
// 	int i;
// 	int	fd;
	
// 	i = 0;
// 	eof_heredoc = save_eof_heredoc(line, count, shell);
// 	while (i < count)
// 	{
// 		// do i need to send
// 		heredoc_read(eof_heredoc[i], shell);
// 		fd = open("tmp_heredoc.txt", O_RDONLY);
// 		if (fd == -1)
// 		{
// 			perror("open");
// 			shell->exit_code = 1;
// 			return (-1);
// 		}
// 		if (dup2(fd, STDIN_FILENO) == -1)
// 		{
//             perror("Failed to redirect stdin");
//             close(fd);
// 			shell->exit_code = 1;
// 			return (-1);
//         }
// 		close(fd);
// 		if (unlink("tmp_heredoc.txt") == -1)
// 		{
//             perror("Failed to delete file");
// 			shell->exit_code = 1;
// 			return (-1);
//         }
// 		i++;	
// 	}
	
// }

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
	launch_heredoc(line, count, shell);
	if (g_ctrl_c_status == 130)
		return (NULL);
	return (NULL);
	//return (ft_strjoin(ft_substr(line, 0, before_heredoc), line + i));
}

// int	open_tmp_heredoc(char *line, t_shell *shell)
// {
// 	int	fd;

// 	fd = open("tmp_heredoc.txt", O_RDWR | O_CREAT | O_APPEND, 0644);
// 	if (fd == -1)
// 	{
// 		perror("open");
// 		shell->exit_code = 1;
// 		return (-1);
// 	}
// 	return (fd);
// }