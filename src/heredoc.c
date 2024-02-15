/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:15:21 by akurmyza          #+#    #+#             */
/*   Updated: 2024/02/15 10:21:39 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int launch_heredoc(char **line, int count, int *old_fd, t_shell *shell)
{
	char **eof_heredoc;
	int i;
	int	fd;
	
	i = 0;
	*old_fd = dup(STDIN_FILENO);
	eof_heredoc = save_eof_heredoc(*line, count);
	*line = remove_heredoc(*line, eof_heredoc);
	fd = 0;
	while (i < count)
	{
		heredoc_read(eof_heredoc[i], shell);
		fd = open("tmp_heredoc.txt", O_RDONLY);
		if (fd == -1)
			return (set_error("open", shell));
		if (dup2(fd, STDIN_FILENO) == -1)
			return (set_error("Failed to redirect stdin", shell));
		if (unlink("tmp_heredoc.txt") == -1)
			return (set_error("Failed to delete file", shell));
		if (count > 1)
			dup2(*old_fd, 0);
		i++;	
	}
	if (shell->is_pipe == FALSE)
	{
		launch_commands(*line, shell);
		dup2(*old_fd, 0);
		close(fd);
	}
	dup2(*old_fd, 0);
	return (fd);
}

int run_heredoc(char **line, int *old_fd, t_shell *shell)
{
	int		count;
	
	count = check_double_symbol(*line, '<');
	if ((count == 0 || count == -1) && shell->is_pipe == FALSE)
	{
		if (count == 0)
		{
			launch_commands(*line, shell);
			return (TRUE);
		}
		write(2, "heredoc: syntax error\n", 22);
		return (FALSE);
	}
	return (launch_heredoc(line, count, old_fd, shell));
}
