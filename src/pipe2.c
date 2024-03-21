/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 23:24:24 by svydrina          #+#    #+#             */
/*   Updated: 2024/03/21 01:36:32 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	parent(int **fds, int i, int n_pipe)
{
	if (i == 0)
		ft_close(fds[i][1]);
	else if (i > 0 && i < n_pipe)
	{
		ft_close(fds[i][1]);
		ft_close(fds[i - 1][0]);
	}
	else if (i == n_pipe)
		ft_close(fds[i - 1][0]);
}

static void	middle_child(t_infos *info, int i)
{
	ft_close(info->fds[i][0]);
	if (info->instr.out == -2)
		dup2(info->fds[i][1], 1);
	ft_close(info->fds[i][1]);
	if (info->instr.in == -2)
		dup2(info->fds[i - 1][0], 0);
	ft_close(info->fds[i - 1][0]);
}

void	child(t_infos *info, int i)
{
	ft_dup(info);
	if (i == 0)
	{
		ft_close(info->fds[i][0]);
		if (info->instr.out == -2)
			dup2(info->fds[i][1], 1);
		ft_close(info->fds[i][1]);
	}
	else if (i > 0 && i < info->n_pipe)
		middle_child(info, i);
	else if (i == info->n_pipe)
	{
		if (info->instr.in == -2)
			dup2(info->fds[i - 1][0], 0);
		ft_close(info->fds[i - 1][0]);
	}
}
