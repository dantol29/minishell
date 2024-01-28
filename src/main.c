/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:58:49 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/28 18:02:37 by akurmyza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_ctrl_c_status;

void	ctrl_c(int signum)
{
	(void)signum;
	g_ctrl_c_status = 130;
	rl_replace_line("\0", 0);
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

char	*change_env_var(char *line, t_shell *shell)
{
	int		i;
	int		start;
	char	*var;
	char	*after_var;
	char	*before_var;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
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
		i++;
	}
	return (line);
}

int	launch_exec(char *line, char *cmd, t_shell *shell, char **envp)
{
	char	**flags;
	char	*cmd_path;
	int		i;
	int		pid;

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
	cmd_path = ft_strjoin("/bin/", cmd);
	if (shell->is_pipe == FALSE)
	{
		if (access(cmd_path, 0) == 0)
		{
			pid = fork();
			if (pid == 0)
				execve(cmd_path, flags, envp);
			waitpid(pid, &shell->exit_code, 0);
			shell->exit_code /= 256;
			return (TRUE);
		}
		else if (access(cmd, 0) == 0)
		{
			pid = fork();
			if (pid == 0)
				execve(cmd, flags, envp);
			waitpid(pid, &shell->exit_code, 0);
			shell->exit_code /= 256;
			return (TRUE);
		}
	}
	else if (shell->is_pipe == TRUE)
	{
		if (access(cmd_path, 0) == 0)
			execve(cmd_path, flags, envp);
		else if (access(cmd, 0) == 0)
			execve(cmd, flags, envp);
	}
	return (FALSE);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*line;
	//int		old_fd;

	(void)argv;
	(void)argc;
	shell.exit_code = 0;
	g_ctrl_c_status = 0;
	save_envp(&shell, envp);
	signal(SIGINT, ctrl_c);
	line = readline("minishell$ ");
	while (line != NULL)
	{
		line = ft_strtrim(line, " ");
		manage_pipes(line, &shell, envp);
		//old_fd = redirections(&line, &shell);
		// if (line && old_fd == 0)
		// 	launch_commands(line, &shell);
		// if (old_fd > 0)
		// {
		// 	dup2(old_fd, 1);
		// 	close(old_fd);
		// }
		add_history(line);
		g_ctrl_c_status = 0;
		line = readline("minishell$ ");
	}
	free(line);
	printf("exit\n");
}
