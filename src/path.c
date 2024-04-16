/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:21:45 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/13 17:27:16 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static char	*cat_bin(char *path, char *cmd)
{
	char	*bin;
	char	*slash;

	slash = ft_strdup("/\0");
	if (!slash)
		return (NULL);
	bin = calloc(sizeof(char), ft_strlen(path) + 1
			+ ft_strlen(cmd) + 1);
	if (!bin)
	{
		free(slash);
		return (NULL);
	}
	ft_strlcat(bin, path, ft_strlen(path) + 1);
	ft_strlcat(bin, slash, ft_strlen(path) + 2);
	ft_strlcat(bin, cmd, ft_strlen(path) + 2
		+ ft_strlen(cmd));
	free(slash);
	return (bin);
}

static void	free_bin(char **bin)
{
	free(*bin);
	*bin = NULL;
}

char	*get_bin(char *cmd, char *path)
{
	char	**path_split;
	char	*bin;
	int		i;

	bin = NULL;
	i = -1;
	if (path && cmd && cmd[0] && !ft_strchr(cmd, '/'))
	{
		path_split = ft_split(path + 5, ":");
		if (!path_split)
			return (NULL);
		while (path_split[++i])
		{
			bin = cat_bin(path_split[i], cmd);
			if (!bin)
				return (NULL);
			if (access(bin, F_OK) == 0)
				break ;
			free_bin(&bin);
		}
		free_arr(path_split);
	}
	if (bin == NULL)
		bin = ft_strdup(cmd);
	return (bin);
}

char	*get_absolute_path(char **cmd, t_env *env)
{
	char	*path;
	char	*bin;

	path = value_by_name("PATH", env);
	bin = get_bin(cmd[0], path);
	return (bin);
}
