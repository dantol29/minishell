/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:58:49 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/16 15:52:40 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_ctrl_c_status;

void	ctrl_c(int signum)
{
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

	pipe_count = check_symbol(line, '|');
	if (pipe_count > 0)
		manage_pipes(line, pipe_count, shell);
	else if (pipe_count == 0)
	{
		shell->is_pipe = FALSE;
		run_heredoc(&line, shell);
	}
	else if (pipe_count == -1)
	{
		write(2, "syntax error near '|'\n", 22);
		shell->exit_code = 1;
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
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("\033[1;38;5;199mminishell $ \033[0m");
		if (line == NULL)
			break ;
		add_history(line);
		tmp = change_env_var(line, &shell);
		organizer(ft_strtrim(tmp, " "), &shell);
		free(tmp);
		g_ctrl_c_status = 0;
	}
	if (line)
		free(line);
	free_linked_list(&shell);
	printf("exit\n");
}
