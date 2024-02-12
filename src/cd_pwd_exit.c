/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:53:41 by akurmyza          #+#    #+#             */
/*   Updated: 2024/02/12 16:56:16 by dtolmaco         ###   ########.fr       */
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
	exit(i);
}

void	pwd(t_shell *shell)
{
	printf("%s\n", getcwd(NULL, 0));
	shell->exit_code = 0;
}

static void	cd_error(char *line, char *current_dir, t_shell *shell)
{
	char	*error;

	error = strerror(errno);
	write(2, "cd: ", 4);
	write(2, error, ft_strlen(error));
	write(2, ": ", 2);
	write(2, line, ft_strlen(line));
	write(2, "\n", 1);
	shell->exit_code = 1;
	free(current_dir);
}

void	cd(char *line, t_shell *shell)
{
	char	*current_dir;

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
		return (cd_error(line, current_dir, shell));
	replace_env_var_value("OLDPWD", current_dir, shell->env);
	replace_env_var_value("PWD", getcwd(NULL, 0), shell->env);
	shell->exit_code = 0;
}
