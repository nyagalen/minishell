/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 23:24:24 by svydrina          #+#    #+#             */
/*   Updated: 2024/03/09 00:14:30 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	parent(int **fds, int i, int n_pipe)
{
	if (i == 0)
		ft_close(fds[i][1]);
	else if (i > 0 && i < n_pipe)
	{
		ft_close(fds[i][1]);
		ft_close(fds[i - 1][0]);
	}
	else if (i == n_pipe)
		ft_close(fds[i - 1][0]);
}

