/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svetlana <svetlana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:32:18 by svydrina          #+#    #+#             */
/*   Updated: 2024/01/10 00:12:40 by svetlana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	env_addback(t_env **env, t_env *new)
{
	t_env	*last;

	if (env)
	{
		if (*env == NULL)
			*env = new;
		else
		{
			last = env_last(*(env));
			last->next = new;
		}
	}
}

t_env	*env_last(t_env *env)
{
	if (!env)
		return (NULL);
	while (env)
	{
		if (env->next == NULL)
			return (env);
		env = env->next;
	}
	return (env);
}

t_env	*env_new(char *new_l)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		perror("Malloc error");
	new->line = ft_strdup(new_l);
	new->next = NULL;
	return (new);
}

int	index_str(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (i);
	}
	return (-1);
}

int	valid_env_var(char *var)
{
	int	i;

	i = 0;
	if (!(ft_isalpha(var[i]) || var[i] == '_'))
		return (0);
	while (var[++i])
	{
		if (!(ft_isalnum(var[i]) || var[i] == '_'))
			return (0);
	}
	return (1);
}
