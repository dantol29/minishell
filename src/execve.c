/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:38:13 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/15 16:18:58 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*skip_env_var(char *before_var, char *after_var, int *i)
{
	*i = -1;
	return (ft_strjoin(before_var, after_var));
}

char	*exec_env_value(char *before_v, char *v, char *after_v, t_shell *shell)
{
	char	*value;
	char	*tmp;

	if (ft_strcmp(v, "?"))
	{
		if (g_ctrl_c_status == 130)
			tmp = ft_itoa(130);
		else
			tmp = ft_itoa(shell->exit_code);
		value = ft_strjoin(tmp, after_v);
		free(tmp);
	}
	else
	{
		tmp = ft_strjoin(get_env_value(v, shell->env), after_v);
		value = ft_strdup(tmp);
		free(tmp);
	}
	tmp = ft_strjoin(before_v, value);
	free(value);
	return (tmp);
}

char	*change_env_var(char *line, t_shell *shell)
{
	int		i;
	int		start;
	char	*var;
	char	*after_var;
	char	*before_var;
	char 	*tmp;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			i = skip_until_char(line, i, '\'', 2);
		if (line[i] == '$' && (is_quote(line[i + 1]) || line[i + 1] == ' ' || line[i + 1] == '\0'))
			i++;
		if (line[i] == '$' && line[i + 1] == '?')
		{
			before_var =  ft_substr(line, 0, i);
			var =  ft_substr(line, i + 1, 1);
			after_var =  ft_substr(line, i + 2, ft_strlen(line) - i + 1);
			free(line);
			line = exec_env_value(before_var, var, after_var, shell);
			free(before_var);
			free(var);
			free(after_var);
			i += 2;
		}
		else if (line[i++] == '$')
		{
			start = i;
			while (line[i] && line[i] != ' ' && \
			line[i] != '$' && !is_quote(line[i]))
				i++;
			var = ft_substr(line, start, i - start);
			after_var = ft_substr(line, i, ft_strlen(line) - i);
			before_var = ft_substr(line, 0, start - 1);
			if (find_env_var(var, shell->env) || ft_strcmp(var, "?"))
			{
				free(line);
				line = exec_env_value(before_var, var, after_var, shell);
			}
			else
			{
				free(line);
				line = skip_env_var(before_var, after_var, &i);
			}
			free(before_var);
			free(var);
			free(after_var);
		}
	}
	tmp = ft_strdup(line);
	free(line);
	return (tmp);
}

static char	**execve_flags(char *line, char *cmd, t_shell *shell)
{
	char	**flags;
	int		flag_count;
	int		i;

	line = skip_command_name(line);
	flag_count = count_flags(line);
	flags = malloc(sizeof(char *) * (flag_count + 2));
	flags[0] = ft_strdup(cmd);
	i = 1;
	while (i <= flag_count)
	{
		flags[i] = find_command(line);
		line = skip_command_name(line);
		if (ft_strcmp(flags[i], "$?") && !ft_strcmp(cmd, "awk"))
			flags[i] = ft_itoa(130);
		else if (!ft_strcmp(cmd, "awk"))
			flags[i] = change_env_var(flags[i], shell);
		i++;
	}
	flags[flag_count + 1] = NULL;
	return (flags);
}

// void	child_ctrl_c(int signum)
// {
// 	(void)signum;
// 	g_ctrl_c_status = 130;
// 	//write(1, "\n", 1);
// 	//rl_on_new_line();
// 	//rl_replace_line("", 0);
// 	//rl_redisplay();
// }

int	launch_exec(char *line, char *cmd, t_shell *shell)
{
	char	**flags;
	char	*cmd_path;
	int		pid;

	update_envp(shell);
	flags = execve_flags(line, cmd, shell);
	cmd_path = get_executable_path(shell, cmd);
	if (!cmd_path)
	{
		free_double_array(flags);
		return (FALSE);
	}
	pid = fork();
	if (pid == 0)
		execve(cmd_path, flags, shell->current_envp);
	waitpid(pid, &shell->exit_code, 0);
	shell->exit_code /= 256;
	free(cmd_path);
	free_double_array(flags);
	if (shell->is_pipe == TRUE)
		exit(shell->exit_code);
	return (TRUE);
}
