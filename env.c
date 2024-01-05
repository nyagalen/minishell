/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 22:24:41 by svydrina          #+#    #+#             */
/*   Updated: 2024/01/05 17:26:12 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env(char **envp)
{
	int		i;
	t_env	*env;

	i = -1;
	while (envp[++i])
		env_addback(&env, env_new(envp[i]));
	return (env);
}

void	print_env(t_env *env)
{
	while (env)
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

