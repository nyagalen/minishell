/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:33:36 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/15 18:10:20 by svydrina         ###   ########.fr       */
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
	int	files_opened;

	if ((all->info.red_tab))
	{
		files_opened = get_inf_outf(all);
		if (files_opened == -1)
			return (-1);
		else if (!files_opened)
		{
			reset_in_out(&all->info);
			if (!all->info.code)
				all->info.code = 1;
			return (0);
		}
	}
	return (1);
}

int	handle_err_set_index(t_all *all, int *fdin, int *fdout, int i)
{
	int	status;

	status = open_file(all, all->info.red_tab[i], fdin, fdout);
	if (status == -1)
	{
		reset_in_out(&all->info);
		return (status);
	}
	else if (status)
	{
		while (all->info.red_tab[i] && all->info.red_tab[i][0] != '|')
			i++;
		all->info.instr.red_start = i
			+ (all->info.red_tab[i] && all->info.red_tab[i][0] == '|');
		if (status == 130)
			all->info.instr.status = status;
		all->info.code = status;
		reset_in_out(&all->info);
		return (status);
	}
	all->info.code = status;
	return (status);
}

int	is_heredoc(char *red)
{
	return (!ft_strncmp(red, "<<", 2));
}

int	open_in(char *red, int *fdin)
{
	if (*(red + 1) == 0 || access(red + 1, F_OK) == -1)
		return (no_such_file_error(red + 1) > 0);
	*fdin = open(red + 1, O_RDONLY);
	if (*fdin == -1 && access(red + 1, R_OK) == -1)
		return (perm_denied(red + 1) > 0);
	return (0);
}
