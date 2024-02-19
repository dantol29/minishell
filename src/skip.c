/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 14:01:31 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/19 18:21:32 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_i_and_count(int *i, int *count)
{
	*i += 1;
	*count += 1;
}

char	*skip_flag_n(char *line, int j)
{
	char	*new;
	char	*tmp;

	new = ft_strdup(line + j);
	free(line);
	tmp = ft_strtrim(new, " ");
	free(new);
	return (tmp);
}

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
