/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 21:29:05 by svydrina          #+#    #+#             */
/*   Updated: 2024/02/12 00:09:49 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_echo(char **cmd)
{
	int	flag;
	int	i;

	flag = 0;
	if (tab_size(cmd) > 1)
	{
		if (!ft_strcmp(cmd[1], "-n"))
			flag = 1;
		if (flag)
			i = 2;
		else
			i = 1;
		if (cmd[i])
		{
			printf("%s", cmd[i]);
			while (cmd[++i])
				printf(" %s", cmd[i]);
		}
	}
	if (!flag)
		printf("\n");
}
