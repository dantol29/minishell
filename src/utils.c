/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:51:29 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/21 17:26:10 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strcmp(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
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
	write(1, "", 1);
	return (TRUE);
}