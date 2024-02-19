/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:40:45 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/19 16:47:03 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_path(char **splited_path, char *command)
{
	char	*cmd;
	char	*temp;
	int		i;

	if (opendir(command))
		return (NULL);
	i = 0;
	while (splited_path[i])
	{
		temp = ft_strjoin(splited_path[i], "/");
		cmd = ft_strjoin(temp, command);
		free(temp);
		if (access(cmd, X_OK) == 0)
			return (cmd);
		free(cmd);
		i++;
	}
	return (NULL);
}

char	*get_executable_path(t_shell *shell, char *cmd)
{
	char	*path;
	char	*cmd_path;
	char	**splitted_path;

	if (access(cmd, X_OK) == 0)
	{
		cmd = ft_substr(cmd, 0, ft_strlen(cmd));
		return (cmd);
	}
	path = get_env_value("PATH", shell->env);
	if (!path)
		return (NULL);
	splitted_path = ft_split(path, ':');
	cmd_path = get_path(splitted_path, cmd);
	free_double_array(splitted_path);
	if (!cmd_path)
		return (NULL);
	return (cmd_path);
}
