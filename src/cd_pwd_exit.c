/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:53:41 by akurmyza          #+#    #+#             */
/*   Updated: 2024/01/27 11:41:06 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(char *line, t_shell *shell)
{
	char	*exit_arg;
	int		i;

	line = skip_command_name(line);
	exit_arg = find_command(line);
	line = skip_command_name(line);
	if (!is_empty_line(line))
	{
		printf("minishell: exit: too many arguments\n");
		shell->exit_code = 1;
		return ;
	}
	i = 0;
	if (exit_arg[i] == '-' || exit_arg[i] == '+')
		i++;
	while (exit_arg[i] && ft_isdigit(exit_arg[i]))
		i++;
	if (exit_arg[i] && !ft_isdigit(exit_arg[i]))
	{
		printf("minishell: exit: numeric argument required\n");
		shell->exit_code = 1;
		return ;
	}
	printf("exit\n");
	exit(ft_atoi(exit_arg));
}

void	pwd(t_shell *shell)
{
	printf("%s\n", getcwd(NULL, 0));
	shell->exit_code = 0;
}

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
