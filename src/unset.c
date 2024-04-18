/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:33:51 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/17 21:33:23 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_unset(char **cmd, t_env **env, t_all *all)
{
	int	i;

	i = 0;
	while (cmd[++i])
		valid_and_remove(cmd[i], env, all);
}

void	valid_and_remove(char *var, t_env **env, t_all *all)
{
	if (!valid_env_var(var) || !var_in_env(var, *env))
		return ;
	env_remove_if(var, env, all);
}

static int	is_env_variable(char *var, char *line)
{
	int	eq;

	eq = index_str(line, '=');
	return (ft_strncmp(var, line, eq));
}

static void	free_maillon(t_env **env)
{
	free((*env)->line);
	(*env)->line = NULL;
	free(*env);
	env = NULL;
}

void	env_remove_if(char *var, t_env **env, t_all *all)
{
	t_env	*next;
	t_env	*prev;
	t_env	*cur;

	cur = *env;
	prev = NULL;
	next = NULL;
	while (cur != NULL)
	{
		next = cur->next;
		if (!is_env_variable(var, cur->line))
		{
			if (!prev)
			{
				*env = next;
				all->env = *env;
			}
			else
				prev->next = next;
			free_maillon(&cur);
		}
		else
			prev = cur;
		cur = next;
	}
}
