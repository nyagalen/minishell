/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pars3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuyurha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:03:03 by cbuyurha          #+#    #+#             */
/*   Updated: 2024/03/11 10:03:08 by cbuyurha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

int	skip_arg3bis(t_all *a, char *buf, int x, int *nbr)
{
	if (buf[x] == '|')
		return (++x);
	while (x < a->info.b_len && buf[x] != ' ' && buf[x] != '	')
	{
		if (buf[x] == '$')
			x = x + skip_dollars2(a, x, 2);
		if (buf[x] == 34)
			x = count_dollars(a, ++x, nbr, 2);
		if (buf[x] == 39 && ++x <= a->info.b_len)
			x = x + skip_char(&buf[x], 39, 1);
		if (buf[x] == '|')
			return (x);
		++x;
	}
	return (x);
}

int	skip_arg3(t_all *a, int x, int *nbr)
{
	int	save;

	save = -1;
	if (x >= a->info.b_len)
		return (x);
	nbr[0] = nbr[0] + 1;
	save = x;
	x = skip_arg3bis(a,a->info.buf, x, nbr);
	if (save != -1 && new_argument(a, x, save, nbr) == -2)
		printf("malloc error potentielle a gérer\n"); //a gerer
	return (x);
}

/*int skip_arg2test()*/
