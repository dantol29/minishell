/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:40:45 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/12 17:51:18 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_executable_path(t_shell *shell, char *cmd)
{
	char	*path;
	char	*cmd_path;

	path = get_env_value("PATH", shell->env);
	if (!path)
		return (NULL);
	cmd_path = get_path(ft_split(path, ':'), cmd);
	if (!cmd_path)
		return (NULL);
	return (cmd_path);
}

char	*get_path(char **splited_path, char *command)
{
	char	*cmd;
	char	*temp;

	if (opendir(command))
		return (NULL);
	if (access(command, X_OK) == 0)
		return (command);
	while (*splited_path)
	{
		temp = ft_strjoin(*splited_path, "/");
		cmd = ft_strjoin(temp, command);
		free(temp);
		if (access(cmd, X_OK) == 0)
			return (cmd);
		free(cmd);
		splited_path++;
	}
	return (NULL);
}
