/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:20:15 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/15 16:29:08 by dtolmaco         ###   ########.fr       */
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
			free(tmp->value);
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
		return ;
	if (current && ft_strcmp(current->name, env_name))
	{
		*lst = current->next;
		free(current->name);
		free(current->value);
		free(current);
		return ;
	}
	while (current && !ft_strcmp(current->name, env_name))
	{
		prev = current;
		current = current->next;
	}
	prev->next = current->next;
	free(current->name);
	free(current->value);
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
	char	*tmp;

	value = find_command(line + i);
	if (!value || is_empty_line(value))
	{
		free(value);
		return ;
	}
	tmp = ft_substr(line, 0, i - 1);
	value = change_env_var(value, shell);
	if (find_env_var(tmp, shell->env))
	{
		replace_env_var_value(tmp, value, shell->env);
		free(tmp);
	}
	else
		lstadd_back(&shell->env, create_new_env_node(tmp, value));
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
	if (line[i] == '\0' || line[i] == ' ')
		return (0);
	if ((line[i] != '=' && !is_empty_line(line + i)) || \
	(line[i] != '_' && !ft_isalpha(line[i]) && \
	!is_empty_line(line + i) && line[i] != '='))
		return (ft_error("minishell: export: not a valid identifier\n", shell));
	add_env_var(line, i + 1, shell);
	shell->exit_code = 0;
	return (TRUE);
}
