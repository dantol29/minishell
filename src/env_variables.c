/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:43:39 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/19 11:24:30 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*exec_env_value(char *before_v, char *v, char *after_v, t_shell *sh)
{
	char	*value;
	char	*tmp;

	if (ft_strcmp(v, "?"))
	{
		if (g_ctrl_c_status == 130)
			tmp = ft_itoa(130);
		else
			tmp = ft_itoa(sh->exit_code);
		value = ft_strjoin(tmp, after_v);
		free(tmp);
	}
	else
	{
		tmp = ft_strjoin(get_env_value(v, sh->env), after_v);
		value = ft_strdup(tmp);
		free(tmp);
	}
	tmp = ft_strjoin(before_v, value);
	free(value);
	return (tmp);
}

static char	*replace_env_value(char	*line, int *i, t_shell *shell)
{
	int		start;
	char	*before_var;
	char	*var;
	char	*after_var;

	start = *i;
	while (line[*i] && line[*i] != ' ' && \
	!is_quote(line[*i]) && (ft_isalnum(line[*i]) || line[*i] == '_'))
		*i += 1;
	var = ft_substr(line, start, *i - start);
	after_var = ft_substr(line, *i, ft_strlen(line) - *i);
	before_var = ft_substr(line, 0, start - 1);
	free(line);
	if (find_env_var(var, shell->env) || ft_strcmp(var, "?"))
		line = exec_env_value(before_var, var, after_var, shell);
	else
		line = skip_env_var(before_var, after_var, i);
	free(before_var);
	free(var);
	free(after_var);
	*i = 0;
	return (line);
}

static char	*replace_exit_code(char *line, int *i, t_shell *shell)
{
	char	*var;
	char	*after_var;
	char	*before_var;

	before_var = ft_substr(line, 0, *i);
	var = ft_substr(line, *i + 1, 1);
	after_var = ft_substr(line, *i + 2, ft_strlen(line) - *i + 1);
	free(line);
	line = exec_env_value(before_var, var, after_var, shell);
	free(before_var);
	free(var);
	free(after_var);
	*i = 0;
	return (line);
}

char	*change_env_var(char *line, t_shell *shell)
{
	int		i;
	char	*tmp;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			i = skip_until_char(line, i, '\'', 2);
		if (line[i] == '$' && (is_quote(line[i + 1]) \
		|| line[i + 1] == ' ' || line[i + 1] == '\0'))
			i++;
		if (line[i] == '$' && line[i + 1] == '?')
			line = replace_exit_code(line, &i, shell);
		else if (line[i++] == '$')
			line = replace_env_value(line, &i, shell);
	}
	tmp = ft_strdup(line);
	free(line);
	return (tmp);
}
