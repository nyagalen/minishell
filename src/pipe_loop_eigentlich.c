/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_loop_eigentlich.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 02:29:02 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/17 17:47:57 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static void	count_hds(t_infos *info)
{
	int	i;

	i = 0;
	while (info->red_tab[i])
	{
		if (info->red_tab[i][0] == '|' || !is_heredoc(info->red_tab[i]))
		{
			i++;
			continue ;
		}
		else if (is_heredoc(info->red_tab[i]))
		{
			info->instr.hd_i += 1;
			i++;
		}
	}
}

static int	name_hd_files(t_all *all, int hds)
{
	char	*hd_num;

	hd_num = ft_itoa(hds);
	if (!hd_num)
		return (0);
	all->info.hd_files[hds] = ft_strjoin(".hd", hd_num);
	if (!all->info.hd_files[hds])
	{
		free(hd_num);
		return (0);
	}
	free(hd_num);
	return (1);
}

static int	open_heredocs(t_all *all)
{
	int		i;
	int		hds;
	int		status;

	i = 0;
	hds = 0;
	while (all->info.red_tab && hds < all->info.instr.hd_i)
	{
		if (all->info.red_tab[i][0] == '|' || !is_heredoc(all->info.red_tab[i]))
		{
			i++;
			continue ;
		}
		if (!name_hd_files(all, hds))
			return (perror("malloc error"), -1);
		status = hd_pipe_parent(all, hds, all->info.red_tab[i] + 2);
		if (status)
			return (status);
		hds++;
		i++;
	}
	if (hds)
		all->info.instr.hd_i = 0;
	return (0);
}

static int	malloc_handle_hds(t_all *all)
{
	int	heredoc_success;

	if (all->info.red_tab)
		count_hds(&all->info);
	if (malloc_pids_fds(&all->info))
		return (-1);
	heredoc_success = open_heredocs(all);
	if (heredoc_success == -1)
		return (-1);
	if (heredoc_success)
	{
		interrupted_heredoc(&all->info);
		return (heredoc_success);
	}
	return (0);
}

void	loop(t_all *all)
{
	int	i;
	int	forks;
	int	letswait;
	int	heredoc_success;

	forks = 0;
	all->info.instr.orig_exitcode = all->info.code;
	heredoc_success = malloc_handle_hds(all);
	if (heredoc_success)
		return ;
	i = 0;
	letswait = 0;
	while (i <= all->info.n_pipe * 2 && all->info.cmd[i])
	{
		if (i / 2 < all->info.n_pipe)
			pipe(all->info.fds[i / 2]);
		if (!handle_redirections(all, i, &forks, &letswait))
			return ;
		parent(all->info.fds, i / 2, all->info.n_pipe);
		reset_in_out(&all->info);
		all->info.instr.cmd_i++;
		i += 2;
	}
	end_loop(&all->info, forks, letswait);
}
