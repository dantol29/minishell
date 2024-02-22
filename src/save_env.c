/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:35:22 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/22 11:38:52 by akurmyza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*add new linked list element*/
t_env	*lstnew(char *content)
{
	int		i;
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (content[i] != '=')
		i++;
	new->name = ft_substr(content, 0, i);
	new->value = ft_strdup(content + i + 1);
	new->next = NULL;
	return (new);
}

/*count the size of a linked lists*/
int	lstsize(t_env *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}

/*add element to the end of a linked list*/
void	lstadd_back(t_env **lst, t_env *new)
{
	t_env	*last;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}

void	update_envp(t_shell *shell)
{
	int		i;
	char	**new;
	char	*tmp_join;
	char	*tmp_join2;
	t_env	*tmp;

	i = lstsize(shell->env);
	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
		return ;
	new[i] = NULL;
	i = 0;
	tmp = shell->env;
	while (tmp)
	{
		tmp_join2 = ft_strjoin("=", tmp->value);
		tmp_join = ft_strjoin(tmp->name, tmp_join2);
		free(tmp_join2);
		new[i++] = ft_strdup(tmp_join);
		free(tmp_join);
		tmp = tmp->next;
	}
	free_double_array(shell->current_envp);
	shell->current_envp = new;
}

/*save enviromental variables in a linked list*/
void	save_envp(t_shell *shell, char **envp)
{
	int		i;
	t_env	*new;

	shell->exit_code = 0;
	shell->is_pipe = FALSE;
	i = 0;
	while (envp[i])
		i++;
	shell->current_envp = malloc(sizeof(char *) * (i + 1));
	if (!shell->current_envp)
		return ;
	shell->env = NULL;
	i = 0;
	while (envp[i])
	{
		new = lstnew(envp[i]);
		lstadd_back(&shell->env, new);
		shell->current_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	shell->current_envp[i] = NULL;
}
