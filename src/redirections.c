/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 14:16:12 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/11 13:09:22 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_file(char **filenames, char *redir, int i, t_shell *shell)
{
	int	new;

	new = 0;
	if (ft_strcmp(redir, ">"))
		new = open(filenames[i + 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (ft_strcmp(redir, "<"))
		new = open(filenames[i + 1], O_RDWR, 0644);
	else if (ft_strcmp(redir, ">>"))
		new = open(filenames[i + 1], O_RDWR | O_CREAT | O_APPEND, 0644);
	if (new == -1)
	{
		perror("open");
		shell->exit_code = 1;
		return (-1);
	}
	if (ft_strcmp(redir, ">") || ft_strcmp(redir, ">>"))
		dup2(new, 1);
	else if (ft_strcmp(redir, "<"))
		dup2(new, 0);
	return (0);
}

int	*launch_redirections(char *line, char **filenames, int redirection_count, t_shell *shell)
{
	int		*old;
	int		i;

	old = malloc(sizeof(int) * 2);
	old[1] = dup(1);
	old[0] = dup(0);
	i = 0;
	while (i < redirection_count * 2)
	{
		if (ft_strcmp(filenames[i], "<") || ft_strcmp(filenames[i], ">") \
		|| ft_strcmp(filenames[i], ">>"))
		{
			if (open_file(filenames, filenames[i], i, shell) == -1)
			{
				old[0] = -1;
				return (old);
			}
		}
		i++;
	}
	launch_commands(line, shell);
	return (old);
}

int	extract_input_output(char **line, char **file, int i, int *count)
{
	int		start;
	char	*tmp;

	tmp = *line;
	start = ++i;
	i = skip_until_char(tmp, i, ' ', 1);
	i = skip_until_char(tmp, i, ' ', 0);
	*file = ft_strtrim(ft_substr(tmp, start, i - start), " ");
	tmp = ft_strjoin(ft_substr(tmp, 0, start - 2), ft_substr(tmp, i, ft_strlen(tmp) - i));
	*count += 1;
	*line = tmp;
	return (-1);
}

int	*extract_redirection(char *line, int redirection_count, t_shell *shell)
{
	int		i;
	int		count;
	char	**filenames;

	i = -1;
	count = 0;
	filenames = malloc(sizeof(char *) * (redirection_count * 2 + 1));
	filenames[redirection_count * 2] = NULL;
	while (line[++i])
	{
		if (line[i] && line[i] == '>'  && line[i + 1] == '>' && \
		!is_quote(line[i - 1]) && !is_quote(line[i + 2]))
		{
			filenames[count] = ">>";
			i = extract_input_output(&line, &filenames[++count], ++i, &count);
		}
		else if (line[i] && (line[i] == '>' || line[i] == '<') && \
		!is_quote(line[i - 1]) && !is_quote(line[i + 1]))
		{
			filenames[count] = "<";
			if (line[i] == '>')
				filenames[count] = ">";
			i = extract_input_output(&line, &filenames[++count], i, &count);
		}
	}
	return (launch_redirections(line, filenames, redirection_count, shell));
}

int	*redirections(char **line, t_shell *shell)
{
	int		output_redir;
	int		input_redir;
	int		append_redir;
	int		*error;

	output_redir = check_symbol(*line, '>');
	input_redir = check_symbol(*line, '<');
	append_redir = check_double_symbol(*line, '>');
	if (output_redir == -1 || input_redir == -1 || append_redir == -1)
	{
		write(2, "minishell: syntax error\n", 24);
		shell->exit_code = 1;
		error = malloc(sizeof(int) * 1);
		error[0] = -1;
		return (error);
	}
	if (output_redir == 0 && input_redir == 0 && append_redir == 0)
		return (0);
	return (extract_redirection(*line, output_redir + input_redir + append_redir, shell));
}
