/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:51:29 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/19 10:53:03 by dtolmaco         ###   ########.fr       */
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

void	dup_output(int *tube, int current_pipe, int num_cmd, int i)
{
	if (i != num_cmd - 1)
		dup2(tube[current_pipe + 1], 1);
}

int	count_flags(char *line)
{
	int		i;
	int		count;
	int		symbol;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] != ' ')
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
