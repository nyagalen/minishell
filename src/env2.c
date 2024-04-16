/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:26:30 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/14 22:18:03 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	valid_env_line(char *line)
{
	int	i;
	int	eq;

	i = 0;
	if (!(ft_isalpha(line[i]) || line[i] == '_'))
		return (0);
	eq = index_str(line, '=');
	while (line[++i] && (eq == -1 || i < eq))
	{
		if (!(ft_isalnum(line[i]) || line[i] == '_'))
			return (0);
	}
	return (1);
}

int	line_in_env(char *line, t_env *env)
{
	int		index;
	char	*env_line;

	while (env)
	{
		env_line = env->line;
		index = index_str(line, '=');
		if (index == -1)
			return (-1);
		if (!ft_strncmp(line, env_line, index + 1))
			return (1);
		env = env->next;
	}
	return (0);
}

int	replace_line_env(char *line, t_env *env)
{
	int	index;

	index = index_str(line, '=');
	while (env)
	{
		if (!ft_strncmp(line, env->line, index + 1))
		{
			free (env->line);
			env->line = ft_strdup(line);
			if (!env->line)
				return (0);
			break ;
		}
		env = env->next;
	}
	return (1);
}

int	export_mult(char **cmd, t_env **env, t_all *all)
{
	int	i;

	i = 0;
	while (cmd[++i])
	{
		if (!valid_env_line(cmd[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
			return (1);
		}
	}
	i = 0;
	while (cmd[++i])
	{
		if (!ft_export(cmd[i], env, all))
			return (-1);
	}
	return (0);
}

int	ft_export(char *var, t_env **env, t_all *all)
{
	t_env	*add_me;

	if (var == NULL)
		return (1);
	if (line_in_env(var, *env) == -1)
		return (1);
	else if (line_in_env(var, *env))
	{
		if (!replace_line_env(var, *env))
			return (0);
	}
	else
	{
		add_me = env_new(var, all);
		env_addback(env, add_me);
	}
	return (1);
}
