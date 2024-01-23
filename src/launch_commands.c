/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:12:31 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/23 16:22:28 by akurmyza         ###   ########.fr       */
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

char	*get_env_value(char *variable_name, t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, variable_name))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	cd(char *line, t_env *env)
{
	int	status;

	status = 0;
	line = skip_command_name(line);
	if (ft_strcmp("-", line))
	{
		printf("%s\n", get_env_value("OLDPWD", env));
		chdir(get_env_value("OLDPWD", env));
		status = 1;
	}
	replace_env_var_value("OLDPWD", getcwd(NULL, 0), env);
	if (ft_strcmp("~", line) || is_empty_line(line))
		chdir(get_env_value("HOME", env));
	else if (status == 0)
	{
		if (chdir(line) == -1)
		{
			printf("cd: %s: %s\n", strerror(errno) ,line);
			return ;
		}
	}
	replace_env_var_value("PWD", getcwd(NULL, 0), env);
}

void	launch_commands(char *line, t_shell *shell, char **envp)
{
	char	*command;

	(void)envp;
	line = ft_strtrim(line, " ");
	command = find_command(line);
	if (is_heredoc (line)
		run_heredoc(line);
	if (command == NULL || is_empty_line(line))
		return ;
	if (check_pipe_symbol(line))
		call_pipe_function();
	else if (ft_strcmp("echo", command) || ft_strcmp("/bin/echo", command))
		check_echo_line(line, shell->env);
	else if (ft_strcmp("env", command) || ft_strcmp("/bin/env", command))
		print_env(shell->env);
	else if (ft_strcmp("export", command))
	{
		if (!add_env_var(line, shell->env))
			printf("error while creating a new variable\n");
	}
	else if (ft_strcmp("unset", command))
		unset_env_var(skip_command_name(line), &shell->env);
	else if (ft_strcmp("pwd", command) || ft_strcmp("/bin/pwd", command))
		printf("%s\n", getcwd(NULL, 0));
	else if (ft_strcmp("cd", command))
		cd(line, shell->env);
	else if (ft_strcmp("exit", command))
	{
		printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	else if (launch_exec(line, shell, envp) == FALSE)
		printf("%s: command not found\n", command);
}
