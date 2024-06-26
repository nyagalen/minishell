/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:37:10 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/18 20:10:01 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	if_signaled_pipes(int code)
{
	if (code == 131)
	{
		rl_replace_line("", 0);
		rl_redisplay();
		ft_putstr_fd("  \b\b\b", 2);
	}
	else
		ft_putstr_fd("\b\b\b   \b\b\b", 2);
}

static int	pipe_wait_code(int code)
{
	if (code == 2)
		code += 128;
	else if (code == 131)
		ft_putendl_fd("\\Quit (core dumped)", 2);
	return (exitcode(code));
}

void	pipe_wait(t_infos *info, int forks, int letswait)
{
	int	i;
	int	code;

	i = -1;
	code = 0;
	while (++i < forks)
	{
		waitpid(info->pids[i], &code, 0);
		if (WIFSIGNALED(code))
			if_signaled_pipes(code);
	}
	if (letswait)
		info->code = pipe_wait_code(code);
	free_pids_fds_hdfs(info);
}

int	malloc_pids_fds(t_infos *info)
{
	int	i;

	i = -1;
	info->pids = ft_calloc(1, sizeof(int) * (info->n_pipe + 1));
	if (!info->pids)
		return (erreur('m'));
	info->fds = malloc(sizeof(int *) * info->n_pipe);
	if (!info->fds)
		return (erreur('m'));
	while (++i < info->n_pipe)
	{
		info->fds[i] = malloc(sizeof(int) * 2);
		if (!info->fds[i])
			return (erreur('m'));
	}
	if (info->instr.hd_i)
	{
		info->hd_files = ft_calloc(1,
				(sizeof(char *) * (info->instr.hd_i + 1)));
		if (!info->hd_files)
			return (erreur('m'));
	}
	return (0);
}

int	file_success(t_all *all, int i, int forks)
{
	int	code;

	code = 0;
	all->info.pids[forks] = fork();
	if (all->info.pids[forks] == -1)
	{
		erreur('f');
		return (-1);
	}
	if (!all->info.pids[forks])
	{
		child(&all->info, i / 2);
		code = execpart(&all->info, all->env, i, all);
		reset_in_out(&all->info);
		exit(code);
	}
	return (code);
}
