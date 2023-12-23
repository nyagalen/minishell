/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:21:45 by svydrina          #+#    #+#             */
/*   Updated: 2023/12/01 20:11:18 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cat_bin(char *path, char *cmd)
{
	char	*bin;
	char	*slash;

	slash = ft_strdup("/\0");
	bin = calloc(sizeof(char), ft_strlen(path) + 1
			+ ft_strlen(cmd) + 1);
	if (!bin)
		return (NULL);
	ft_strlcat(bin, path, ft_strlen(path) + 1);
	ft_strlcat(bin, slash, ft_strlen(path) + 2);
	ft_strlcat(bin, cmd, ft_strlen(path) + 2
		+ ft_strlen(cmd));
	free(slash);
	return (bin);
}

void	get_absolute_path(char **cmd)
{
	char	*path;
	char	**path_split;
	char	*bin;
	int		i;

	i = -1;
	path = ft_strdup(getenv("PATH"));
	if (path == NULL)
		path = ft_strdup("/bin:/usr/local/bin:\
				/usr/bin:/bin:/usr/local/sbin");
	if (cmd[0] && cmd[0][0] != '/' && ft_strncmp(cmd[0], "./", 2))
	{
		path_split = ft_split(path, ":");
		free(path);
		while (path_split[++i])
		{
			bin = cat_bin(path_split[i], cmd[0]);
			if (!bin)
				break ;
			if (access(bin, F_OK) == 0)
				break ;
			free(bin);
			bin = NULL;
		}
		free_arr(path_split);
		if (bin)
		{
			free(cmd[0]);
			cmd[0] = bin;
		}
	}
	else
		free(path);
}
