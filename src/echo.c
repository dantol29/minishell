/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurmyza <akurmyza@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:50:22 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/23 15:38:38 by akurmyza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*checks that every quote is closed and skips \\"*/
static int	check_quotes(char *line)
{
	char	symbol;
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] && line[i - 1] != '\\' && \
		(line[i] == '\'' || line[i] == '\"'))
		{
			symbol = line[i];
			while (line[i])
			{
				i++;
				if (line[i] && line[i] == symbol && line[i - 1] != '\\')
					break ;
			}
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

/*echo print function*/
static int	print_inside_quotes(char *line, int i, t_env *lst, int *invalid_var)
{
	char	symbol;

	symbol = line[i];
	if (line[i - 1] == ' ')
		write(1, " ", 1);
	if (symbol == '$')
		return (print_env_var(line, lst, i, invalid_var));
	i++;
	while (line[i] && line[i] != symbol)
	{
		if (line[i] == '\\' && symbol != '\'' && \
		(line[i + 1] == '\\' || line[i + 1] == '\"'))
			i++;
		if (symbol == '\"' && line[i] == '$')
			i = print_env_var(line, lst, i, invalid_var);
		else
			write(1, &line[i], 1);
		i++;
	}
	return (i);
}

/*print echo*/
static void	print_echo_line(char *line, t_env *lst)
{
	int	i;
	int	invalid_var;

	i = 0;
	invalid_var = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"' || line[i] == '$')
			i = print_inside_quotes(line, i, lst, &invalid_var);
		else if (line[i] != ' ')
		{
			if (invalid_var == 0 && line[i - 1] == ' ')
				write(1, " ", 1);
			if (line[i] == '\\' && line[i + 1])
				i++;
			write(1, &line[i], 1);
		}
		i++;
	}
}

/*checks echo -n flag
echo -n -nnnnn AB
skip all valid -n -nnnnnn
return line*/
static char	*check_flag_n(char *line, int *flag)
{
	int		i;
	int		j;
	char	symbol;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			symbol = line[i++];
			if (line[i++] != '-')
				return (line + j);
			while (line[i] && line[i] == 'n')
				i++;
			if (line[i++] != symbol)
				return (line + j);
			if (line[i] != ' ' && line[i] != '\0')
				return (line + j);
			*flag = 0;
			j = i;
		}
		else if (line[i] == '-')
		{
			i++;
			while (line[i] == 'n')
				i++;
			if (line[i] != ' ' && line[i] != '\0')
				return (line + j);
			*flag = 0;
			j = i;	
		}
		i++;
	}
	return (line + j);
}

/*manage echo function
while (*line && *line != ' ')
		line++; // to skip `echo`*/
void	check_echo_line(char *line, t_env *lst)
{
	int	flag;

	flag = 1;
	line = skip_command_name(line);
	if (is_empty_line(line))
	{
		write(1, "\n", 1);
		return ;
	}
	line = check_flag_n(line, &flag);
	line = ft_strtrim(line, " ");
	if (!check_quotes(line))
		return ;
	print_echo_line(line, lst);
	if (flag)
		write(1, "\n", 1);
}
