/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 20:52:03 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/04 19:54:59 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	interrupted_heredoc(t_infos *info)
{
	info->code = info->instr.status;
	info->instr.status = 0;
	info->instr.red_start = 0;
	info->instr.hd_i = 0;
	reset_in_out(info);
	info->instr.cmd_i = 0;
	info->code = 130;
}

void	end_loop(t_infos *info, int forks, int letswait)
{
	pipe_wait(info, forks, letswait);
	info->instr.red_start = 0;
	info->instr.hd_i = 0;
	reset_in_out(info);
	info->instr.cmd_i = 0;
	g_sig = 0;
}

static void	no_success(t_infos *info, int i, int success)
{
	if (i == info->n_pipe * 2 && !success && info->instr.status == 130)
	{
		info->code = 130;
		info->instr.status = 0;
	}
	else
		info->code = 1;
}

static void	success_action(t_all *all, int i, int *forks, int *letswait)
{
	all->info.code = file_success(all, i, *forks);
	*forks += 1;
	if (i == all->info.n_pipe * 2)
		*letswait = 1;
}

void	handle_redirections(t_all *all, int i, int *forks, int *letswait)
{
	int	success;

	success = assign_inout_handle_err(all);
	if (success && all->info.cmd[i][0])
		success_action(all, i, forks, letswait);
	else if (success && !all->info.cmd[i][0])
		return ;
	else
		no_success(&all->info, i, success);
}
