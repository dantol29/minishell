/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:58:49 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/22 11:37:41 by akurmyza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_ctrl_c_status;

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
		line = readline("\033[1;38;5;201;1m\033[4mminishell 🐱‍💻 \033[0m");
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
