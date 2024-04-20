/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:30:04 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/20 03:24:28 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

// static int	is_non_printing_builtin(char *command)
// {
// 	return (!ft_strcmp(command, "exit") || !ft_strcmp(command, "cd")
// 		|| !ft_strcmp(command, "export") || !ft_strcmp(command, "unset"));
// }

static int	exec_no_pipe(t_infos *info, t_env *env, t_all *all)
{
	int	code;
	int	pid;

	code = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
	{
		erreur('f');
		return (-1);
	}
	if (!pid)
	{
		ft_dup(info);
		code = execpart(info, env, 0, all);
		exit(exitcode(code));
	}
	waitpid(pid, &code, 0);
	if (WIFSIGNALED(code))
		code = if_signaled(code);
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
	return (code);
}

void	no_pipe(t_all *all, t_env *env)
{
	int		code;

	code = 0;
	if (assign_inout_handle_err(all) <= 0 || !all->info.cmd[0][0])
	{
		all->info.instr.red_start = 0;
		return ;
	}
	if (is_built_in(all->info.cmd[0][0]))
		code = exec_builtin(&all->info, env, 0, all);
	else
		code = exec_no_pipe(&all->info, env, all);
	if (code == 42 || code == -1)
		erreur('m');
	reset_in_out(&all->info);
	all->info.instr.red_start = 0;
	if (all->info.code > -1)
		all->info.code = exitcode(code);
}
