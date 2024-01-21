/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:12:31 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/21 19:28:13 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*extract command from the line (only echo with 1 white space after)*/
static char	*extract_command(char *line, int count_letters)
{
	int		i;
	char	*cmd;

	cmd = malloc(sizeof(char) * (count_letters + 2));
	if (!cmd)
		return (NULL);
	i = 0;
	count_letters = 0;
	while (line[i] && line[i] != ' ')
	{
		if (line[i] != '\"')
			cmd[count_letters++] = line[i];
		i++;
	}
	if (line[i] == ' ')
		cmd[count_letters++] = ' ';
	cmd[count_letters] = '\0';
	return (cmd);
}

/*find command in the line ("echo" .....)*/
static char	*find_command(char *line)
{
	int		i;
	int		count_quotes;
	int		count_letters;

	i = 0;
	count_quotes = 0;
	count_letters = 0;
	while (line[i] && line[i] != ' ')
	{
		if (line[i] == '\"')
			count_quotes += 1;
		else
			count_letters += 1;
		i++;
	}
	if (count_quotes % 2 != 0)
	{
		printf("minishell: error while looking for matching quote\n");
		return (NULL);
	}
	return (extract_command(line, count_letters));
}

void	launch_commands(char *line, t_shell *shell, char **envp)
{
	char	*command;

	line = ft_strtrim(line, " ");
	command = find_command(line);
	if (command == NULL || is_empty_line(line))
		return ;
	if (check_pipe_symbol(line))
		call_pipe_function();
	else if (ft_strcmp("echo ", command) == 0 \
	|| ft_strcmp("echo", command) == 0)
		check_echo_line(line, shell->env);
	else if (access(ft_strjoin("/usr/bin/", command), 0) == 0)
		launch_exec(line, shell, envp);
	else
		printf("command not found\n");
}
