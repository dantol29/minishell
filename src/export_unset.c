/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:20:15 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/26 14:08:44 by akurmyza         ###   ########.fr       */
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
		return ;
	if (current != NULL && ft_strcmp(current->name, env_name))
	{
		*lst = current->next;
		free(current);
		return ;
	}
	while (current && !ft_strcmp(current->name, env_name))
	{
		prev = current;
		current = current->next;
	}
	prev->next = current->next;
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

int	add_env_var(char *line, t_shell *shell)
{
	char	*name;
	char	*value;
	int		len;
	int		i;

	line = skip_command_name(line);
	if (is_empty_line(line))
	{
		print_env(shell->env);
		return (TRUE);
	}
	i = 0;
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
		i++;
	if (line[i++] != '=')
		return (FALSE);
	len = i;
	while (line[len] && line[len] != ' ')
		len++;
	name = ft_substr(line, 0, i - 1);
	value = ft_substr(line, i, len);
	if (find_env_var(name, shell->env))
		replace_env_var_value(name, value, shell->env);
	else
		lstadd_back(&shell->env, create_new_env_node(name, value));
	shell->exit_code = 0;
	return (TRUE);
}
