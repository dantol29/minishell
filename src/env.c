/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtolmaco <dtolmaco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:00:47 by dtolmaco          #+#    #+#             */
/*   Updated: 2024/01/27 11:48:14 by dtolmaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*print all env variables*/
void	print_env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}

/*print the value of the enviroment variable*/
void	print_env_var_value(char *variable_name, t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, variable_name))
		{
			write(1, tmp->value, sizeof(tmp->value));
			break ;
		}
		tmp = tmp->next;
	}
}

/* i++ - to skip $ dollar sign, i-- - to not skip white space between env var*/
int	print_env_var(char *line, t_shell *shell, int i, int *invalid_var)
{
	int	start;

	i++;
	start = i;
	if (line[i] == '?')
	{
		if (g_ctrl_c_status == 130)
			ft_putnbr_fd(130, 1);
		else
			ft_putnbr_fd(shell->exit_code, 1);
		return (i);
	}
	while (line[i] && line[i] != ' '&& line[i] != '$' && !is_quote(line[i]))
		i++;
	print_env_var_value(ft_substr(line, start, i - start), shell->env);
	if (!find_env_var(ft_substr(line, start, i - start), shell->env))
		*invalid_var = 1;
	i--;
	return (i);
}

/*checks if the environment variable exists*/
int	find_env_var(char *variable_name, t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, variable_name))
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

/*returns the value of the env variable*/
char	*get_env_value(char *variable_name, t_env *lst)
{
	t_env	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, variable_name))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
