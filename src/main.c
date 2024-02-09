/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 16:58:49 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/09 08:49:11 by akurmyza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_ctrl_c_status;

void	ctrl_c(int signum)
{
	(void)signum;
	g_ctrl_c_status = 130;
	rl_replace_line("\0", 0);
	write(STDERR_FILENO, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
	return ;
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
	line = readline("minishell$ ");
	while (line != NULL)
	{
		line = ft_strtrim(line, " ");
		manage_pipes(line, &shell);
		add_history(line);
		g_ctrl_c_status = 0;
		line = readline("minishell$ ");
	}
	free(line);
	free_linked_list(&shell);
	printf("exit\n");
}
