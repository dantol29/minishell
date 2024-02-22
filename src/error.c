/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:37:28 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/22 14:50:43 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	syntax_error(char *line, t_shell *shell)
{
	write(2, line, ft_strlen(line));
	shell->exit_code = 2;
	return (FALSE);
}

int	ft_error(char *line, t_shell *shell)
{
	write(2, line, ft_strlen(line));
	shell->exit_code = 1;
	return (FALSE);
}

int	set_error(char *line, t_shell *shell)
{
	perror(line);
	shell->exit_code = 1;
	return (FALSE);
}
