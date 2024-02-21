/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:58:49 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/21 20:05:34 by akurmyza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_ctrl_c_status;

void ctrl_c_child_process(int signum)
{
	printf("CTRL+C_CHILD\n");
	(void)signum;
	write(1, "\n", 1);
	g_ctrl_c_status = 130;
}

void ctrl_c_heredoc(int signum)
{
	printf("CTRL+C_HEREDOC\n");
	(void)signum;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	g_ctrl_c_status = 130;
}

/*
0. No process running - need redisplay
1. process running - no redisplay needed
*/
void	ctrl_c(int signum)
{
	printf("CTRL+C\n");
	(void)signum;
	g_ctrl_c_status = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	organizer(char *line, t_shell *shell)
{
	int	pipe_count;
	
	if (g_ctrl_c_status == 130)
		g_ctrl_c_status = 0;
	pipe_count = check_pipe(line, '|');
	if (pipe_count == -1 || check_double_symbol(line, '|') > 0)
	{
		write(2, "minishell: syntax error near '|'\n", 33);
		shell->exit_code = 1;
	}
	else if (pipe_count > 0)
		manage_pipes(line, pipe_count, shell);
	else if (pipe_count == 0)
	{
		shell->is_pipe = FALSE;
		run_heredoc(&line, shell);
	}
	free(line);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*line;
	char	*tmp;

	(void)argv;
	(void)argc;
	g_ctrl_c_status = 0;
	save_envp(&shell, envp);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, ctrl_c);
		line = readline("\033[1;38;5;199mminishell $ \033[0m");
		if (line == NULL)
			break ;
		add_history(line);
		tmp = change_env_var(line, &shell);
		organizer(ft_strtrim(tmp, " "), &shell);
		free(tmp);
	}
	if (line)
		free(line);
	free_linked_list(&shell);
	printf("exit\n");
}
