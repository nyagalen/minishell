/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_getline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 21:16:26 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/02 23:19:42 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	if_signaled(t_infos *infos, int code)
{
	if (code == 131)
	{
		rl_replace_line("", 0);
		rl_redisplay();
		printf("\b\b\b   \b\b\b");
		printf("Quit (core dumped)\n");
	}
	else
		printf("\b\b\b   \b\b\b");
	infos->code = code;
}

int	exec_cmd(t_infos *infos, char *exec, t_env *env, int i)
{
	int		code;

	infos->code = 0;
	execve(exec, infos->cmd[i], NULL);
	code = failed_exec(exec, env);
	infos->code = exitcode(code);
	return (exitcode(code));
}

int	execpart(t_infos *infos, t_env *env, int i)
{
	char	*exec;
	int		code;

	code = 0;
	if (!infos->cmd || !infos->cmd[0])
		return (0);
	if (is_built_in(infos->cmd[i][0]))
	{
		code = exec_builtin(infos, env, i);
		free_resources_child(infos, env);
		return (exitcode(code));
	}
	else
	{
		exec = get_absolute_path(infos->cmd[i], env);
		code = exec_cmd(infos, exec, env, i);
		free(exec);
		free_resources_child(infos, env);
		return (exitcode(code));
	}
	return (0);
}

char	*new_entry(t_infos *info)
{
	info->cmd = free_tab3(info->cmd);
	info->red_tab = free_tab(info->red_tab);
	info->instr.red_start = 0;
	info->instr.status = 0;
	info->n_pipe = 0;
	info->instr.line += 1;
	reset_in_out(info);
	return (readline("$> "));
}
