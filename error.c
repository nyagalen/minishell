/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:29:49 by svydrina          #+#    #+#             */
/*   Updated: 2023/12/02 15:37:35 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_error(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		write(2, &cmd[i], 1);
		i++;
	}
	write(2, ": command not found\n", 20);
}

void	write_cd_error(char *file)
{
	int	i;

	i = -1;
	write(2, "minishell: cd: ", 15);
	while (file[++i])
		write(2, &file[i], 1);
	write(2, ": No such file or directory\n", 28);
}
