/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 01:51:07 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/20 03:09:01 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	is_built_in(char *cmd)
{
	int			i;
	const char	*built_in[] = {"cd", "pwd", "export", \
		"unset", "env", "echo", "exit", NULL};

	i = -1;
	while (built_in[++i])
	{
		if (!ft_strcmp(cmd, built_in[i]))
			return (1);
	}
	return (0);
}

int	built_in_pwd(t_infos *info)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd()");
		return (-1);
	}
	else if (!info->n_pipe)
		ft_putendl_fd(cwd, info->instr.out);
	else if (info->n_pipe)
		printf("%s\n", cwd);
	return (0);
}

int	exec_builtin(t_infos *infos, t_env *env, int i, t_all *all)
{
	int	code;

	if (infos->instr.out < 0 && !infos->n_pipe)
		infos->instr.out = STDOUT_FILENO;
	code = 0;
	if (!ft_strcmp(infos->cmd[i][0], "pwd"))
		code = built_in_pwd(infos);
	else if (!ft_strcmp(infos->cmd[i][0], "cd"))
		code = built_in_cd(infos->cmd[i], env, all);
	else if (!ft_strcmp(infos->cmd[i][0], "env"))
		print_env(env, infos);
	else if (!ft_strcmp(infos->cmd[i][0], "export"))
		code = export_mult(infos->cmd[i], &env, all);
	else if (!ft_strcmp(infos->cmd[i][0], "unset"))
		ft_unset(infos->cmd[0], &env, all);
	else if (!infos->n_pipe && !ft_strcmp(infos->cmd[i][0], "echo"))
		ft_echo(infos->cmd[i], infos);
	else if (infos->n_pipe && !ft_strcmp(infos->cmd[i][0], "echo"))
		ft_echo_pipe(infos->cmd[i]);
	else if (!ft_strcmp(infos->cmd[i][0], "exit"))
		code = ft_exit(infos, &env, i);
	return (code);
}
