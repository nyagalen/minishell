/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:11:44 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/17 16:38:35 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	ft_close(int fd)
{
	if (fd > 0)
		close (fd);
}

void	free_close_fds_pids(t_infos *info)
{
	int	i;

	i = -1;
	while (++i < info->n_pipe)
	{
		if (info->fds && info->fds[i])
		{
			free(info->fds[i]);
			info->fds[i] = NULL;
		}
	}
	if (info->fds)
		free(info->fds);
	if (info->pids)
		free(info->pids);
	if (info->hd_files)
		free_tab(info->hd_files);
	info->fds = NULL;
	info->pids = NULL;
	info->hd_files = NULL;
}

void	reset_in_out(t_infos *info)
{
	ft_close(info->instr.in);
	ft_close(info->instr.out);
	info->instr.in = -2;
	info->instr.out = -2;
}
