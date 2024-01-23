/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:15:21 by akurmyza          #+#    #+#             */
/*   Updated: 2024/01/23 18:14:07 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_heredoc(char *line)
{
    int i;
	int	count;

	count = 0;
    i = 0;
    while(line[i])
	{
		if(line[i] == '<' && line[i + 1] == '<')
		{
			i += 2;
			while (line[i])
			{
				count++;
				if (line[i] == '<')
					return (FALSE);
				i++;
			}
		}
		i++;
	}
	if (count == 1)
		return (TRUE);
	return (FALSE);
}

char   *run_heredoc(char *line)
{
    int     i;
    int     start;
	int		before_heredoc;
    char    *exit_heredoc;
    char    *read_heredoc;

    i = 0;
    while(line[i] && line[i] != '<')
		i++;
	before_heredoc = i;
    i += 2;
	while (line[i] && line[i] == ' ')
		i++;
    if(!line[i])
    {
        printf("heredoc: syntax error\n");
        return (NULL);
    }
    start = i;
    while(line[i] && line[i] != ' ')
        i++;
    exit_heredoc = ft_strjoin(ft_substr(line, start, i - start), "\n");
	write(1, "heredoc> ", 9);
    read_heredoc = get_next_line(0);
    while(read_heredoc != NULL && !ft_strcmp(read_heredoc, exit_heredoc))
    {
        free(read_heredoc);
		write(1, "heredoc> ", 9);
        read_heredoc = get_next_line(0);
    }
    return (ft_strjoin(ft_substr(line, 0, before_heredoc), line + i));
}
