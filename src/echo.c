

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
static int	print_inside_quot(char *line, int i)
{
	char	symbol;

	symbol = line[i];
	if (line[i - 1] == ' ')
		printf(" ");
	i++;
	while (line[i] && line[i] != symbol)
	{
		if (line[i] == '\\' && symbol != '\'' && \
		(line[i + 1] == '\\' || line[i + 1] == '\"'))
			i++;
		printf("%c", line[i]);
		i++;
	}
	return (i);
}

/*print echo*/
static void	print_echo_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] && is_quote(line[i]))
			i = print_inside_quot(line, i);
		else if (line[i] && line[i] != ' ')
		{
			if (line[i - 1] == ' ')
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
	char	*new;
	char	*tmp;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (is_quote(line[i]))
		{
			if (!flag_in_quotes(line, flag, &i, &j))
			{
				new = ft_strdup(line + j);
				free(line);
				tmp = ft_strtrim(new, " ");
				free(new);
				return (tmp);
			}
		}
		else if (line[i] == '-')
		{
			i++;
			while (line[i] == 'n')
				i++;
			if (line[i] != ' ' && line[i] != '\0')
			{
				new = ft_strdup(line + j);
				free(line);
				tmp = ft_strtrim(new, " ");
				free(new);
				return (tmp);
			}
			*flag = 0;
			j = i;
		}
		i++;
	}
	new = ft_strdup(line + j);
	free(line);
	tmp = ft_strtrim(new, " ");
	free(new);
	return (tmp);
}

/*manage echo function*/
void	check_echo_line(char *line, t_shell *shell)
{
	int		flag;
	char	*tmp;

	flag = 1;
	line = skip_command_name(line);
	tmp = ft_strtrim(line, " ");
	if (is_empty_line(tmp))
	{
		printf("\n");
		free(tmp);
		return ;
	}
	tmp = check_flag_n(tmp, &flag);
	if (!check_quotes(tmp))
	{
		free(tmp);
		return ;
	}
	print_echo_line(tmp);
	if (flag)
		printf("\n");
	shell->exit_code = 0;
	free(tmp);
}
