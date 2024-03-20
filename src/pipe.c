/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:37:10 by svydrina          #+#    #+#             */
/*   Updated: 2024/03/20 23:36:23 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	child(int **fds, int i, int n_pipe)
{
	if (i == 0)
	{
		ft_close(fds[i][0]);
		dup2(fds[i][1], 1);
		ft_close(fds[i][1]);
	}
	else if (i > 0 && i < n_pipe)
	{
		ft_close(fds[i][0]);
		dup2(fds[i][1], 1);
		ft_close(fds[i][1]);
		dup2(fds[i - 1][0], 0);
		ft_close(fds[i - 1][0]);
	}
	else if (i == n_pipe)
	{
		dup2(fds[i - 1][0], 0);
		ft_close(fds[i - 1][0]);
	}
}

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

void	loop(t_infos *info, t_env *env)
{
	int	i;
	int	*pids;
	int	**fds;
	int	code;

	i = -1;
	code = 0;
	pids = malloc(sizeof(int) * (info->n_pipe + 1));
	info->pids = pids;
	fds = malloc(sizeof(int *) * info->n_pipe);
	info->fds = fds;
	while (++i < info->n_pipe)
		fds[i] = malloc(sizeof(int) * 2);
	i = 0;
	while (i <= info->n_pipe * 2 && info->cmd[i])
	{
		if (i / 2 < info->n_pipe)
			pipe(fds[i / 2]);
	//	info->instr.red_start = get_inf_outf(&info->instr, info->red_tab) + 1;
		pids[i / 2] = fork();
		if (pids[i / 2] == -1)
			perror("fork error");
		if (pids[i / 2] == 0)
		{
			child(fds, i / 2, info->n_pipe);
			code = execpart(info, env, i);
			exit(code);
		}
		parent(fds, i / 2, info->n_pipe);
		i += 2;
	}
	pipe_wait(fds, pids, info);
	info->n_pipe = 0;
}
