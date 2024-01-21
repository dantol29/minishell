/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 17:50:22 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/21 19:00:39 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*checks that every quote is closed and skips \\"*/
static int	check_quotes(char *line)
{
	char	symbol;
	int		i;

	i = 0;
	while(line[i])
	{
		if (line[i] && line[i - 1] != '\\' && (line[i] == '\'' || line[i] ==  '\"'))
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
		if (line[i] == '\\' && symbol != '\'' && \
		(line[i + 1] == '\\' || line[i + 1] == '\"'))
			i++;	
		if (symbol == '\"' && line[i] == '$')
			i = print_env_var(line, lst, i);
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

/*checks echo -n flag*/
static char	*check_flag_n(char *line, int *flag)
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

/*manage echo function*/
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