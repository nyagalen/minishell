/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 20:16:49 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/14 20:45:05 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	**copy_envp(t_env *env)
{
	int		envp_size;
	int		i;
	char	**envp;

	i = -1;
	envp_size = env_size(env);
	envp = ft_calloc(1, sizeof(char *) * (envp_size + 1));
	if (!envp)
		return (NULL);
	while (env && ++i < envp_size)
	{
		envp[i] = ft_strdup(env->line);
		if (!envp[i])
		{
			free_arr(envp);
			return (NULL);
		}
		env = env->next;
	}
	return (envp);
}
