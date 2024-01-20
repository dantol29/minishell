/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:50:22 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/20 19:25:02 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
checks if the environment variable is set
*/
void	print_env_var_value(char *variable_name, t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, variable_name) == 0)
		{
			write(1, tmp->value, sizeof(tmp->value));
			break ;
		}
		tmp = tmp->next;
	}
}

int	print_env_var(char *line, t_env *lst, int i)
{
	int	start;

	i++; // to skip $ dollar sign
	start = i;
	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
			i++;
	print_env_var_value(ft_substr(line, start, i - start), lst);
	i--; // to not skip white space between env var
	return (i);
}

void	check_input(char *line, t_env *lst)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (line[i])
	{
		if (line[i] == '$')
			i = print_env_var(line, lst, i);
		else if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				write(1, &line[i++], 1);
		}
		else if (line[i] == '\"')
		{
			i++;
			while (line[i] && line[i] != '\"')
			{
				if (line[i] == '$')
					i = print_env_var(line, lst, i);
				else
					write(1, &line[i], 1);
				i++;
			}
		}
		else
			write(1, &line[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

// if (line[i] == '$')
// {
// 	i++;
// 	start = i;
// 	while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
		// check if valid variable
// 		i++;
// 	if (is_env_var(ft_substr(line, start, i - start), lst))
		// check if variable exists
// 		check_quotes_print(line, TRUE, lst);
// 	else
// 		check_quotes_print(line, FALSE, lst);
			// check which quotes and print variable
// }
// else
// 	write(1, &line[i], 1);

// void check_quotes_print(char *line, int exist, t_env *lst)
// {
// 	int i;
// 	int start;

// 	i = 0;
// 	start = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '\'')	// '$TEXT'
// 		{
// 			i++;
// 			start = i;
// 			while( line[i] && line[i] != '\'')
// 					i++;
// 			printf("%s", ft_substr(line, start, i - start));
// 		}
// 		else if (line[i] == '\"')		// "$VAR"
// 		{
// 			i++;
// 			start = i; // +1 skip "
// 			while (line[i] && line[i] != '\"')
// 					i++;
// 			if (exist == FALSE)
// 				write(1, "\n", 1);
// 			else
// 				print_env_var_value(ft_substr(line, start + 1, i - start - 1),
// 		}
// 		i++;
// 	}
// }

// /*
// checks if the environment variable is set
// */
// int	is_env_var(char *variable_name, t_env *lst)
// {
// 	t_env	*tmp;

// 	tmp = lst;
// 	while (tmp)
// 	{
// 		if (ft_strcmp(tmp->name, variable_name) == 0)
// 			return (TRUE);
// 		tmp = tmp->next;
// 	}
// 	return (FALSE);
// }