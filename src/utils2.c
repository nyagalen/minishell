/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 20:54:20 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/03 18:29:21 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	free_resources_child(t_infos *info, t_env *env)
{
	free_close_fds_pids(info);
	free_env(&env);
	info->cmd = free_tab3(info->cmd);
	info->red_tab = free_tab(info->red_tab);
	rl_clear_history();
}
