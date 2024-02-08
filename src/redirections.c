/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 14:16:12 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/08 11:57:05 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	extract_redirection(char *line, int redirection_count, t_shell *shell)
{
	int		i;
	int		start;
	int		count;
	int		new;
	int		old;
	char	*filenames[redirection_count + 1];

	i = 0;
	count = 0;
	filenames[redirection_count] = NULL;
	while(line[i])
	{
		if (line[i] && line[i] == '>' && !is_quote(line[i - 1]) && !is_quote(line[i + 1]))
		{
			start = ++i;
			i = skip_until_char(line, i, ' ', 1);
			while (line[i] && line[i] != ' ')
				i++;
			filenames[count] = ft_strtrim(ft_substr(line, start, i - start), " ");
			line = ft_strjoin(ft_substr(line, 0, start - 2), ft_substr(line, i, ft_strlen(line) - i));
			count++;
			i = -1;
		}
		i++;
	}
	i = 0;
	old = dup(1);
	while (i < redirection_count)
	{
		new = open(filenames[i],  O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (new == -1)
    	{
			perror("open");
			shell->exit_code = 1;
			return (-1);
		}
		dup2(new, 1);
		launch_commands(line, shell);
		i++;
	}
	return (old);
}

int	redirections(char **line, t_shell *shell)
{
	int		redirection_count;

	redirection_count = check_symbol(*line, '>');
	if (redirection_count == -1)
	{
		printf("minishell: syntax error\n");
		shell->exit_code = 1;
		return (-1);
	}
	if (redirection_count == 0)
		return (0);
	return (extract_redirection(*line, redirection_count, shell));
}