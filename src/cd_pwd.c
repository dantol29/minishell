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

static void	cd_error(char *line, char *path, char *current_dir, t_shell *shell)
{
	// char	*error;

	// error = strerror(errno);
	write(2, "cd: ", 4);
	write(2, line, ft_strlen(line));
	shell->exit_code = 1;
	free(current_dir);
	free(path);
}

void	cd(char *line, t_shell *shell)
{
	char	*current_dir;
	char	*path;

	current_dir = getcwd(NULL, 0);
	line = skip_command_name(line);
	path = find_command(line);
	line = skip_command_name(line);
	if (line[0] == ' ')
		line += 1;
	if (!is_empty_line(line + 1))
		return (cd_error("too many arguments\n", path, current_dir, shell));
	if (ft_strcmp("-", path))
	{
		printf("%s\n", get_env_value("OLDPWD", shell->env));
		chdir(get_env_value("OLDPWD", shell->env));
	}
	else if (ft_strcmp("~", path) || is_empty_line(path))
		chdir(get_env_value("HOME", shell->env));
	else if (chdir(path) == -1)
		return (cd_error("No such file or directory\n", \
		path, current_dir, shell));
	replace_env_var_value("OLDPWD", current_dir, shell->env);
	replace_env_var_value("PWD", getcwd(NULL, 0), shell->env);
	shell->exit_code = 0;
	free(path);
}
