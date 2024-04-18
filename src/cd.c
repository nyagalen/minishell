/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 23:14:57 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/18 19:07:52 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static int	check_dir_cd(char *fold)
{
	DIR	*folder;

	folder = opendir(fold);
	if (!access(fold, F_OK) && folder == NULL)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(fold, 2);
		ft_putendl_fd(": Not a directory", 2);
		return (1);
	}
	if (folder)
		closedir(folder);
	return (0);
}

static int	change_oldpwd(t_env *env, t_all *all)
{
	char	*oldpwd;
	char	*old_join;

	oldpwd = value_by_name("PWD", env);
	if (oldpwd)
	{
		old_join = ft_strjoin("OLDPWD=", oldpwd);
		if (!old_join)
			return (-1);
	}
	else
		old_join = NULL;
	if (!ft_export(old_join, &env, all))
		return (free(old_join), -1);
	if (old_join)
		free(old_join);
	return (0);
}

static int	change_pwd(t_env *env, t_all *all)
{
	char	cwd[PATH_MAX];
	char	*newpwd;
	char	*new_join;

	newpwd = getcwd(cwd, sizeof(cwd));
	if (!newpwd)
		return (0);
	new_join = ft_strjoin("PWD=", newpwd);
	if (!new_join)
		return (-1);
	if (!ft_export(new_join, &env, all))
		return (free(new_join), -1);
	if (new_join)
		free(new_join);
	return (0);
}

int	built_in_cd(char **cmd, t_env *env, t_all *all)
{
	char	*home;

	home = value_by_name("HOME", env);
	if (cmd[1] && cmd[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", 2);
		return (1);
	}
	if (cmd[1] && check_dir_cd(cmd[1]))
		return (1);
	if (!cmd[1] && home == NULL)
		return (ft_putendl_fd("minishell: cd: HOME not set", 2), 1);
	if (!cmd[1] && home[0] && chdir(home) == -1)
		return (write_cd_error(home));
	if (cmd[1] && chdir(cmd[1]) == -1)
		return (write_cd_error(cmd[1]));
	if (change_oldpwd(env, all))
		return (-1);
	if (change_pwd(env, all))
		return (-1);
	return (0);
}
