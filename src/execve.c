/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:38:13 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/08 12:12:53 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*change_env_var(char *line, t_shell *shell)
{
	int		i;
	int		start;
	char	*var;
	char	*after_var;
	char	*before_var;

	i = 0;
	while (line[i])
	{
		if (line[i++] == '$')
		{
			start = i;
			while (line[i] && line[i] != ' ' && line[i] != '$' && !is_quote(line[i]))
				i++;
			var = ft_substr(line, start, i - start);
			after_var = ft_substr(line, i, ft_strlen(line) - i);
			before_var = ft_substr(line, 0, start - 1);
			if (find_env_var(var, shell->env))
				line = ft_strjoin(before_var, \
				ft_strjoin(get_env_value(var, shell->env), after_var));
			else
			{
				line = ft_strjoin(before_var, after_var);
				i = -1;
			}
		}
	}
	return (line);
}

char	*get_path(char **splited_path, char *command)
{
	char	*cmd;
	char	*temp;

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

static char	**execve_flags(char *line, char *cmd, t_shell *shell)
{
	char	**flags;
	int		i;

	line = skip_command_name(line);
	flags = ft_split(ft_strjoin(ft_strjoin(cmd, " "), line), ' ');
	i = 1;
	while (flags[i])
	{
		flags[i] = find_command(flags[i]);
		if (ft_strcmp(flags[i], "$?"))
			flags[i] = ft_itoa(shell->exit_code);
		else
			flags[i] = change_env_var(flags[i], shell);
		i++;
	}
	return (flags);
}

int	launch_exec(char *line, char *cmd, t_shell *shell)
{
	char	**flags;
	char	*cmd_path;
	char	*path;
	int		pid;

	shell->current_envp = update_envp(shell);
	flags = execve_flags(line, cmd, shell);
	path = get_env_value("PATH", shell->env);
	if (!path)
		return (FALSE);
	cmd_path = get_path(ft_split(path, ':'), cmd);
	if (!cmd_path)
		return (FALSE);
	if (shell->is_pipe == FALSE)
	{
		pid = fork();
		if (pid == 0)
			execve(cmd_path, flags, shell->current_envp);
		waitpid(pid, &shell->exit_code, 0);
		shell->exit_code /= 256;
		return (TRUE);
	}
	else if (shell->is_pipe == TRUE)
			execve(cmd_path, flags, shell->current_envp);
	return (FALSE);
}
