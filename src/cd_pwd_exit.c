/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:53:41 by akurmyza          #+#    #+#             */
/*   Updated: 2024/02/11 13:05:13 by dtolmaco         ###   ########.fr       */
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
		write(2, "minishell: exit: too many arguments\n", 36);
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
		write(2, "minishell: exit: numeric argument required\n", 43);
		printf("exit\n");
		shell->exit_code = 2;
		exit(2);
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
	char	*current_dir;
	char	*error;

	current_dir = getcwd(NULL, 0);
	line = skip_command_name(line);
	if (ft_strcmp("-", line))
	{
		printf("%s\n", get_env_value("OLDPWD", shell->env));
		chdir(get_env_value("OLDPWD", shell->env));
	}
	else if (ft_strcmp("~", line) || is_empty_line(line))
		chdir(get_env_value("HOME", shell->env));
	else if (chdir(change_env_var(line, shell)) == -1)
	{
		error = strerror(errno);
		write(2, "cd: ", 4);
		write(2, error, ft_strlen(error));
		write(2, ": ", 2);
		write(2, line, ft_strlen(line));
		write(2, "\n", 1);
		shell->exit_code = 1;
		return ;
	}
	replace_env_var_value("OLDPWD", current_dir, shell->env);
	replace_env_var_value("PWD", getcwd(NULL, 0), shell->env);
	shell->exit_code = 0;
}
