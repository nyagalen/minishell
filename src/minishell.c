/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 19:27:19 by cbuyurha          #+#    #+#             */
/*   Updated: 2024/04/14 05:42:08 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	g_sig = 0;

static void	init_all(t_all *all, char **envp)
{
	t_env	*env;

	all->info.cmd = NULL;
	all->info.red_tab = NULL;
	all->env = NULL;
	env = init_env(envp, all);
	all->info.code = 0;
	all->info.n_pipe = 0;
	all->info.instr.in = -2;
	all->info.instr.out = -2;
	all->info.instr.red_start = 0;
	all->info.instr.status = 0;
	all->info.instr.cmd_i = 0;
	all->info.instr.hd_i = 0;
	all->info.instr.line = 1;
	all->info.pids = NULL;
	all->info.fds = NULL;
	all->info.hd_files = NULL;
	increment_shlvl(env);
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, handle_signals);
}

void	update_sig(int *code)
{
	if (g_sig)
		*code = g_sig;
	g_sig = 0;
}

void	exec(t_all *all)
{
	if (!all->info.cmd)
		return ;
	if (all->info.cmd[0] || all->info.red_tab)
	{
		if (!all->info.n_pipe)
			no_pipe(all, all->env);
		else
			loop(all);
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*buffer;
	t_all	all;

	(void)ac;
	(void)av;
	init_all(&all, envp);
	buffer = readline("$> ");
	while (buffer)
	{
		update_sig(&all.info.code);
		if (*buffer)
			add_history(buffer);
		all.info.cmd = cmd_tab(&all, buffer);
		free(buffer);
		exec(&all);
		buffer = new_entry(&all.info);
	}
	ft_exit(&(all.info), &all.env, 0);
	return (0);
}
