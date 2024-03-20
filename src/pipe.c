/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 18:37:10 by svydrina          #+#    #+#             */
/*   Updated: 2024/03/20 20:24:00 by svydrina         ###   ########.fr       */
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

void	no_pipe(t_infos *info, t_env *env)
{
	int		pid;
	int		code;
	char	*exec;

	code = 0;
	if (info->red_tab && !get_inf_outf(&info->instr, info->red_tab))
	{
		code = 1;
		ft_close(info->instr.in);
		ft_close(info->instr.out);
		info->instr.in = -2;
		info->instr.out = -2;
		info->code = exitcode(code);
		return ;
	}
	printf("fdin: %d\n", info->instr.in);
	if (is_built_in(info->cmd[0][0]))
	{
		code = exec_builtin(info, env, 0);
	}
	else
	{
		pid = fork();
		if (pid == -1)
			perror("pid error");
		if (!pid)
		{
			exec = get_absolute_path(info->cmd[0], env);
			if (info->instr.in > 0)
				dup2(info->instr.in, 0);
			if (info->instr.out > 0)
				dup2(info->instr.out, 1);
			code = exec_cmd(info, exec, env, 0);
			free(exec);
			free_env(&env);
			free_tab3(info->cmd);
			info->red_tab = free_tab(info->red_tab);
			rl_clear_history();
			exit(exitcode(code));
		}
		waitpid(pid, &code, 0);
		if (WIFSIGNALED(code))
			if_signaled(info, code);
	}
	ft_close(info->instr.in);
	ft_close(info->instr.out);
	info->instr.in = -2;
	info->instr.out = -2;
	info->code = exitcode(code);
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
		info->instr.red_start = get_inf_outf(&info->instr, info->red_tab) + 1;
		pids[i / 2] = fork();
		if (pids[i / 2] == 0)
		{
			child(fds, i / 2, info->n_pipe);//seems like it's enough to change the parameters if child, put t_info as the third
			// if (info->red_tab && !ft_strncmp(info->red_tab[0], ">", 1))
			// 	redir(info, 0, 1);
			code = execpart(info, env, i);
		
			exit(code);
		}
		else if (pids[i / 2] > 0)
		{
			parent(fds, i / 2, info->n_pipe);
			//if (i == info->n_pipe * 2)
			//{
			//	i = -1;
			//	while (++i < info->n_pipe + 1)
			//		waitpid(pids[i], &code, 0);
			//	if (WIFSIGNALED(code))
			//		if_signaled(info,	ft_close(fds[i][1]); code);
			//}
			//waitpbuffer = new_entry(&all.info);id(pids[i / 2], &code, 0);
			//if (WIFSIGNALED(code))
			//	if_signaled(info, code);
			//info->code  = exitcode(code);
			//printf("what's info-code in parent? %d\n", info->code);
		}
		i += 2;
	}
	pipe_wait(fds, pids, info);
	info->n_pipe = 0;
}
/*			if (cmd centrale)
			{
				dup2(pipefd[0], 0);
				info->pipin = pipefd[0];
				dup2(pipefd[1], 1);
				info->pipout = pipefd[1];these functions shall open the file and return a non-negative integer representing the file descripto
*/
/*
	|
	|pars
	|
	|pipe() * le nombre de commande
	|
	|fork
	|_______
	|		|child process (ls)
	|		|
	|		|close les fd inutiles
	|		|execve()
	|		|
	|		|close les fd que tu a utilise, free le tableau cmd, free l'environement





*/