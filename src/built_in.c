/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 01:51:07 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/17 21:08:09 by svydrina         ###   ########.fr       */
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

int	built_in_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd()");
	return (0);
}

int	exec_builtin(t_infos *infos, t_env *env, int i, t_all *all)
{
	if (!ft_strcmp(infos->cmd[i][0], "pwd"))
		return (built_in_pwd());
	else if (!ft_strcmp(infos->cmd[i][0], "cd"))
		return (built_in_cd(infos->cmd[i], env, all));
	else if (!ft_strcmp(infos->cmd[i][0], "env"))
		print_env(env);
	else if (!ft_strcmp(infos->cmd[i][0], "export"))
		return (export_mult(infos->cmd[i], &env, all));
	else if (!ft_strcmp(infos->cmd[i][0], "unset"))
		ft_unset(infos->cmd[0], &env, all);
	else if (!ft_strcmp(infos->cmd[i][0], "echo"))
		ft_echo(infos->cmd[i]);
	else if (!ft_strcmp(infos->cmd[i][0], "exit"))
		return (ft_exit(infos, &env, i));
	return (0);
}
