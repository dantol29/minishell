/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:14:45 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/21 19:27:50 by akurmyza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_pipe_symbol(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '|')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	call_pipe_function(void)
{
	return ;
}
