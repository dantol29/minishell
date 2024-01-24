/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:15:21 by akurmyza          #+#    #+#             */
/*   Updated: 2024/01/24 14:18:53 by akurmyza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//  expects substring  between pipes and without command
int	is_heredoc(char *line, int command_len)
{
	int	i;
	int	status;
	int	count;

	i = 0;
	status = 0;
	count = 0;
    line = line + command_len;
	while (line[i])
	{
		if(is_quote(line[i]))
            return (FALSE);
		if(line[i] == '<' && line[i + 1] == '<')
		{
			i += 2;
            if (is_empty_line(line))
                return (-1);
			while (line[i])
			{
                if (is_quote(line[i]))
                    return (-1);
				if (line[i] == '<')
					return (-1);
				i++;
			}
            count++;
		}
		i++;
	}
    if (count == 1)
	    return (TRUE);
    return (FALSE);
}

char   *run_heredoc(char *line, char *command)
{
    int     i;
    int     start;
	int		before_heredoc;
    int     heredoc_status;
    char    *exit_heredoc;
    char    *read_heredoc;

    heredoc_status = is_heredoc(line, ft_strlen(command));
    if (!heredoc_status)
        return (line);
    i = 0;
    while(line[i] && line[i] != '<')
		i++;
	before_heredoc = i;
    i += 2;
	while (line[i] && line[i] == ' ')
		i++;
    if(!line[i] || heredoc_status == -1)
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
