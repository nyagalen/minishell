/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 20:52:03 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/17 17:57:59 by svydrina         ###   ########.fr       */
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
	if (!ft_strcmp("exit", info->cmd[info->n_pipe * 2][0])
		&& !info->cmd[info->n_pipe * 2][1])
		info->code = info->instr.orig_exitcode;
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

static int	success_action(t_all *all, int i, int *forks, int *letswait)
{
	all->info.code = file_success(all, i, *forks);
	if (all->info.code == -1)
		return (all->info.code);
	if (all->info.code == 42)
	{
		erreur('m');
		return (42);
	}
	*forks += 1;
	if (i == all->info.n_pipe * 2)
		*letswait = 1;
	return (0);
}

int	handle_redirections(t_all *all, int i, int *forks, int *letswait)
{
	int	success;
	int	success_act;

	success = assign_inout_handle_err(all);
	if (success && all->info.cmd[i][0])
	{
		success_act = success_action(all, i, forks, letswait);
		if (success_act == -1 || success_act == 42)
			return (0);
	}
	else if (success && !all->info.cmd[i][0])
		return (1);
	else
		no_success(&all->info, i, success);
	return (1);
}
