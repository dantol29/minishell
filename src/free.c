/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:41:15 by akurmyza          #+#    #+#             */
/*   Updated: 2024/02/09 08:45:45 by akurmyza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_double_array(char **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	ft_error(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

void	free_linked_list(t_shell *shell)
{

	t_env	*next_node;
	t_env	*current;

	if (shell->env == NULL)
		return ;
	current = shell->env;
	while (current)
	{
		next_node = current->next;
		free(current->value);
		free(current->name);
		current = next_node;
	}
	shell->env = NULL;
}