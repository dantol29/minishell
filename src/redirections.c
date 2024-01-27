/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 14:16:12 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/27 17:09:01 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*extract_redirection(char *line, char **filename)
{
	int		i;
	int		start;

	i = 0;
	while(line[i])
	{
		if (line[i] && line[i] == '>' && !is_quote(line[i - 1]) && !is_quote(line[i + 1]))
		{
			start = ++i;
			i = skip_until_char(line, i, ' ', 1);
			while (line[i] && line[i] != ' ')
				i++;
			*filename = ft_substr(line, start, i - start);
			line = ft_strjoin(ft_substr(line, 0, start - 2), ft_substr(line, i, ft_strlen(line) - i));
		}
		i++;
	}
	return (line);
}

int	redirections(char **line, t_shell *shell)
{
	int		new;
	int		old;
	char	*filename;

	if (check_symbol(*line, '>') == -1)
	{
		write(2, "minishell: syntax error\n", 24);
		shell->exit_code = 1;
		return (-1);
	}
	if (check_symbol(*line, '>') == 0)
		return (0);
	*line = extract_redirection(*line, &filename);
	new = open(filename,  O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (new == -1)
    {
		perror("open");
		shell->exit_code = 1;
		return (-1);
	}
	old = dup(1);
	dup2(new, 1);
	return (old);
}