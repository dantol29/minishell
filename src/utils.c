/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:51:29 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/24 15:27:25 by dtolmaco         ###   ########.fr       */
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

/*checks that every quote is closed and skips \\"*/
int	check_quotes(char *line)
{
	char	symbol;
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] && line[i - 1] != '\\' && is_quote(line[i]))
		{
			symbol = line[i];
			while (line[i])
			{
				i++;
				if (line[i] && line[i] == symbol && line[i - 1] != '\\')
					break ;
			}
			if (line[i] != symbol)
			{
				printf("minishell: error while looking for matching quote\n");
				return (FALSE);
			}
		}
		i++;
	}
	return (TRUE);
}