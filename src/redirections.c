/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 14:16:12 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/18 15:47:18 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	*launch_redir(char *line, char **file, int redir_count, t_shell *sh)
{
	int		*old;
	int		i;

	old = malloc(sizeof(int) * 2);
	old[1] = dup(1);
	old[0] = dup(0);
	i = -1;
	while (++i < redir_count * 2)
	{
		if (ft_strcmp(file[i], "<") || ft_strcmp(file[i], ">") \
		|| ft_strcmp(file[i], ">>"))
		{
			if (open_file(file, file[i], i, sh) == -1)
			{
				old[0] = -1;
				free_double_array(file);
				free(line);
				return (old);
			}
		}
	}
	free_double_array(file);
	launch_commands(line, sh);
	free(line);
	return (old);
}

char	*extract_input_output(char *line, int i)
{
	int		start;
	char	*filename;
	char	*tmp;

	start = ++i;
	i = skip_until_char(line, i, ' ', 1);
	i = skip_until_char(line, i, ' ', 0);
	tmp = ft_substr(line, start, i - start);
	filename = ft_strtrim(tmp, " ");
	free(tmp);
	return (filename);
}

char	*remove_redir(char *line, int i)
{
	char	*cmd;
	char	*after_redir;
	char	*tmp;
	int		start;

	start = ++i;
	i = skip_until_char(line, i, ' ', 1);
	i = skip_until_char(line, i, ' ', 0);
	cmd = ft_substr(line, 0, start - 1);
	after_redir = ft_substr(line, i, ft_strlen(line) - i);
	tmp = ft_strjoin(cmd, after_redir);
	free(line);
	free(cmd);
	free(after_redir);
	return (tmp);
}

static int	*extract_redirection(char *line, int redir_count, t_shell *shell)
{
	int		i;
	int		count;
	char	**filenames;
	char	*tmp;

	tmp = ft_strdup(line);
	i = -1;
	count = 0;
	filenames = malloc(sizeof(char *) * (redir_count * 2 + 1));
	filenames[redir_count * 2] = NULL;
	while (tmp[++i])
	{
		if (tmp[i] && tmp[i] == '>' && tmp[i + 1] == '>' && \
		!is_quote(tmp[i - 1]) && !is_quote(tmp[i + 2]))
		{
			filenames[count++] = ft_strdup(">>");
			filenames[count++] = extract_input_output(tmp, i + 1);
			tmp = remove_redir(tmp, i + 1);
			i = -1;
		}
		else if (tmp[i] && (tmp[i] == '>' || tmp[i] == '<') && \
		!is_quote(tmp[i - 1]) && !is_quote(tmp[i + 1]))
			tmp = get_filename(filenames, tmp, &count, &i);
	}
	return (launch_redir(tmp, filenames, redir_count, shell));
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
		ft_error("minishell: syntax error\n", shell);
		error = malloc(sizeof(int) * 1);
		error[0] = -1;
		return (error);
	}
	if (output_redir == -2 || input_redir == -2 || append_redir == -2)
	{
		error = malloc(sizeof(int) * 1);
		error[0] = -2;
		return (error);
	}
	if (output_redir == 0 && input_redir == 0 && append_redir == 0)
		return (0);
	return (extract_redirection(*line, \
	output_redir + input_redir + append_redir, shell));
}
