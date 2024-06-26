/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 21:29:05 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/20 03:12:36 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static int	is_n_flag(char *option)
{
	int	i;

	i = 1;
	if (option[0] != '-')
		return (0);
	while (option[i])
	{
		if (option[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

static int	count_ns(char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i] && is_n_flag(cmd[i]))
		i++;
	return (i);
}

void	ft_echo(char **cmd, t_infos *info)
{
	int	flag;
	int	i;

	flag = 0;
	if (tab_size(cmd) > 1)
	{
		i = count_ns(cmd);
		flag = (i > 1);
		if (cmd[i])
		{
			ft_putstr_fd(cmd[i], info->instr.out);
			while (cmd[++i])
			{
				ft_putchar_fd(' ', info->instr.out);
				ft_putstr_fd(cmd[i], info->instr.out);
			}
		}
	}
	if (!flag)
		ft_putstr_fd("\n", info->instr.out);
}

void	ft_echo_pipe(char **cmd)
{
	int	flag;
	int	i;

	flag = 0;
	if (tab_size(cmd) > 1)
	{
		i = count_ns(cmd);
		flag = (i > 1);
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