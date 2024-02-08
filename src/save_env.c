/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:35:22 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/08 09:52:20 by akurmyza         ###   ########.fr       */
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
	new->value = content + i + 1;
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

/*save enviromental variables in a linked list*/
void	save_envp(t_shell *shell, char **envp)
{
	int		i;
	t_env	*new;

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
		shell->current_envp[i] = envp[i];
		i++;
	}
}
