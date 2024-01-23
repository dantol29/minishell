/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:15:21 by akurmyza          #+#    #+#             */
/*   Updated: 2024/01/23 16:45:40 by akurmyza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int is_heredoc ( char *line)
{
    int i;

    i = 0;
    
    if (ft_strnstr(line, "<<", ft_strlen(line)))
        return (TRUE);
    return (FALSE);
}

char   *run_heredoc(char *line)
{
    int     i;
    int     start;
    char    *exit_heredoc;
    char    *line;

    i = 0;
    while(line[i] && line[i] != '<' && line[i + 1] != '<')
        i++;
    i += 2;
    if(!line[i])
    {
        printf("heredoc: syntax error\n");
        return ;
    }
    start = i;
    while(line[i] && line[i] != ' ')
        i++;
    exit_heredoc = ft_substr(line, start, i - start);
    line = get_next_line(0);
    while(line != NULL && !ft_strcmp(line, exit_heredoc))
    {
        free(line);
        line = get_next_line(0);
    }
    return (line + i);
}