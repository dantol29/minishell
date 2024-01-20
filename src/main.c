/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:58:49 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/20 16:48:17 by akurmyza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrl_c(int signum)
{
	(void)signum;
}

void	parsing(char *line, t_shell *shell, char **envp)
{
	shell->command = ft_split(line, ' '); // store entered command (use ft_split for flags)
	shell->cmd_path = ft_strjoin("/usr/bin/", shell->command[0]); // if commands whtout path (ls, pwd)
	if (access(shell->cmd_path, 0) == 0)
	{
		shell->pid = fork();
		if (shell->pid == 0)
			execve(shell->cmd_path, shell->command, envp); // execute command (command path, command with flags, env variables)
		waitpid(shell->pid, NULL, 0);
	}
	else if (access(shell->command[0], 0) == 0) // if absolute path (/bin/ls, ../bin/ls)
	{
		shell->pid = fork();
		if (shell->pid == 0)
			execve(shell->command[0], shell->command, envp); // execute command (command path, command with flags, env variables)
		waitpid(shell->pid, NULL, 0);
	}
	else
		printf("minishell: command not found: %s\n", shell->command[0]);
}

int	ft_strcmp(const char *str1, const char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
}

/*
checks if the environment variable is set
*/
int is_env_var(char *variable_name, t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, variable_name) == 0)
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

/*
checks if the environment variable is set
*/
void print_env_var_value(char *variable_name, t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, variable_name) == 0)
		{
			printf("%s",  tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
}

	
/*
	// start checking in both directions, before and after variable    "<--$VAR-->"
	  abcd "$USER    fsdgsd"
	VALID:
		$VAR
		"$VAR"
		"'$VAR"
	
	NOT_VALID:
		$USEr (Small letter) Retturn: empty line 
*/
void check_quotes_print(char *line, int exist, t_env *lst)
{
	// go both directions, before and after variable
	//invalid cases: $USEr. ! Small letter. Retturn:empty line 
	int i;
	int start;

	i = 0;
	start = 0;
	(void)lst;
	while (line[i])
	{
		// if (line[i] == '\'')	// '$TEXT'
		// {
		// 	start = i;
		// 	while( line[i] && line[i] != '\'')
		// 	 	i++;
		// 	printf("%s", ft_substr(line, start, i - start));
		// }
		if (line[i] == '\"')		// "$VAR"
		{
			i++;
			start = i; // +1 skip "
			while (line[i] && line[i] != '\"')
			 	i++;
			if (exist == FALSE)
				write(1, "\n", 1);
			else
				print_env_var_value(ft_substr(line, start + 1, i - start - 1), lst);
		}
		i++;
	}	
}

void check_input(char *line, t_env *lst)
{
	int i;
	//int start;

	i = 0;
	//start = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			//i++;
			//start = i;
			// while (line[i] && (ft_isalnum(line[i]) || line[i] == '_')) // check if valid variable
			// 	i++;
			//if (is_env_var(ft_substr(line, start, i - start), lst)) // check if variable exists
			check_quotes_print(line, TRUE, lst);
			//else
				//check_quotes_print(line, FALSE, lst); // check which quotes and print variable
		}
		i++;
	}
	
}

int	main(int argc, char **argv, char **envp)
{
	t_shell shell;
	char	*line;

	(void)argv;
	(void)argc;
	signal(SIGINT, ctrl_c);
	shell.username = getenv("USER"); // get env variable user
	save_envp(&shell, envp);
	getcwd(shell.work_dir, sizeof(shell.work_dir)); // getcwd - get the current working directory
	printf("%s@minishell %s", shell.username, shell.work_dir);
	line = readline(" $ "); // read user input
	while (line != NULL)
	{
		check_input(line, shell.env);
		//parsing(line, &shell, envp);
		add_history(line);
		printf("%s@minishell %s", shell.username, shell.work_dir);
		line = readline(" $ "); // read user input
	}
	printf("exit\n");
}