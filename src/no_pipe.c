/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:30:04 by svydrina          #+#    #+#             */
/*   Updated: 2024/03/30 21:38:17 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static int	is_non_printing_builtin(char *command)
{
	return (!ft_strcmp(command, "exit") || !ft_strcmp(command, "cd")
		|| !ft_strcmp(command, "export") || !ft_strcmp(command, "unset"));
}

static int	exec_no_pipe(t_infos *info, t_env *env)
{
	int	code;
	int	pid;

	code = 0;
	pid = fork();
	if (pid == -1)
		perror("pid error");
	if (!pid)
	{
		ft_dup(info);
		code = execpart(info, env, 0);
		exit(exitcode(code));
	}
	waitpid(pid, &code, 0);
	if (WIFSIGNALED(code))
		if_signaled(info, code);
	return (code);
}

void	no_pipe(t_all *all, t_env *env)
{
	int		code;

	code = 0;
	if (!assign_inout_handle_err(all) || !all->info.cmd[0][0])
	{
		all->info.instr.red_start = 0;
		return ;
	}
	if (is_non_printing_builtin(all->info.cmd[0][0]))
		code = exec_builtin(&all->info, env, 0);
	else
		code = exec_no_pipe(&all->info, env);
	reset_in_out(&all->info);
	all->info.instr.red_start = 0;
	all->info.code = exitcode(code);
}
