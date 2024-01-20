/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:58:49 by dtolmaco          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/01/20 14:08:48 by akurmyza         ###   ########.fr       */
=======
/*   Updated: 2024/01/20 13:40:30 by dtolmaco         ###   ########.fr       */
>>>>>>> eff8ffbee251884c3f4b1e2e13ea8350ab8b3b17
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

/*
checks if the environment variable is set
return 1 if set, 0 if not
 */
t_bool is_env_var_set()



	
/*
	// start checking in both directions, before and after variable    "<--$VAR-->"
	VALID:
		$VAR
		"$VAR"
		"'$VAR"
	
	NOT_VALID:
		$USEr (Small letter) Retturn: empty line 
*/
int check_brackets(char *line)
{
	// go both directions, before and after variable
	
	//invalid cases: $USEr. ! Small letter. Retturn:empty line 
}

void check_input(char *line)
{
	int i;

	i = 0;

	while (line[i])
	{
		if (line[i] == '$')
		{
			check_brackets( )
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
		parsing(line, &shell, envp);
		add_history(line);
		printf("%s@minishell %s", shell.username, shell.work_dir);
		line = readline(" $ "); // read user input
	}
	printf("exit\n");
}