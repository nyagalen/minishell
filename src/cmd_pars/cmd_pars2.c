/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pars2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:02:50 by cbuyurha          #+#    #+#             */
/*   Updated: 2024/03/12 18:14:45 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

int	skip_arg2bis(t_all *a, int x, int *nbr)
{
	if (a->info.buf[x] == '|' && ++a->info.l_arg[nbr[0] - 1] >= 0)
		return (++x);
	while (x < a->info.b_len && a->info.buf[x] != ' ' && a->info.buf[x] != '	')
	{
		if (a->info.buf[x] != 34 && a->info.buf[x] != 39 && a->info.buf[x] != '|')
			++a->info.l_arg[nbr[0] - 1];
		if (a->info.buf[x] == '$')
			x = x + skip_dollars(a, x, nbr);
		if (a->info.buf[x] == 34)
			x = count_dollars(a, ++x, nbr, 1);
		if (a->info.buf[x] == 39 && ++x < a->info.b_len)
		{
			while (a->info.buf[x] != 39 && ++x < a->info.b_len)
				++a->info.l_arg[nbr[0] - 1];
		}
		if (a->info.buf[x] == '|')
			return (x);
		++x;
	}
	return (x);
}
/*pointe a l'endroit ou l'argument en cours(nbr) se termine
calcul la taille de cet argument 
et la met dans a->info.l_arg[nbr[0] - 1]
gere le cas des "" et ''
gere le cas d'un |
gere le cas des $
gere le cas des '$' (39)
gere le cas des "$" (34)*/
/*charactere speciaux : /-'* + #~@^*/

int	skip_arg2(t_all *a, int x, int *nbr)
{
//	printf("			1 a->info.p_check: %d -> tqb_nbr: %d\n", a->info.p_check, a->info.tab_nbr);
	if (x >= a->info.b_len)
		return (x);
	if ((x == 0 || a->info.tab_nbr == -1) && a->info.buf[x] != '|')
		a->info.l_tab[++a->info.tab_nbr] = 2;
	else if (a->info.buf[x] == '|')
	{
		if (++a->info.p_check >= 2 || (x == 0 || a->info.tab_nbr == -1))
			a->info.l_tab[++a->info.tab_nbr] = 1;
		/*if (a->info.p_check++ >= 2)
			a->info.p_check = 0;*/
		a->info.l_tab[++a->info.tab_nbr] = 2;
	}
	else if (a->info.buf[x - 1] == ' ' || a->info.buf[x - 1] == '	')
	{
		if (a->info.p_check >= 1)
			a->info.l_tab[++a->info.tab_nbr] = 1;
		a->info.p_check = 0;
		a->info.l_tab[a->info.tab_nbr]++;
	}
	else
		return (skip_arg2bis(a, x, nbr));
	nbr[0] = nbr[0] + 1;
	a->info.l_arg[nbr[0] - 1] = 1;
//	printf("			2 a->info.p_check: %d -> l_tab[tqb_nbr:%d] %d\n", a->info.p_check, a->info.tab_nbr, a->info.l_tab[a->info.tab_nbr]);
	return (skip_arg2bis(a, x, nbr));
}

/*gerer ici la présence de | seules*/
/*
ls | >fdsa |fdsaf
2  2 1     22
*/
