/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:51:29 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/16 13:03:44 by akurmyza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_flags(char *line)
{
	int		i;
	int		count;
	int		symbol;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] != ' ' && !is_quote(line[i]))
		{
			count++;
			while (line[i] && line[i] != ' ')
				i++;
		}
		if (is_quote(line[i]))
		{
			symbol = line[i++];
			count++;
			while (line[i] && line[i] != symbol)
				i++;
		}
		i++;
	}
	return (count);
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
			if (line[i] && line[i] != symbol)
			{
				write(2, \
				"minishell: error while looking for matching quote\n", 50);
				return (FALSE);
			}
		}
		i++;
	}
	return (TRUE);
}
