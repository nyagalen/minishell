/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:33:36 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/03 20:09:39 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_dup(t_infos *info)
{
	if (info->instr.in > 0)
		dup2(info->instr.in, 0);
	if (info->instr.out > 0)
		dup2(info->instr.out, 1);
}

int	assign_inout_handle_err(t_all *all)
{
	if ((all->info.red_tab && !get_inf_outf(all)))
	{
		reset_in_out(&all->info);
		if (!all->info.code)
			all->info.code = 1;
		return (0);
	}
	return (1);
}

int	handle_err_set_index(t_all *all, int *fdin, int *fdout, int i)
{
	int	status;

	status = open_file(all, all->info.red_tab[i], fdin, fdout);
	if (status)
	{
		while (all->info.red_tab[i] && all->info.red_tab[i][0] != '|')
			i++;
		all->info.instr.red_start = i
			+ (all->info.red_tab[i] && all->info.red_tab[i][0] == '|');
		if (status == 130)
			all->info.instr.status = status;
		all->info.code = status;
		return (status);
	}
	all->info.code = status;
	return (status);
}
