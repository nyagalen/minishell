/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:26:30 by svydrina          #+#    #+#             */
/*   Updated: 2024/01/07 17:41:09 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_env_var(char *line)
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

int	var_in_env(char *line, t_env *env)
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

void	replace_line_env(char *line, t_env *env)
{
	int	index;

	index = index_str(line, '=');
	while (env)
	{
		if (!ft_strncmp(line, env->line, index + 1))
		{
			free (env->line);
			env->line = ft_strdup(line);
			break ;
		}
		env = env->next;
	}
}

void	export_mult(char **cmd, t_env **env)
{
	int	i;

	i = 0;
	while (cmd[++i])
	{
		if (!valid_env_var(cmd[i]))
		{
			printf("minishell: export: `%s': not a valid identifier\n", cmd[i]);
			return ;
		}
	}
	i = -1;
	while (cmd[++i])
		ft_export(cmd[i], env);
}

void	ft_export(char *var, t_env **env)
{
	t_env	*add_me;

	if (var_in_env(var, *env) == -1)
		return ;
	else if (var_in_env(var, *env))
		replace_line_env(var, *env);
	else
	{
		add_me = env_new(var);
		env_addback(env, add_me);
	}
}
