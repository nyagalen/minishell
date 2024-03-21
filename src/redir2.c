/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 01:33:36 by svydrina          #+#    #+#             */
/*   Updated: 2024/03/21 01:35:08 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	ft_dup(t_infos *info)
{
	if (info->instr.in > 0)
		dup2(info->instr.in, 0);
	if (info->instr.out > 0)
		dup2(info->instr.out, 1);
}
