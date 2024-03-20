/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svetlana <svetlana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:33:51 by svydrina          #+#    #+#             */
/*   Updated: 2024/01/10 00:07:48 by svetlana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

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

void	ft_unset(char **cmd, t_env **env)
{
	int	i;

	i = 0;
	while (cmd[++i])
		valid_and_remove(cmd[i], env);
}

void	valid_and_remove(char *var, t_env **env)
{
	if (!valid_env_var(var) || !var_in_env(var, *env))
		return ;
	env_remove_if(var, env);
}

void	env_remove_if(char *var, t_env **env)
{
	int		eq;
	t_env	*next;
	t_env	*prev;
	t_env	*cur;

	cur = *env;
	prev = NULL;
	while (cur != NULL)
	{
		next = cur->next;
		eq = index_str(cur->line, '=');
		if (!ft_strncmp(var, cur->line, eq))
		{
			if (!prev)
				*env = next;
			else
				prev->next = next;
			free(cur->line);
			free(cur);
		}
		else
			prev = cur;
		cur = next;
	}
}
