/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_symbol.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:58:54 by akurmyza          #+#    #+#             */
/*   Updated: 2024/02/16 13:04:03 by akurmyza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_symbol(char *line, char c)
{
	int	i;
	int	status;
	int	count;

	i = -1;
	status = 0;
	count = 0;
	if (line[0] && line[1] && line[0] == c && line[1] != c)
		return (-2);
	while (line[++i])
	{
		if (is_quote(line[i]))
			i = skip_until_char(line, i, line[i], 2);
		if (line[i] != c && line[i] != ' ' && !is_quote(line[i]))
			status = 1;
		if (status == 1 && line[i] == c && !is_quote(line[i - 1]) \
		&& !is_quote(line[i + 1]) && line[i + 1] != c && line[i - 1] != c)
		{
			if (is_empty_line(line + i + 1))
				return (-1);
			count++;
			status = 0;
		}
	}
	return (count);
}

/*finds heredoc or append redirection in a line */
int	check_double_symbol(char *line, char c)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (line[++i])
	{
		if (is_quote(line[i]))
			i = skip_until_char(line, i, line[i], 2);
		if (line[i] == c && line[i + 1] == c && !is_quote(line[i - 1]) \
		&& !is_quote(line[i + 2]) && line[i + 2] != c && line[i - 1] != c)
		{
			if (is_empty_line(line + i + 2))
				return (-1);
			count++;
		}
	}
	return (count);
}

int	is_quote(char c)
{
	if (c == '\"' || c == '\'')
		return (TRUE);
	return (FALSE);
}
