/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:58:49 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/11 18:46:12 by dtolmaco         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*line;

	(void)argv;
	(void)argc;
	shell.exit_code = 0;
	g_ctrl_c_status = 0;
	save_envp(&shell, envp);
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("\033[1;38;5;199mminishell $ \033[0m");
		if (line == NULL)
			break ;
		line = ft_strtrim(line, " ");
		manage_pipes(line, &shell);
		add_history(line);
		g_ctrl_c_status = 0;
	}
	free(line);
	//free_linked_list(&shell);
	printf("exit\n");
}