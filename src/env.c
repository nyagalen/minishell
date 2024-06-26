/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 22:24:41 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/20 03:10:38 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

t_env	*init_env(char **envp, t_all *all)
{
	int		i;
	t_env	*env;

	i = -1;
	env = NULL;
	while (envp[++i])
		env_addback(&env, env_new(envp[i], all));
	return (env);
}

void	print_env(t_env *env, t_infos *info)
{
	while (!info->n_pipe && env)
	{
		ft_putendl_fd(env->line, info->instr.out);
		env = env->next;
	}
	while (info->n_pipe && env)
	{
		printf("%s\n", env->line);
		env = env->next;
	}
}

void	free_env(t_env **env)
{
	t_env	*temp;

	if (!env)
		return ;
	while (*env)
	{
		temp = (*env)->next;
		free((*env)->line);
		free(*env);
		*env = temp;
	}
}

char	*var_value(t_env *env)
{
	int	eq;

	eq = index_str(env->line, '=');
	return (env->line + eq + 1);
}

char	*value_by_name(char *name, t_env *env)
{
	while (env)
	{
		if (env->line[ft_strlen(name)] == '='
			&& !ft_strncmp(name, env->line, ft_strlen(name)))
			return (var_value(env));
		env = env->next;
	}
	return (NULL);
}
