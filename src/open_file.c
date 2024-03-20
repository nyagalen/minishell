/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 18:26:41 by svydrina          #+#    #+#             */
/*   Updated: 2024/03/20 20:12:38 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	open_out(char *red, int *fdout, char mode)
{
	DIR		*folder;
	char	*filename;
	int		code;

	code = 0;
	if (mode == 'a')
	{
		filename = red + 2;
		*fdout = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	else if (mode == 't')
	{
		filename = red + 1;
		*fdout = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	folder = opendir(filename);
	if (*fdout == -1 && folder != NULL)
		code = is_a_dir_err(filename);
	if (*fdout == -1 && folder == NULL)
		code = perm_denied(filename);
	if (folder)
		closedir(folder);
	return (code > 0);
}

int	open_in(char *red, int *fdin)
{
	if (access(red + 1, F_OK) == -1)
		return (no_such_file_error(red + 1) > 0);
	*fdin = open(red + 1, O_RDONLY);
	if (*fdin == -1 && access(red + 1, R_OK) == -1)
		return (perm_denied(red + 1) > 0);
	return (0);
}
