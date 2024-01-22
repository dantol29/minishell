/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:00:47 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/22 17:24:40 by akurmyza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*checks if the environment variable is set*/
void	print_env_var_value(char *variable_name, t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, variable_name) == 0)
		{
			write(1, tmp->value, sizeof(tmp->value));
			break ;
		}
		tmp = tmp->next;
	}
}

/* i++ - to skip $ dollar sign, i-- - to not skip white space between env var*/
int	print_env_var(char *line, t_env *lst, int i)
{
	int	start;

	i++;
	start = i;
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
		i++;
	print_env_var_value(ft_substr(line, start, i - start), lst);
	i--;
	return (i);
}

/*checks if the environment variable exists*/
int find_env_var(char *variable_name, t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, variable_name) == 0)
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

void	replace_env_var_value(char *variable_name, char *new_value, t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, variable_name) == 0)
		{
			tmp->value = new_value;
			break ;
		}
		tmp = tmp->next;
	}
}

void unset_env_var(char *env_name, t_env **lst)
{
	t_env	*current;
	t_env	*prev;

	current = *lst;
	prev = NULL;
	if (!find_env_var(env_name, *lst))
		return ;
    if (current != NULL && ft_strcmp(current->name, env_name) == 0)
	{
        *lst = current->next;
        free(current);
        return  ;
    }

	while(current && ft_strcmp(current->name, env_name) != 0)
	{
		prev = current;
		current = current->next;
	}
    prev->next = current->next;
    free(current);
}

