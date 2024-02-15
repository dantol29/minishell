/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 13:53:41 by akurmyza          #+#    #+#             */
/*   Updated: 2024/02/15 11:54:52 by akurmyza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd(t_shell *shell)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	printf("%s\n", cwd);
	free(cwd);
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
	else if (chdir(line) == -1)
		return (cd_error(line, current_dir, shell));
	replace_env_var_value("OLDPWD", current_dir, shell->env);
	replace_env_var_value("PWD", getcwd(NULL, 0), shell->env);
	shell->exit_code = 0;
}
