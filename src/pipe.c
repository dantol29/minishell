/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:14:45 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/28 14:48:41 by akurmyza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_symbol(char *line, char c)
{
	int	i;
	int	status;
	int	count;

	i = 0;
	status = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] != c && line[i] != ' ' && !is_quote(line[i]))
			status = 1;
		if (status == 0 && line[i] == c)
			return (-1);
		if (status == 1 && line[i] == c && !is_quote(line[i - 1]) \
		&& !is_quote(line[i + 1]))
		{
			if (!is_empty_line(line + i + 1))
				count++;
			else
				return (-1);
			status = 0;
		}
		i++;
	}
	//printf("%c count:%d\n", c, count);
	return (count);
}

int	is_valid_substring(char **substrings, int j, t_shell *shell)
{
	char	*command;

	command = find_command(substrings[j - 1]);
	if (access(command, 0) == 0 \
	|| access(ft_strjoin("/bin/", command), 0) == 0)
		return (TRUE);
	printf("%s: command not found\n", substrings[j - 1]);
	shell->exit_code = 127;
	free_double_array(substrings, j);
	return (FALSE);
}

int	split_pipes(char *line, t_shell *shell, char **substrings)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	j = 0;
	start = i;
	while (line[i])
	{
		if (line[i + 1] == '\0' || \
		(line[i] == '|' && !is_quote(line[i - 1]) && !is_quote(line[i + 1])))
		{
			if (line[i + 1] == '\0')
				substrings[j++] = ft_strtrim(ft_substr(line, start, i - start + 1), " ");
			else
			substrings[j++] = ft_strtrim(ft_substr(line, start, i - start), " ");
			if (!is_valid_substring(substrings, j, shell))
				return (-1);
			start = i + 1;
		}
		i++;
	}
	return (j);
}

void	launch_pipes(char **substrings ,t_shell *shell, char **envp)
{
	int		tube[2];
	int		pid;
	int		pid2;


	pipe(tube);
	pid = fork();
	if (pid == 0)
	{
		dup2(tube[1], 1);
		close(tube[0]);
		close(tube[1]);
		launch_commands(substrings[0], shell, envp);
		exit(EXIT_SUCCESS);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		dup2(tube[0], 0);
		close(tube[1]);
		close(tube[0]);
		launch_commands(substrings[1], shell, envp);
		exit(EXIT_SUCCESS);
	}
	close(tube[0]);
	close(tube[1]);
	waitpid(pid, &shell->exit_code, 0);
	waitpid(pid2, &shell->exit_code, 0);
}

void	manage_pipes(char *line, t_shell *shell, char **envp)
{
	int		pipe_count;
	int		split_count;
	//int		i;
	char	**substrings;

	pipe_count = check_symbol(line, '|');
	if (pipe_count <= 0)
	{
		if (pipe_count == -1)
		{
			printf("syntax error near '|'\n");
			return ;
		}
		launch_commands(line, shell, envp);
		return ;
	}
	substrings = (char **)malloc(sizeof(char *) * (pipe_count + 1));
	if (!substrings)
		return ;
	split_count = split_pipes(line, shell, substrings);
	if (split_count == -1)
		return ;
	launch_pipes(substrings, shell, envp);
	// i = 0;
	// while(i < split_count)
	// {
	// 	printf("c:%s\n", substrings[i]);
	// 	launch_commands(substrings[i++], shell, envp);
	// }
	return ;
}