/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:14:45 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/15 15:13:19 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	is_valid_substring(char **substrings, int j, t_shell *shell)
// {
// 	char	*command;
// 	char	*path;

// 	command = find_command(substrings[j - 1]);
// 	path = get_executable_path(shell, command);
// 	free(command);
// 	if (path)
// 	{
// 		free(path);
// 		return (TRUE);
// 	}
// 	write(2, substrings[j - 1], ft_strlen(substrings[j - 1]));
// 	write(2, ": command not found\n", 20);
// 	shell->exit_code = 127;
// 	free(path);
// 	return (FALSE);
// }

int	split_pipes(char *line, char **substrings)
{
	int		i;
	int		j;
	int		start;
	char	*tmp;

	i = 0;
	j = 0;
	start = i;
	while (line[i])
	{
		if (line[i + 1] == '\0' || \
		(line[i] == '|' && !is_quote(line[i - 1]) && !is_quote(line[i + 1])))
		{
			if (line[i + 1] == '\0')
				tmp = ft_substr(line, start, i - start + 1);
			else
				tmp = ft_substr(line, start, i - start);
			substrings[j++] = ft_strtrim(tmp, " ");
			free(tmp);
			start = i + 1;
		}
		i++;
	}
	return (j);
}

void	pipe_loop(char **substrings, int *tube, int num_cmd, t_shell *shell)
{
	int		pid;
	int		i;
	int		j;
	int		current_pipe;
	int		fd[num_cmd];
	int		old_fd;

	i = 0;
	current_pipe = 0;
	while (i < num_cmd)
	{
		fd[i] = run_heredoc(&substrings[i], &old_fd, shell);
		i++;
	}
	i = 0;
	while (i < num_cmd)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i != num_cmd - 1)
				dup2(tube[current_pipe + 1], 1);
			if (fd[i] != 0)
				dup2(fd[i], 0);
			else if (i != 0)
				dup2(tube[current_pipe - 2], 0);
			j = 0;
			while (j < 2 * (num_cmd))
				close(tube[j++]);
			launch_commands(substrings[i], shell);
			if (fd[i] != 0)
				close(fd[i]);
			exit(EXIT_SUCCESS);
		}
		current_pipe += 2;
		i++;
	}
}

void	launch_pipes(char **substrings, t_shell *shell, int num_commands)
{
	int		*tube;
	int		i;

	tube = malloc(sizeof(int) * (2 * num_commands));
	shell->is_pipe = TRUE;
	i = 0;
	while (i < num_commands)
		pipe(tube + (i++) * 2);
	pipe_loop(substrings, tube, num_commands, shell);
	i = 0;
	while (i < 2 * (num_commands))
		close(tube[i++]);
	i = -1;
	while (++i < num_commands) 
		waitpid(-1, &shell->exit_code, 0);
	shell->exit_code /= 256;
	free(tube);
}

void	manage_pipes(char *line, int pipe_count, t_shell *shell)
{
	int		num_commands;
	char	**substrings;

	substrings = (char **)malloc(sizeof(char *) * (pipe_count + 1 + 1));
	substrings[pipe_count + 1] = NULL;
	num_commands = split_pipes(line, substrings);
	if (num_commands != -1)
		launch_pipes(substrings, shell, num_commands);
	free_double_array(substrings);
	return ;
}
