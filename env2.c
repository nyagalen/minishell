/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 23:26:30 by svydrina          #+#    #+#             */
/*   Updated: 2024/01/07 01:29:51 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(char *var, t_env **env)
{
	t_env	*add_me;

	add_me = env_new(var);
	env_addback(env, add_me);
}
