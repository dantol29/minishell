/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:20:15 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/11 13:06:58 by dtolmaco         ###   ########.fr       */
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

int	skip_until_char(char *line, int i, char c, char mode)
{
	if (mode == 0)
	{
		while (line[i] && line[i] != c)
			i++;
	}
	else if (mode == 1)
	{
		while (line[i] && line[i] == c)
			i++;
	}
	else if (mode == 2)
	{
		i++;
		while (line[i] && line[i] != c)
			i++;
	}
	return (i);
}

int	add_env_var(char *line, t_shell *shell)
{
	char	*value;
	int		i;

	line = skip_command_name(line);
	if (is_empty_line(line))
	{
		print_env(shell->env);
		return (TRUE);
	}
	i = 0;
	if (line[0] != '_' && !ft_isalpha(line[0]))
	{
		write(2, "minishell: export: not a valid identifier\n", 42);
		shell->exit_code = 1;
		return (FALSE);
	}
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
		i++;
	if ((line[i] != '=' && !is_empty_line(line + i)) ||\
	(line[i] != '_' && !ft_isalpha(line[i]) && !is_empty_line(line + i) && line[i] != '='))
	{
		write(2, "minishell: export: not a valid identifier\n", 42);
		shell->exit_code = 1;
		return (FALSE);
	}
	i++;
	value = find_command(line + i);
	if (!value || is_empty_line(value))
	{
		shell->exit_code = 0;
		return (FALSE);
	}
	if (find_env_var(ft_substr(line, 0, i - 1), shell->env))
		replace_env_var_value(ft_substr(line, 0, i - 1), value, shell->env);
	else
		lstadd_back(&shell->env, \
		create_new_env_node(ft_substr(line, 0, i - 1), value));
	shell->exit_code = 0;
	return (TRUE);
}
