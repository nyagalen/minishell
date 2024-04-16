/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_conv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:03:35 by cbuyurha          #+#    #+#             */
/*   Updated: 2024/04/11 19:50:28 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

char	*var_value_tmp(t_env *env)
{
	int	eq;

	eq = index_str(env->line, '=');
	return (env->line + eq + 1);
}

char	*find_var_val(char *var, t_env *env)
{
	size_t	len;
	char	*env_line;

	len = ft_strlen(var);
	while (env)
	{
		env_line = env->line;
		if (len <= ft_strlen(env_line))
		{
			if (env_line && env_line[len] && env_line[len] == '=')
			{
				if (!ft_strncmp(var, env_line, len))
					return (var_value_tmp(env));
			}
		}
		env = env->next;
	}
	return (NULL);
}

int	find_variable(char *var, t_env *env)
{
	size_t	len;
	char	*env_line;

	len = ft_strlen(var);
	while (env)
	{
		env_line = env->line;
		if (len <= ft_strlen(env_line))
		{
			if (env_line && env_line[len] && env_line[len] == '=')
			{
				if (!ft_strncmp(var, env_line, len))
					return (1);
			}
		}
		env = env->next;
	}
	return (0);
}

char	*var_copy(t_all *a, char *dst, char *model)
{
	int	len;
	int	x;

	len = ft_strlen(model);
	x = -1;
	while (a->info.w < a->info.l_arg[a->info.na - 1] && ++x < len)
		dst[++a->info.w] = model[x];
	return (dst);
}
