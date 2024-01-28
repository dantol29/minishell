/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 10:41:15 by akurmyza          #+#    #+#             */
/*   Updated: 2024/01/28 18:26:12 by akurmyza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_double_array(char **array, int size)
{
	int i;

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
