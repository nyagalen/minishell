/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 01:51:07 by svydrina          #+#    #+#             */
/*   Updated: 2024/01/07 01:30:41 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_built_in(char *cmd)
{
	int			i;
	const char	*built_in[] = {"cd", "pwd", "export",\
	"unset", "env", NULL};//echo is not here anymore

	i = -1;
	while (built_in[++i])
	{
		if (!ft_strcmp(cmd, built_in[i]))
			return (1);
	}
	return (0);
}

void	built_in_cd(char *path)
{
	if (chdir(path) == -1)
		write_cd_error(path);
}

void	built_in_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd()");
}

void	exec_builtin(char **cmd, t_env *env)
{
	if (!ft_strcmp(cmd[0], "pwd"))
		built_in_pwd();
	else if (!ft_strcmp(cmd[0], "cd"))
		built_in_cd(cmd[1]);
	else if (!ft_strcmp(cmd[0], "env"))
		print_env(env);
	else if (!ft_strcmp(cmd[0], "export"))
		export_mult(cmd, &env);
}
