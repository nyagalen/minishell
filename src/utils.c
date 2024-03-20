/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:11:44 by svydrina          #+#    #+#             */
/*   Updated: 2024/03/20 23:29:24 by svydrina         ###   ########.fr       */
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

void	exit_blabla(t_infos *info, int i)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(info->cmd[i][1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	info->code = 2;
}

void	free_close_fds_pids(t_infos *info)
{
	int	i;

	i = -1;
	while (++i < info->n_pipe)
	{
		free(info->fds[i]);
		info->fds[i] = NULL;
	}
	if (info->fds)
		free(info->fds);
	if (info->pids)
		free(info->pids);
	info->fds = NULL;
	info->pids = NULL;
}

void	reset_in_out(t_infos *info)
{
	ft_close(info->instr.in);
	ft_close(info->instr.out);
	info->instr.in = -2;
	info->instr.out = -2;
}

