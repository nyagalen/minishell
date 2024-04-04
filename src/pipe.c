/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:37:10 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/03 20:05:14 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	if_signaled_pipes(int code)
{
	if (code == 131)
	{
		rl_replace_line("", 0);
		rl_redisplay();
		printf("  \b\b\b");
	}
	else
		printf("\b\b\b   \b\b\b");
}

static int	pipe_wait_code(int code)
{
	if (code == 2)
		code += 128;
	else if (code == 131)
		printf("\\Quit (core dumped)\n");
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
	free(info->pids);
	info->pids = NULL;
	i = -1;
	while (++i < info->n_pipe)
	{
		free(info->fds[i]);
		info->fds[i] = NULL;
	}
	free(info->fds);
	info->fds = NULL;
	info->hd_files = free_tab(info->hd_files);
}

void	malloc_pids_fds(t_infos *info)
{
	int	i;

	i = -1;
	info->pids = ft_calloc(1, sizeof(int) * (info->n_pipe + 1));
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
	if (info->instr.hd_i)
	{
		info->hd_files = ft_calloc(1,
				(sizeof(char *) * (info->instr.hd_i + 1)));
		if (!info->hd_files)
			perror("malloc error");
	}
}

int	file_success(t_all *all, int i, int forks)
{
	int	code;

	code = 0;
	all->info.pids[forks] = fork();
	if (all->info.pids[forks] == -1)
		perror("fork error");
	if (!all->info.pids[forks])
	{
		child(&all->info, i / 2);
		code = execpart(&all->info, all->env, i);
		reset_in_out(&all->info);
		exit(code);
	}
	return (code);
}
