/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:15:21 by akurmyza          #+#    #+#             */
/*   Updated: 2024/02/14 13:41:46 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	launch_heredoc(char **line, int count, t_shell *shell)
{
	char **eof_heredoc;
	int i;
	int	fd;
	int	old_fd;
	
	i = 0;
	eof_heredoc = save_eof_heredoc(*line, count);
	*line = remove_heredoc(*line, eof_heredoc);
	while (i < count)
	{
		heredoc_read(eof_heredoc[i], shell);
		fd = open("tmp_heredoc.txt", O_RDONLY);
		if (fd == -1)
			return (set_error("open", shell));
		old_fd = dup(STDIN_FILENO);
		if (dup2(fd, STDIN_FILENO) == -1)
			return (set_error("Failed to redirect stdin", shell));
		if (unlink("tmp_heredoc.txt") == -1)
			return (set_error("Failed to delete file", shell));
		if (count > 1)
			dup2(old_fd, 0);
		i++;	
	}
	launch_commands(*line, shell);
	dup2(old_fd, 0);
	close(fd);
}

char	*run_heredoc(char *line, t_shell *shell)
{
	int		count;
	
	count = check_double_symbol(line, '<');
	if (count == 0 || count == -1)
	{
		if (count == 0)
			return (line);
		write(2, "heredoc: syntax error\n", 22);
		return (NULL);
	}
	launch_heredoc(&line, count, shell);
	return (NULL);
}
