/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:50:22 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/21 17:24:20 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
checks if the environment variable is set
*/
static void	print_env_var_value(char *variable_name, t_env *lst)
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

static int	print_env_var(char *line, t_env *lst, int i)
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

static int	check_quotes(char *line)
{
	char	symbol;
	int		i;

	i = 0;
	while(line[i])
	{

		if (line[i] && line[i - 1] == '\\' && (line[i] == '\'' || line[i] ==  '\"'))
			i++;
		if (line[i] == '\'' || line[i] ==  '\"')
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

static int	print_inside_quotes(char *line, int i, t_env *lst)
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
		if (line[i] == '\\' && line[i + 1] && symbol != '\'')
			i++;	
		if (symbol == '\"' && line[i] == '$')
			i = print_env_var(line, lst, i);
		else
			write(1, &line[i], 1);
		i++;
	}
	return (i);
}

static void	print_echo_line(char *line, t_env *lst)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"' || line[i] == '$')
			i = print_inside_quotes(line, i, lst);
		else if (line[i] != ' ')
		{
			if (line[i - 1] == ' ')
				write(1, " ", 1);
			if (line[i] == '\\' && line[i + 1])
				i++;
			write(1, &line[i], 1);
		}
		i++;
	}
}

char	*check_flag_n(char *line, int *flag)
{
	if (ft_strncmp("\"-n\" ", line, 5) == 0 \
	|| ft_strncmp("\'-n\' ", line, 5) == 0)
	{
		line = ft_strtrim(line + 5, " ");
		*flag = 1;
	}
	else if  (ft_strncmp("-n ", line, 3) == 0)
	{
		line = ft_strtrim(line + 3, " ");
		*flag = 1;
	}
	else if (ft_strncmp("-n", line, 2) == 0)
	{
		if (is_empty_line(line + 2))
			return (NULL);
	}
	else if (ft_strncmp("\"-n\"", line, 4) == 0 \
	|| ft_strncmp("\'-n\'", line, 4) == 0)
	{
		if (is_empty_line(line + 4))
			return (NULL);
	}
	return (line);
}

void	check_echo_line(char *line, t_env *lst)
{
	int	flag;

	flag = 0;
	while (*line && *line != ' ')
		line++;
	line = ft_strtrim(line, " ");
	line = check_flag_n(line, &flag);
	if (line == NULL)
		return ;
	if (!check_quotes(line))
		return ;
	print_echo_line(line, lst);
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