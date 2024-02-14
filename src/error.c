/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:37:28 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/14 17:17:13 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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