/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:30:04 by svydrina          #+#    #+#             */
/*   Updated: 2024/03/20 23:31:30 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	no_pipe(t_infos *info, t_env *env)
{
	int		pid;
	int		code;

	code = 0;
	if (info->red_tab && !get_inf_outf(&info->instr, info->red_tab))
	{
		reset_in_out(info);
		info->code = 1;
		return ;
	}
	if (!ft_strcmp(info->cmd[0][0], "exit"))
		ft_exit(info, &env, 0);
	else
	{
		pid = fork();
		if (pid == -1)
			perror("pid error");
		if (!pid)
		{
			if (info->instr.in > 0)
				dup2(info->instr.in, 0);
			if (info->instr.out > 0)
				dup2(info->instr.out, 1);
			code = execpart(info, env, 0);
			exit(exitcode(code));
		}
		waitpid(pid, &code, 0);
		if (WIFSIGNALED(code))
			if_signaled(info, code);
	}
	reset_in_out(info);
	info->code = exitcode(code);
}

