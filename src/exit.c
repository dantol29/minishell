/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:54:21 by akurmyza          #+#    #+#             */
/*   Updated: 2024/02/15 11:55:04 by akurmyza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_error(char	*exit_arg)
{
	write(2, "minishell: exit: numeric argument required\n", 43);
	printf("exit\n");
	free(exit_arg);
	exit(2);
}

void	ft_exit(char *line, t_shell *shell)
{
	char	*exit_arg;
	int		i;

	line = skip_command_name(line);
	exit_arg = change_env_var(find_command(line), shell);
	i = 0;
	if (exit_arg[i] == '-' || exit_arg[i] == '+')
		i++;
	while (exit_arg[i] && ft_isdigit(exit_arg[i]))
		i++;
	if (exit_arg[i])
		exit_error(exit_arg);
	printf("exit\n");
	i = ft_atoi(exit_arg);
	free(exit_arg);
	free(line);
	exit(i);
}
