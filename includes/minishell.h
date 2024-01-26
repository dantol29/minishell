/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:02:31 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/26 14:36:47 by akurmyza         ###   ########.fr       */
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
#include "../libft/libft.h"

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
	int		exit_code;
	t_env	*env;
}	t_shell;

extern int	g_ctrl_c_status;

void	launch_commands(char *line, t_shell *shell, char **envp);
int		launch_exec(char *line, char *cmd, char **envp, t_shell *shell);
char	*find_command(char *line);

// echo
void	check_echo_line(char *line, t_shell *shell);

// heredoc
char   *run_heredoc(char *line, char *command);
int		is_heredoc(char *line);

// utils
int		ft_strcmp(const char *str1, const char *str2);
int		is_empty_line(char *line);
char	*skip_command_name(char *line);
int		is_quote(char c);
int		check_quotes(char *line);

// env
int		print_env_var(char *line, t_shell *shell, int i, int *invalid_var);
void	print_env_var_value(char *variable_name, t_env *lst);
int		find_env_var(char *variable_name, t_env *lst);
void	print_env(t_env *env);
char	*get_env_value(char *variable_name, t_env *lst);

// export and unset
int		add_env_var(char *line, t_shell *shell);
t_env	*create_new_env_node(char *name, char *value);
void	replace_env_var_value(char *variable_name, char *new_value, t_env *lst);
void	unset_env_var(char *env_name, t_env **lst);

// cd
void	cd(char *line, t_shell *shell);

// pipe
int		check_pipe_symbol(char *line);
char	*split_pipes(char *line);

// free
void    free_double_array(char **array, int size);

// save all env variables in a linked list
void	save_envp(t_shell *shell, char **envp);
void	lstadd_back(t_env **lst, t_env *new);

// gnl
char	*get_next_line(int fd);

#endif