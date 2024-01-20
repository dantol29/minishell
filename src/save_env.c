/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 13:35:22 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/20 13:39:03 by dtolmaco         ###   ########.fr       */
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
	t_env	*new;

	shell->env = NULL;
	while (*envp)
	{
		new = lstnew(*envp);
		lstadd_back(&shell->env, new);
		envp++;
	}
	//printf("list size: %d\n", lstsize(shell->env));
}