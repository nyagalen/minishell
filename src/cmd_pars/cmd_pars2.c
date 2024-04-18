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

int	skip_arg2bis(t_all *a, t_infos *i, int x)
{
	char	*b;

	b = i->buf;
	if (b[x] == '|' && ++i->l_arg[i->na - 1] >= 0)
		return (++x);
	while (x < i->b_len && b[x] != ' ' && b[x] != '	')
	{
		if (b[x] != 34 && b[x] != 39 && b[x] != '|')
			++i->l_arg[i->na - 1];
		if (b[x] == '$')
			x = x + skip_dollars(a, i, x);
		if (x < i->b_len && b[x] == 34)
			x = count_dollars(a, ++x, 1);
		if (x < i->b_len && b[x] && b[x] == 39 && ++x < i->b_len)
		{
			while (b[x] != 39 && ++x < i->b_len)
				++i->l_arg[i->na - 1];
		}
		if (x < i->b_len && b[x] == '|')
			return (x);
		++x;
	}
	return (x);
}
/*pointe a l'endroit ou l'argument en cours(nbr) se termine
calcul la taille de cet argument 
et la met dans i->l_arg[nbr[0] - 1]
gere le cas des "" et ''
gere le cas d'un |
gere le cas des $
gere le cas des '$' (39)
gere le cas des "$" (34)*/
/*charactere speciaux : /-'* + #~@^*/

int	skip_arg2(t_all *a, t_infos *i, int x)
{
	char	*b;

	b = i->buf;
	if (x >= i->b_len)
		return (x);
	if ((x == 0 || i->tab_nbr == -1) && b[x] != '|')
		i->l_tab[++i->tab_nbr] = 2;
	else if (b[x] == '|')
	{
		if (++i->p_check >= 2 || (x == 0 || i->tab_nbr == -1))
			i->l_tab[++i->tab_nbr] = 1;
		i->l_tab[++i->tab_nbr] = 2;
	}
	else if (b[x - 1] == ' ' || b[x - 1] == '	' || b[x - 1] == '|')
	{
		if (i->p_check >= 1)
			i->l_tab[++i->tab_nbr] = 1;
		i->p_check = 0;
		i->l_tab[i->tab_nbr]++;
	}
	else
		return (skip_arg2bis(a, i, x));
	i->na = i->na + 1;
	i->l_arg[i->na - 1] = 1;
	return (skip_arg2bis(a, i, x));
}

/*gerer ici la présence de | seules*/
/*
ls | >fdsa |fdsaf
2  2 1     22
*/
