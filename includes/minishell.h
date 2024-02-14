/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:02:31 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/14 13:41:20 by dtolmaco         ###   ########.fr       */
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
	int		is_pipe;
	char	**current_envp;
	t_env	*env;
}	t_shell;

extern int	g_ctrl_c_status;

void	launch_commands(char *line, t_shell *shell);
char	*find_command(char *line);
char	*change_env_var(char *line, t_shell *shell);

// echo
void	check_echo_line(char *line, t_shell *shell);

// heredoc
char   *run_heredoc(char *line, t_shell *shell);
int		check_double_symbol(char *line, char c);
char 	*remove_heredoc(char *line, char **eof_heredoc);
char 	**save_eof_heredoc(char *line, int count);
void	heredoc_read(char *exit_heredoc, t_shell *shell);

// redirections
int	*redirections(char **line, t_shell *shell);

// utils
int		ft_strcmp(const char *str1, const char *str2);
int		is_empty_line(char *line);
char	*skip_command_name(char *line);
int		is_quote(char c);
int		check_quotes(char *line);
int		count_flags(char *line);

// env
int		print_env_var(char *line, t_shell *shell, int i, int *invalid_var);
void	print_env_var_value(char *variable_name, t_env *lst);
int		find_env_var(char *variable_name, t_env *lst);
void	print_env(t_env *env);
char	*get_env_value(char *variable_name, t_env *lst);

// export and unset
int		export(char *line, t_shell *shell);
t_env	*create_new_env_node(char *name, char *value);
void	replace_env_var_value(char *variable_name, char *new_value, t_env *lst);
void	unset_env_var(char *env_name, t_env **lst);
int		skip_until_char(char *line, int i, char c, char mode);

// cd_pwd_shell
void	cd(char *line, t_shell *shell);
void	ft_exit(char *line, t_shell *shell);
void	pwd(t_shell *shell);

// error
int	ft_error(char *line, t_shell *shell);
void	set_error(char *line, t_shell *shell);

// pipe
int		check_symbol(char *line, char c);
void	manage_pipes(char *line, t_shell *shell);

// path
char *get_executable_path(t_shell *shell, char *cmd);

// execve
int		launch_exec(char *line, char *cmd, t_shell *shell);
char	*get_path(char **splited_path, char *command);

// free
void    free_double_array(char **array);
void	free_linked_list(t_shell *shell);

// save all env variables in a linked list
void	save_envp(t_shell *shell, char **envp);
void	lstadd_back(t_env **lst, t_env *new);
void	update_envp(t_shell *shell);

#endif