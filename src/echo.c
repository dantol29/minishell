/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:50:22 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/25 18:49:39 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*echo print function*/
static int	print_inside_quot(char *line, int i, t_shell *shell, int *inval_var)
{
	char	symbol;

	symbol = line[i];
	if (line[i - 1] == ' ')
		write(1, " ", 1);
	if (symbol == '$')
		return (print_env_var(line, shell, i, inval_var));
	i++;
	while (line[i] && line[i] != symbol)
	{
		if (line[i] == '\\' && symbol != '\'' && \
		(line[i + 1] == '\\' || line[i + 1] == '\"'))
			i++;
		if (symbol == '\"' && line[i] == '$')
			i = print_env_var(line, shell, i, inval_var);
		else
			write(1, &line[i], 1);
		i++;
	}
	return (i);
}

/*print echo*/
static void	print_echo_line(char *line, t_shell *shell)
{
	int	i;
	int	invalid_var;

	i = 0;
	invalid_var = 0;
	while (line[i])
	{
		if (is_quote(line[i]) || line[i] == '$')
			i = print_inside_quot(line, i, shell, &invalid_var);
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

/*checks echo -n flag*/
static char	*check_flag_n(char *line, int *flag)
{
	int		i;
	int		j;
	char	symbol;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (is_quote(line[i]))
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

/*manage echo function*/
void	check_echo_line(char *line, t_shell *shell)
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
	print_echo_line(line, shell);
	if (flag)
		write(1, "\n", 1);
}
