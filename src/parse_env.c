/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:50:22 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/21 13:25:55 by dtolmaco         ###   ########.fr       */
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

int	check_quotes(char *line)
{
	char	symbol;
	int		i;

	i = 0;
	while(line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			symbol = line[i];
			i++;
			while (line[i] && line[i] != symbol)
				i++;
			if (line[i] != symbol)
			{
				printf("minishell: error while looking for matching quote\n");
				return (FALSE);
			}
		}
		i++;
	}
	return (TRUE);
}

int	print_inside_quotes(char *line, int i, t_env *lst)
{
	char	symbol;

	symbol = line[i];
	if (line[i - 1] == ' ')
		write(1, " ", 1);
	if (symbol == '$')
		return (print_env_var(line, lst, i));
	i++;
	while (line[i] && line[i] != symbol)
	{
		if (symbol == '\"' && line[i] == '$')
			i = print_env_var(line, lst, i);
		else
			write(1, &line[i], 1);
		i++;
	}
	return (i);
}

void	check_input(char *line, t_env *lst)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	line = ft_strtrim(line, " ");
	if (ft_strncmp("-n ", line, 3) == 0)
	{
		line = ft_strtrim(line + 3, " ");
		flag = 1;
	}
	if (!check_quotes(line))
		return ;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"' || line[i] == '$')
			i = print_inside_quotes(line, i, lst);
		else if (line[i] != ' ')
		{
			if (line[i - 1] == ' ')
				write(1, " ", 1);
			write(1, &line[i], 1);
		}
		i++;
	}
	if (!flag)
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