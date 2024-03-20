/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 19:27:19 by cbuyurha          #+#    #+#             */
/*   Updated: 2024/03/20 23:13:27 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	g_sig = 0;

void	handle_signals(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_sig = 130;
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		printf("  \b\b");
	}
}

static void	init_all(t_all *all, char **envp)
{
	t_env	*env;

	all->info.cmd = NULL;
	all->info.red_tab = NULL;
	env = init_env(envp);
	all->env = env;
	all->info.code = 0;
	all->info.n_pipe = 0;
	all->info.instr.in = -2;
	all->info.instr.out = -2;
	all->info.instr.red_start = 0;
	all->info.pids = NULL;
	all->info.fds = NULL;
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

int	main(int ac, char **av, char **envp)
{
	char	*buffer;
	t_all	all;

	(void)ac;
	(void)av;
	init_all(&all, envp);
	buffer = readline("$>");
	while (buffer)
	{
		update_sig(&all.info.code);
		if (*buffer)
			add_history(buffer);
		all.info.cmd = cmd_tab(&all, buffer);
		free(buffer);
		if (all.info.cmd && all.info.cmd[0])
		{
			if (!all.info.n_pipe)
				no_pipe(&all.info, all.env);
			else
				loop(&(all.info), all.env);
		}
		buffer = new_entry(&all.info);
	}
	ft_exit(&(all.info), &all.env, 0);
	return (0);
}
