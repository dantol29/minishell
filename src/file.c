/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:06:38 by akurmyza          #+#    #+#             */
/*   Updated: 2024/02/16 13:54:45 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_file(char **filenames, char *redir, int i, t_shell *shell)
{
	int	new;

	new = 0;
	if (ft_strcmp(redir, ">"))
		new = open(filenames[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (ft_strcmp(redir, "<"))
		new = open(filenames[i + 1], O_RDWR, 0644);
	else if (ft_strcmp(redir, ">>"))
		new = open(filenames[i + 1], O_RDWR | O_CREAT | O_APPEND, 0644);
	if (new == -1)
	{
		perror("open");
		shell->exit_code = 1;
		return (-1);
	}
	if (ft_strcmp(redir, ">") || ft_strcmp(redir, ">>"))
		dup2(new, 1);
	else if (ft_strcmp(redir, "<"))
		dup2(new, 0);
	return (0);
}
