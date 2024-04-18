/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 23:17:18 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/17 21:34:24 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	is_a_dir_err(char *exec)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(exec, 2);
	ft_putendl_fd(": Is a directory", 2);
	return (126);
}

int	perm_denied(char *exec)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(exec, 2);
	ft_putendl_fd(": Permission denied", 2);
	return (126);
}

int	var_in_line(char *var, char *line)
{
	int	i;

	i = -1;
	while (var[++i])
	{
		if (var[i] != line[i])
			return (0);
	}
	return (1);
}

int	var_in_env(char *var, t_env *env)
{
	while (env)
	{
		if (var_in_line(var, env->line))
			return (1);
		env = env->next;
	}
	return (0);
}
