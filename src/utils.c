/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:51:29 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/24 11:30:50 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] && str1[i] == str2[i])
		i++;
	if (str1[i] == str2[i])
		return (TRUE);
	return (FALSE);
}

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

char	*skip_command_name(char *line)
{
	while (*line && *line != ' ')
		line++;
	line = ft_strtrim(line, " ");
	return (line);
}

int	is_quote(char c)
{
	if (c == '\"' || c == '\'')
		return (TRUE);
	return (FALSE);
}