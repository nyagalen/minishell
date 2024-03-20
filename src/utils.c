/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 17:11:44 by svydrina          #+#    #+#             */
/*   Updated: 2024/03/13 21:37:42 by svydrina         ###   ########.fr       */
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
	// if (info->n_pipe)
	// {
	// 	free_close_fds_pids(info);
	// 	free_env(env);
	// 	free_tab3(info->cmd);
	// 	rl_clear_history();
	//}
}

void	free_close_fds_pids(t_infos *info)
{
	int	i;

	i = -1;
	while (++i < info->n_pipe)
	{
		// ft_close(info->fds[i][0]);
		// ft_close(info->fds[i][1]);
		free(info->fds[i]);
	}
	free(info->fds);
	free(info->pids);
}