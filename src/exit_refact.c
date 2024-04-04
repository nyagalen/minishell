/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_refact.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 18:31:08 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/03 19:07:06 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	exit_blabla(t_infos *info, int i)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(info->cmd[i][1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	info->code = 2;
}

int	exit_error(t_infos *infos, int i)
{
	if (infos->cmd && infos->cmd[i]
		&& check_ex_args(infos, infos->cmd[i]) == -1)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		if (!infos->code)
			infos->code = 1;
		return (infos->code);
	}
	if (infos->cmd && infos->cmd[i] && !check_ex_args(infos, infos->cmd[i]))
	{
		exit_blabla(infos, i);
		return (infos->code);
	}
	return (0);
}

// if (infos->cmd && infos->cmd[i]
	// 	&& check_ex_args(infos, infos->cmd[i]) == -1)
	// {
	// 	write(2, "minishell: exit: too many arguments\n", 36);
	// 	if (!infos->code)
	// 		infos->code = 1;
	// 	return (infos->code);
	// }
	// if (infos->cmd && infos->cmd[i] && !check_ex_args(infos, infos->cmd[i]))
	// {
	// 	exit_blabla(infos, i);
	// 	if (infos->n_pipe)
	// 		return (infos->code);
	// }