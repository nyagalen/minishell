/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:37:10 by svydrina          #+#    #+#             */
/*   Updated: 2024/03/21 01:51:08 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static void	pipe_wait(int **fds, int *pids, t_infos *info)
{
	int	i;
	int	code;

	i = -1;
	code = 0;
	while (++i <= info->n_pipe)
		waitpid(pids[i], &code, 0);
	if (WIFSIGNALED(code))
		if_signaled(info, code);
	info->code = exitcode(code);
	free(pids);
	i = -1;
	while (++i < info->n_pipe)
		free(fds[i]);
	free(fds);
}

static void	malloc_pids_fds(t_infos *info)
{
	int	i;

	i = -1;
	info->pids = malloc(sizeof(int) * (info->n_pipe + 1));
	if (!info->pids)
		perror("malloc error");
	info->fds = malloc(sizeof(int *) * info->n_pipe);
	if (!info->fds)
		perror("malloc error");
	while (++i < info->n_pipe)
	{
		info->fds[i] = malloc(sizeof(int) * 2);
		if (!info->fds[i])
			perror("malloc error");
	}
}

void	loop(t_infos *info, t_env *env)
{
	int	i;
	int	code;

	code = 0;
	malloc_pids_fds(info);
	i = 0;
	while (i <= info->n_pipe * 2 && info->cmd[i])
	{
		if (i / 2 < info->n_pipe)
			pipe(info->fds[i / 2]);
		info->pids[i / 2] = fork();
		if (info->pids[i / 2] == -1)
			perror("fork error");
		if (info->pids[i / 2] == 0)
		{
			child(info, i / 2);
			code = execpart(info, env, i);
			exit(code);
		}
		parent(info->fds, i / 2, info->n_pipe);
		i += 2;
	}
	pipe_wait(info->fds, info->pids, info);
	info->n_pipe = 0;
}
