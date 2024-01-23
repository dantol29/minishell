/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:12:31 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/23 11:34:36 by akurmyza         ###   ########.fr       */
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

void	print_env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}

t_env	*create_new_env_node(char *name, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->name = name;
	new->value = value;
	new->next = NULL;
	return (new);
}

int	add_env_var(char *line, t_env *env)
{
	char	*name;
	char	*value;
	int		len;
	int		i;

	line = skip_command_name(line);
	i = 0;
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
		i++;
	if (line[i++] != '=' || i == 0)
		return (FALSE);
	len = i;
	while (line[len] && line[len] != ' ')
		len++;
	if (!(is_empty_line(line + len)))
		return (FALSE);
	name = ft_substr(line, 0, i - 1);
	value = ft_substr(line, i, len);
	if (find_env_var(name, env))
		replace_env_var_value(name, value, env);
	else
		lstadd_back(&env, create_new_env_node(name, value));
	return (TRUE);
}

void	launch_commands(char *line, t_shell *shell, char **envp)
{
	char	*command;

	(void)envp;
	line = ft_strtrim(line, " ");
	command = find_command(line);
	if (command == NULL || is_empty_line(line))
		return ;
	if (check_pipe_symbol(line))
		call_pipe_function();
	else if (ft_strcmp("echo", command) == 0 || ft_strcmp("/bin/echo", command) == 0)
		check_echo_line(line, shell->env);
	else if (ft_strcmp("env", command) == 0 || ft_strcmp("/bin/env", command) == 0)
		print_env(shell->env);
	else if (ft_strcmp("export", command) == 0)
	{
		if (!add_env_var(line, shell->env))
			printf("error while creating a new variable\n");
	}
	else if (ft_strcmp("unset", command) == 0)
		unset_env_var(skip_command_name(line), &shell->env);
	else if (ft_strcmp("pwd", command) == 0 || ft_strcmp("/bin/pwd", command) == 0)
		printf("%s\n", getcwd(NULL, 0));
	else if (launch_exec(line, shell, envp) == FALSE)
		printf("command not found\n");
}
