/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:15:21 by akurmyza          #+#    #+#             */
/*   Updated: 2024/02/16 13:14:44 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	heredoc_loop(char **eof_hered, int count, int *old_fd, t_shell *sh)
{
	int	i;
	int	fd;

	i = 0;
	fd = 0;
	while (i < count)
	{
		heredoc_read(eof_hered[i], sh);
		fd = open("tmp_heredoc.txt", O_RDONLY);
		if (fd == -1)
			return (set_error("open", sh));
		if (dup2(fd, STDIN_FILENO) == -1)
			return (set_error("Failed to redirect stdin", sh));
		if (unlink("tmp_heredoc.txt") == -1)
			return (set_error("Failed to delete file", sh));
		if (count > 1)
			dup2(*old_fd, 0);
		i++;
	}
	return (fd);
}

static int	launch_heredoc(char **line, int count, int *old_fd, t_shell *shell)
{
	char	**eof_heredoc;
	int		i;
	int		fd;

	i = 0;
	*old_fd = dup(STDIN_FILENO);
	eof_heredoc = save_eof_heredoc(*line, count);
	*line = remove_heredoc(*line, eof_heredoc);
	fd = 0;
	fd = heredoc_loop(eof_heredoc, count, old_fd, shell);
	if (shell->is_pipe == FALSE)
	{
		launch_commands(*line, shell);
		dup2(*old_fd, 0);
		close(fd);
	}
	free_double_array(eof_heredoc);
	dup2(*old_fd, 0);
	return (fd);
}

int	run_heredoc(char **line, int *old_fd, t_shell *shell)
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
