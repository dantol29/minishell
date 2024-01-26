/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:53:41 by akurmyza          #+#    #+#             */
/*   Updated: 2024/01/26 14:13:48 by akurmyza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd(char *line, t_shell *shell)
{
	int	status;

	status = 0;
	line = skip_command_name(line);
	if (ft_strcmp("-", line))
	{
		printf("%s\n", get_env_value("OLDPWD", shell->env));
		chdir(get_env_value("OLDPWD", shell->env));
		status = 1;
	}
	replace_env_var_value("OLDPWD", getcwd(NULL, 0), shell->env);
	if (ft_strcmp("~", line) || is_empty_line(line))
		chdir(get_env_value("HOME", shell->env));
	else if (status == 0)
	{
		if (chdir(line) == -1)
		{
			printf("cd: %s: %s\n", strerror(errno), line);
			return ;
		}
	}
	replace_env_var_value("PWD", getcwd(NULL, 0), shell->env);
	shell->exit_code = 0;
}
