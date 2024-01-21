/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:50:22 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/21 12:15:25 by dtolmaco         ###   ########.fr       */
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
	int	flag;

	i = 0;
	flag = 1;
	start = 0;
	line = ft_strtrim(line, " ");
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (line[i - 1] == ' ')
				write(1, " ", 1);
			i = print_env_var(line, lst, i);
		}
		else if (line[i] == '\'')
		{
			if (line[i - 1] == ' ')
				write(1, " ", 1);
			i++;
			while (line[i] && line[i] != '\'')
				write(1, &line[i++], 1);
		}
		else if (line[i] == '\"')
		{
			if (line[i - 1] == ' ')
				write(1, " ", 1);
			i++;
			while (line[i] && line[i] != '\"') // TODO: error if a quote is not closed
			{
				if (line[i] == '$')
					i = print_env_var(line, lst, i);
				else
					write(1, &line[i], 1);
				i++;
			}
		}
		else if (line[i] != ' ')
		{
			if (line[i - 1] == ' ')
				write(1, " ", 1);
			write(1, &line[i], 1);
		}
		i++;
	}
	if (ft_strncmp("-n", line, 2) != 0)
		write(1, "\n", 1);
}


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