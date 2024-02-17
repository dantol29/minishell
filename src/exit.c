/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 11:54:21 by akurmyza          #+#    #+#             */
/*   Updated: 2024/02/16 12:59:51 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	exit_error(char	*exit_arg)
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
	line = skip_command_name(line);
	if (line[i] == ' ')
		line += 1;
	if (!is_empty_line(line + 1))
	{
		write(2, "minishell: exit: too many arguments\n", 37);
		shell->exit_code = 1;
		return (free(exit_arg));
	}
	if (exit_arg[i] == '-' || exit_arg[i] == '+')
		i++;
	while (exit_arg[i] && ft_isdigit(exit_arg[i]))
		i++;
	if (exit_arg[i])
		exit_error(exit_arg);
	printf("exit\n");
	i = ft_atoi(exit_arg);
	free(exit_arg);
	exit(i);
}
