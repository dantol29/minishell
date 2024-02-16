/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:01:31 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/16 14:07:39 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	skip_until_char(char *line, int i, char c, char mode)
{
	if (mode == 0)
	{
		while (line[i] && line[i] != c)
			i++;
	}
	else if (mode == 1)
	{
		while (line[i] && line[i] == c)
			i++;
	}
	else if (mode == 2)
	{
		i++;
		while (line[i] && line[i] != c)
			i++;
	}
	return (i);
}

char	*skip_command_name(char *line)
{
	while (*line && *line != ' ')
		line++;
	while (*line && *line == ' ')
		line++;
	return (line);
}
