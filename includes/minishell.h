/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:02:31 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/18 11:14:08 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Standard I/O functions
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
// Process-related functions
# include <sys/types.h>
// wait, waitpid, wait3, wait4
# include <sys/wait.h>
// signal, sigaction, sigemptyset, sigaddset, kill
# include <signal.h>
// Error handling
# include <errno.h>    
# include <fcntl.h>
# include <sys/stat.h>
// Directory-related functions
# include <dirent.h>   
// Terminal-related functions
# include <sys/ioctl.h>
# include <string.h>
# include <pwd.h>
// Terminal I/O functions
# include <termios.h>  
# include <curses.h>
// Terminal capabilities
# include <term.h>    
// Readline library functions     
# include <readline/history.h>
# include <readline/readline.h>
// Error handling
# include <errno.h>
// libft
# include "../libft/libft.h"

# define TRUE 1
# define FALSE 0

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	int		exit_code;
	int		is_pipe;
	char	**current_envp;
	t_env	*env;
}	t_shell;

// global variable to store ctrl+c exit code (130)
extern int	g_ctrl_c_status;

// launch commands (decides what to execute)
void	launch_commands(char *line, t_shell *shell);
char	*find_command(char *line);

// cd pwd (cd and pwd builtins)
void	cd(char *line, t_shell *shell);
void	pwd(t_shell *shell);

// check symbol (counts how many valid symbols the line has)
int		check_symbol(char *line, char c);
int		check_double_symbol(char *line, char c);
int		is_quote(char c);

// env variables (changes env variables in the line)
char	*change_env_var(char *line, t_shell *shell);

// echo (echo builtin)
void	check_echo_line(char *line, t_shell *shell);

// heredoc (<< redirection)
int		run_heredoc(char **line, t_shell *shell);
int		*heredoc_in_pipe(char **substrings, int num_cmd, t_shell *shell);

// heredoc parsing (<< redirection)
char	**save_eof_heredoc(char *line, int count);
char	*remove_heredoc(char *line, char **eof_heredoc);
void	heredoc_read(char *exit_heredoc, t_shell *shell);
char	*get_line_without_heredoc(char *line, int start_heredoc, int i);

// redirections (< input, > output, >> output append redirections)
int		*redirections(char **line, t_shell *shell);
char	*extract_input_output(char *line, int i);
char	*remove_redir(char *line, int i);

// utils (useful functions)
int		is_empty_line(char *line);
int		check_quotes(char *line);
int		count_flags(char *line);
void	dup_output(int *tube, int current_pipe, int num_cmd, int i);
int		ft_strcmp(const char *str1, const char *str2);	

// env (manipulations with env variables)
char	*skip_env_var(char *before_var, char *after_var, int *i);
int		find_env_var(char *variable_name, t_env *lst);
void	print_env(t_env *env);
char	*get_env_value(char *variable_name, t_env *lst);

// export and unset (builtins)
int		export(char *line, t_shell *shell);
t_env	*create_new_env_node(char *name, char *value);
void	replace_env_var_value(char *variable_name, char *new_value, t_env *lst);
void	unset_env_var(char *env_name, t_env **lst);

// error (error handling)
int		ft_error(char *line, t_shell *shell);
int		set_error(char *line, t_shell *shell);

// pipe ('|')
void	manage_pipes(char *line, int pipe_count, t_shell *shell);

// path (find PATH for execve)
char	*get_executable_path(t_shell *shell, char *cmd);

// execve (for non-builtins (ls, wc, cat ...))
int		launch_exec(char *line, char *cmd, t_shell *shell);

// exit (builtin)
void	ft_exit(char *line, t_shell *shell);

// free (free heap allocated memory)
void	free_double_array(char **array);
void	free_linked_list(t_shell *shell);

// save_envp (save all env variables in a linked list)
void	save_envp(t_shell *shell, char **envp);
void	lstadd_back(t_env **lst, t_env *new);
void	update_envp(t_shell *shell);

// file (file manipulation)
int		open_file(char **filenames, char *redir, int i, t_shell *shell);
char	*get_filename(char **filenames, char *tmp, int *count, int *i);

// skip (utils to skip or delete from the line)
char	*skip_command_name(char *line);;
int		skip_until_char(char *line, int i, char c, char mode);
char	*skip_flag_n(char *line, int j);

#endif