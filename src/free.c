/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:41:15 by akurmyza          #+#    #+#             */
/*   Updated: 2024/02/13 13:36:14 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void free_double_array(char **array, int size)
{
	(void)size;
    if (array == NULL)
        return;
    for (int i = 0; array[i] != NULL; ++i)
    {
        free(array[i]);
    }

    //free(array);
}

void free_env_list(t_env *env_list)
{
    while (env_list != NULL)
    {
        t_env *temp = env_list;
        env_list = env_list->next;

        free(temp->name);
        free(temp->value);
        free(temp);
    }
}

void free_linked_list(t_shell *shell)
{
    free_env_list(shell->env);
    //free(shell->current_envp);
    //free(shell);
	exit(0);
}

// void	free_linked_list(t_shell *shell)
// {
// 	t_env	*next_node;
// 	t_env	*current;

// 	if (shell->env == NULL)
// 		return ;
// 	current = shell->env;
// 	while (current)
// 	{
// 		next_node = current->next;
// 		if (current->value)
// 		{
// 			printf("%s\n", current->value);
// 			free(current->value);
// 		}
// 		if (current->name)
// 		{
// 			printf("%s\n", current->name);
// 			free(current->name);
// 		}
// 		current = next_node;
// 	}
// 	shell->env = NULL;
// }
