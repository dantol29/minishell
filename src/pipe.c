/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:14:45 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/24 11:52:03 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_pipe_symbol(char *line)
{
	int	i;
	int	status;
	int	pipe_count;

	i = 0;
	status = 0;
	pipe_count = 0;
	while (line[i])
	{
		if (line[i] != '|' && line[i] != ' ' && !is_quote(line[i]))
			status = 1;
		if (status == 1 && line[i] == '|' && !is_quote(line[i - 1]) && !is_quote(line[i + 1]))
		{
			if (!is_empty_line(line + i + 1))
				pipe_count++;
			else
			{
				printf("syntax error near '|'\n");
				return (-1);
			}
			status = 0;
		}
		i++;
	}
	printf("pipe count:%d\n", pipe_count);
	return (pipe_count);
}

void	call_pipe_function(void)
{
	return ;
}
