/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 20:54:20 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/14 22:14:05 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	free_resources_child(t_infos *info, t_env *env)
{
	free_close_fds_pids(info);
	free_env(&env);
	info->cmd = free_tab3(info->cmd);
	info->red_tab = free_tab(info->red_tab);
	reset_in_out(info);
	rl_clear_history();
}

int	erreur(char type)
{
	if (type == 'm')
		perror("malloc error");
	else if (type == 'f')
		perror("fork error");
	else if (type == 'd')
		perror("fd error");
	return (1);
}

void	free_pids_fds_hdfs(t_infos *info)
{
	int	i;

	if (info->pids)
		free(info->pids);
	info->pids = NULL;
	i = -1;
	if (info->fds)
	{
		while (++i < info->n_pipe)
		{
			free(info->fds[i]);
			info->fds[i] = NULL;
		}
		free(info->fds);
	info->fds = NULL;
	}
	info->hd_files = free_tab(info->hd_files);
}

int	env_size(t_env *env)
{
	int	size;

	size = 0;
	while (env)
	{
		size++;
		env = env->next;
	}
	return (size);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}
