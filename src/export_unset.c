/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:20:15 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/12 17:56:08 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_env_var_value(char *variable_name, char *new_value, t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, variable_name))
		{
			tmp->value = new_value;
			break ;
		}
		tmp = tmp->next;
	}
}

void	unset_env_var(char *env_name, t_env **lst)
{
	t_env	*current;
	t_env	*prev;

	current = *lst;
	prev = NULL;
	if (!find_env_var(env_name, *lst))
	{
		free(env_name);
		return ;
	}
	if (current != NULL && ft_strcmp(current->name, env_name))
	{
		*lst = current->next;
		free(current);
		free(env_name);
		return ;
	}
	while (current && !ft_strcmp(current->name, env_name))
	{
		prev = current;
		current = current->next;
	}
	prev->next = current->next;
	free(env_name);
	free(current);
}

t_env	*create_new_env_node(char *name, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}

static void	add_env_var(char *line, int i, t_shell *shell)
{
	char	*value;

	value = find_command(line + i);
	if (!value || is_empty_line(value))
		return ;
	value = change_env_var(value, shell);
	if (find_env_var(ft_substr(line, 0, i - 1), shell->env))
		replace_env_var_value(ft_substr(line, 0, i - 1), value, shell->env);
	else
		lstadd_back(&shell->env, \
		create_new_env_node(ft_substr(line, 0, i - 1), value));
}

int	export(char *line, t_shell *shell)
{
	int		i;

	line = skip_command_name(line);
	if (is_empty_line(line))
	{
		print_env(shell->env);
		return (TRUE);
	}
	i = 0;
	if (line[0] != '_' && !ft_isalpha(line[0]))
		return (ft_error("minishell: export: not a valid identifier\n", shell));
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
		i++;
	if ((line[i] != '=' && !is_empty_line(line + i)) || \
	(line[i] != '_' && !ft_isalpha(line[i]) && \
	!is_empty_line(line + i) && line[i] != '='))
		return (ft_error("minishell: export: not a valid identifier\n", shell));
	add_env_var(line, i + 1, shell);
	shell->exit_code = 0;
	return (TRUE);
}
