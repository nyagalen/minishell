/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_getline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 21:16:26 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/18 20:10:36 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	if_signaled(int code)
{
	int	sig;

	sig = WTERMSIG(code);
	if (code == 131)
	{
		rl_replace_line("", 0);
		rl_redisplay();
		ft_putstr_fd("  \b\b", 2);
		ft_putendl_fd("Quit (core dumped)", 2);
	}
	else
	{
		ft_putendl_fd("  \b\b", 2);
		return (code + 128);
	}
	return (code);
}

int	exec_cmd(t_infos *infos, char *exec, t_env *env, int i)
{
	int		code;
	char	**envp;

	envp = copy_envp(env);
	if (!envp)
		return (42);
	infos->code = 0;
	execve(exec, infos->cmd[i], envp);
	code = failed_exec(exec, env);
	infos->code = exitcode(code);
	free_arr(envp);
	free_resources_child(infos, env);
	return (exitcode(code));
}

static int	do_builtin(t_all *all, int i, t_infos *infos, t_env *env)
{
	int	code;

	code = exec_builtin(infos, env, i, all);
	if (code == -1)
		code = 42;
	free_resources_child(infos, env);
	return (exitcode(code));
}

int	execpart(t_infos *infos, t_env *env, int i, t_all *all)
{
	char	*exec;
	int		code;

	code = 0;
	if (!infos->cmd || !infos->cmd[0])
		return (0);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!ft_strcmp(infos->cmd[i][0], ".."))
	{
		write_error(infos->cmd[i][0]);
		return (free_resources_child(infos, env), 127);
	}
	if (is_built_in(infos->cmd[i][0]))
		return (do_builtin(all, i, infos, env));
	else
	{
		exec = get_absolute_path(infos->cmd[i], env);
		if (!exec)
			return (42);
		code = exec_cmd(infos, exec, env, i);
		free(exec);
		return (exitcode(code));
	}
	return (0);
}

char	*new_entry(t_infos *info)
{
	info->cmd = free_tab3(info->cmd);
	info->red_tab = free_tab(info->red_tab);
	free_pids_fds_hdfs(info);
	info->instr.red_start = 0;
	info->instr.status = 0;
	info->n_pipe = 0;
	info->instr.hd_i = 0;
	info->instr.cmd_i = 0;
	info->instr.line += 1;
	reset_in_out(info);
	return (readline("$> "));
}
