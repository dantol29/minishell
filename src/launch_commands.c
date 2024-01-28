/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:12:31 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/28 11:10:42 by akurmyza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*extract command from the line (only echo with 1 white space after)*/
static char	*extract_command(char *line, int count_letters)
{
	int		i;
	int		j;
	char	*cmd;

	cmd = malloc(sizeof(char) * (count_letters + 2));
	if (!cmd)
		return (NULL);
	i = 0;
	j = 0;
	while (j < count_letters)
	{
		if (!is_quote(line[i]))
			cmd[j++] = line[i];
		i++;
	}
	cmd[count_letters] = '\0';
	return (cmd);
}

/*find command in the line ("echo" .....)*/
char	*find_command(char *line)
{
	int		i;
	int		count_quotes;
	int		count_letters;

	i = 0;
	count_quotes = 0;
	count_letters = 0;
	while (line[i])
	{
		if ((count_quotes == 0 || count_quotes % 2 == 0) && line[i] == ' ')
			break ;
		if (is_quote(line[i]))
		{
			count_quotes++;
			if (count_quotes > 1 && line[i + 1] == ' ')
				return (extract_command(line, count_letters));
		}
		else
			count_letters++;
		i++;
	}
	if (count_quotes % 2 != 0)
	{
		printf("minishell: error while looking for matching quote\n");
		return (NULL);
	}
	return (extract_command(line, count_letters));
}

static int	builtins(char *line, char *command, t_shell *shell)
{
	if (ft_strcmp("echo", command) || ft_strcmp("/bin/echo", command))
		check_echo_line(line, shell);
	else if ((ft_strcmp("env", command) || ft_strcmp("/bin/env", command)) && \
	is_empty_line(skip_command_name(line)))
	{
		print_env(shell->env);
		shell->exit_code = 0;
	}
	else if (ft_strcmp("export", command))
		add_env_var(line, shell);
	else if (ft_strcmp("unset", command))
	{
		unset_env_var(skip_command_name(line), &shell->env);
		shell->exit_code = 0;
	}
	else if (ft_strcmp("pwd", command) || ft_strcmp("/bin/pwd", command))
		pwd(shell);
	else if (ft_strcmp("cd", command))
		cd(line, shell);
	else if (ft_strcmp("exit", command))
		ft_exit(line, shell);
	else
		return (FALSE);
	return (TRUE);
}

void	launch_commands(char *line, t_shell *shell, char **envp)
{
	char	*command;

	command = find_command(line);
	line = run_heredoc(line, command);
	if (command == NULL || line == NULL || is_empty_line(line))
		shell->exit_code = 0;
	else if (!check_quotes(line))
		shell->exit_code = 1;
	else if (builtins(line, command, shell))
		(void)shell->envp;
	else if (launch_exec(line, command, shell, envp) == FALSE)
	{
		shell->exit_code = 127;
		printf("%s: command not found\n", command);
	}
}
