/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:53:41 by akurmyza          #+#    #+#             */
/*   Updated: 2024/01/24 15:34:53 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd(char *line, t_env *env)
{
	int	status;

	status = 0;
	line = skip_command_name(line);
	if (ft_strcmp("-", line))
	{
		printf("%s\n", get_env_value("OLDPWD", env));
		chdir(get_env_value("OLDPWD", env));
		status = 1;
	}
	replace_env_var_value("OLDPWD", getcwd(NULL, 0), env);
	if (ft_strcmp("~", line) || is_empty_line(line))
		chdir(get_env_value("HOME", env));
	else if (status == 0)
	{
		if (chdir(line) == -1)
		{
			printf("cd: %s: %s\n", strerror(errno), line);
			return ;
		}
	}
	replace_env_var_value("PWD", getcwd(NULL, 0), env);
}
