

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:50:22 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/02/12 17:52:18 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*echo print function*/
static int	print_inside_quot(char *line, int i, t_shell *shell, int *inval_var)
{
	char	symbol;

	symbol = line[i];
	if (line[i - 1] == ' ')
		printf(" ");
	if (symbol == '$')
		return (print_env_var(line, shell, i, inval_var));
	i++;
	while (line[i] && line[i] != symbol)
	{
		if (line[i] == '\\' && symbol != '\'' && \
		(line[i + 1] == '\\' || line[i + 1] == '\"'))
			i++;
		if (symbol == '\"' && line[i] == '$' && !is_empty_line(line + i + 1) \
		&& line[i + 1] != ' ' && !is_quote(line[i + 1]))
			i = print_env_var(line, shell, i, inval_var);
		else
			printf("%c", line[i]);
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
		if (line[i] && (is_quote(line[i]) || (line[i] == '$' \
		&& !is_empty_line(line + i + 1) \
		&& line[i + 1] != ' ' && !is_quote(line[i + 1]))))
			i = print_inside_quot(line, i, shell, &invalid_var);
		else if (line[i] && line[i] != ' ')
		{
			if (invalid_var == 0 && line[i - 1] == ' ')
				printf(" ");
			if (line[i] == '\\' && line[i + 1])
				i++;
			printf("%c", line[i]);
		}
		i++;
	}
}

static int	flag_in_quotes(char *line, int *flag, int *i, int *j)
{
	char	symbol;
	int		tmp_i;

	tmp_i = *i;
	symbol = line[tmp_i++];
	if (line[tmp_i++] != '-')
		return (*j);
	while (line[tmp_i] && line[tmp_i] == 'n')
		tmp_i++;
	if (line[tmp_i++] != symbol)
		return (*j);
	if (line[tmp_i] != ' ' && line[tmp_i] != '\0')
		return (*j);
	*flag = 0;
	*j = tmp_i;
	*i = tmp_i;
	return (TRUE);
}

/*checks echo -n flag*/
static char	*check_flag_n(char *line, int *flag)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (is_quote(line[i]))
		{
			if (!flag_in_quotes(line, flag, &i, &j))
				return (line + j);
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
	line = ft_strtrim(skip_command_name(line), " ");
	if (is_empty_line(line))
	{
		printf("\n");
		return ;
	}
	line = check_flag_n(line, &flag);
	while (*line && *line == ' ')
		line++;
	if (!check_quotes(line))
		return ;
	print_echo_line(line, shell);
	if (flag)
		printf("\n");
	shell->exit_code = 0;
}
