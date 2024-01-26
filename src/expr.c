/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 17:00:35 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/26 17:47:29 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// int	is_num(char *str)
// {
// 	int	i;
	
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[0] == '-' || str[0] == '+')
// 			i++;
// 		if (!(str[i] >= '0' && str[i] <= '9'))
// 			return (FALSE);
// 		i++;
// 	}
// 	return (TRUE);
// }

// int is_dollar_question(char *str)
// {
// 	 if (ft_strcmp("$?", str))
// 	 	return (TRUE);
// 	return (FALSE);
// }

// void	expr(char *line, t_shell *shell)
// {
// 	char	**expr_line;
// 	int		i;

// 	i = 0;
// 	line = skip_command_name(line);
// 	if (is_empty_line(line))
// 	{
// 		printf("expr: missing operand\n");
// 		shell->exit_code = 2;
// 		return (FALSE);
// 	}
// 	expr_line = ft_split(line, ' ');
// 	if (find_env_var(expr_line[0], shell->env) && is_empty_line)
// 	{
// 		print_env_var_value(expr_line[0]);
// 		return (TRUE);
// 	} 
// 	else if (!ft_strcmp("+", expr_line[0]) && !is_num(expr_line[0]) && !is_dollar_question(expr_line[0]))
// 	{
// 		printf("expr: syntax error\n");
// 		shell->exit_code = 2;
// 		return (FALSE);
// 	}
// 	else
// 	{
		
// 	}
// 	while (expr_line[i])
// 	{
		
// 	}
	
// }