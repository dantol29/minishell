/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:02:31 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/20 13:59:56 by akurmyza         ###   ########.fr       */
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

typedef enum e_bool
{
	TRUE = 1,
	FALSE = 0
}	t_bool;

typedef struct s_shell
{
	char	work_dir[1024];
	char	*username;
	char	**command;
	char	*cmd_path;
	int		pid;
}	t_shell;

#include "../libft/libft.h"



#endif