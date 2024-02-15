/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:41:15 by akurmyza          #+#    #+#             */
/*   Updated: 2024/02/15 13:52:41 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_double_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
        free(array[i++]);
    free(array);
}

void free_env_list(t_env *env_list)
{
	t_env *temp;

    while (env_list)
    {
        temp = env_list;
        env_list = env_list->next;
        free(temp->name);
        free(temp->value);
        free(temp);
    }
}

void free_linked_list(t_shell *shell)
{
    free_env_list(shell->env);
	free_double_array(shell->current_envp);
}
