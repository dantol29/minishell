/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:02:31 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/23 15:39:58 by akurmyza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H


// Standard I/O functions
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// Process-related functions
#include <sys/types.h>
// wait, waitpid, wait3, wait4
#include <sys/wait.h>
// signal, sigaction, sigemptyset, sigaddset, kill
#include <signal.h>
// Error handling
#include <errno.h>    
#include <fcntl.h>
#include <sys/stat.h>
// Directory-related functions
#include <dirent.h>   
// Terminal-related functions
#include <sys/ioctl.h>
#include <string.h>
#include <pwd.h>
// Terminal I/O functions
#include <termios.h>  
#include <curses.h>
// Terminal capabilities
#include <term.h>    
// Readline library functions     
#include <readline/history.h>
#include <readline/readline.h>
// Error handling
#include <errno.h>
#define TRUE 1
#define FALSE 0

typedef struct s_env
{
	char		*name;
	char		*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	char	work_dir[1024];
	char	*username;
	char	**command;
	char	*cmd_path;
	int		pid;
	t_env	*env;
}	t_shell;

#include "../libft/libft.h"

void	save_envp(t_shell *shell, char **envp);
void	check_echo_line(char *line, t_env *lst);
void	launch_commands(char *line, t_shell *shell, char **envp);
int		launch_exec(char *line, t_shell *shell, char **envp);

// utils
int		ft_strcmp(const char *str1, const char *str2);
int		is_empty_line(char *line);
char	*skip_command_name(char *line);
void	lstadd_back(t_env **lst, t_env *new);

// env
int		print_env_var(char *line, t_env *lst, int i, int *invalid_var);
void	print_env_var_value(char *variable_name, t_env *lst);
int		find_env_var(char *variable_name, t_env *lst);
void	replace_env_var_value(char *variable_name, char *new_value, t_env *lst);
void	unset_env_var(char *env_name, t_env **lst);

// pipe
int		check_pipe_symbol(char *line);
void	call_pipe_function(void);

#endif