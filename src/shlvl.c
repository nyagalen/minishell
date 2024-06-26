/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:07:24 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/13 17:25:43 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static void	quit_shlvl(t_env *env)
{
	erreur('m');
	free_env(&env);
	exit(2);
}

t_env	*env_by_name(char *name, t_env *env)
{
	char	*eq;

	eq = ft_strjoin(name, "=");
	if (!eq)
		quit_shlvl(env);
	while (env)
	{
		if (!ft_strncmp(eq, env->line, ft_strlen(name) + 1))
		{
			free(eq);
			return (env);
		}
		env = env->next;
	}
	free(eq);
	return (NULL);
}

int	lvl_incr(t_env *env)
{
	char	*lvl_s;
	t_env	*shlvl;
	int		lvl_i;
	char	*value;

	lvl_i = 0;
	if (env == NULL)
		return (0);
	if (line_in_env("SHLVL=", env))
	{
		shlvl = env_by_name("SHLVL", env);
		lvl_s = shlvl->line;
		value = ft_substr(lvl_s, 6, ft_strlen(lvl_s) - 6);
		lvl_i = ft_atoi(value);
		free(value);
	}
	return (lvl_i + 1);
}

void	increment_shlvl(t_env *env)
{
	int		incr;
	char	*num;
	char	*shlvl_inc;
	t_env	*shlvl;

	incr = lvl_incr(env);
	num = ft_itoa(incr);
	if (!num)
		quit_shlvl(env);
	shlvl_inc = ft_strjoin("SHLVL=", num);
	if (!shlvl_inc)
	{
		free(num);
		quit_shlvl(env);
	}
	free(num);
	shlvl = env_by_name("SHLVL", env);
	if (!replace_line_env(shlvl_inc, shlvl))
	{
		free(shlvl_inc);
		quit_shlvl(env);
	}
	free(shlvl_inc);
}
