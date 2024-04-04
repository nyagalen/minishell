/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:06:07 by cbuyurha          #+#    #+#             */
/*   Updated: 2024/03/15 17:12:31 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

char	***tab_assign(t_all *a);
int		fct_test_big_tab(t_all *a,int x, int *nbr);

int	argument_nbr(t_all *a, int mode)
{
	int x;
	int *nbr;

	x = 0;
	a->info.nbr2 = 0;
	a->info.w = -1;
	a->info.error = 0;
	nbr = &a->info.nbr2;
	if (!a->info.buf)
		return (-1);
	while (x < a->info.b_len && a->info.buf[x])
	{
		x = skip_space(a->info.buf, x, 1);
		if (mode == 1)
			x = skip_arg1(&a->info, x);
		else if (mode == 2)
			x = skip_arg2(a, x, nbr);
		else
			x = skip_arg3(a, x, nbr);

	}
	if (mode == 1)
	{
		//printf("	->tabnbr: %d, i->n_pipe: %d\n", a->info.tab_nbr, a->info.n_pipe);
		if (a->info.p_check == 1)
			a->info.tab_nbr++;
		return (a->info.arg_nbr);
	}
	a->info.l_arg[nbr[0]] = 0;
	if (mode == 3)
		a->info.tmp[a->info.arg_nbr] = NULL;
	else if (mode == 2)
	{
	//	printf("	-a->info.l_tab[%d] %d\n", a->info.tab_nbr, a->info.l_tab[a->info.tab_nbr]);
		if (a->info.p_check == 1)
			a->info.l_tab[++a->info.tab_nbr] = 1;
		a->info.l_tab[a->info.tab_nbr + 1] = 0;
	}
	return (a->info.nbr2);
}

int	check_buf(t_infos *i);
int	pars_error(int error);

int	split_parse(t_all *all, char *buffer, t_infos *i)
{
	i->arg_nbr = 0;
	i->b_len = ft_strlen(buffer);
	i->n_pipe = 0;
	i->p_check = 0;
	i->tab_nbr = 0;
	i->error = 0;
	i->red_n = 0;
	i->q = 0;
	i->buf = ft_strdup(buffer);
	if (!i->buf)
		return (i->error = 1, -2);
	if (check_buf(&all->info) < 0)
		return (-2);
	if (red_init(all, i, -1, -1) < 0 && free_tab(i->red_tab) == NULL)
		return (-2);
	printf("\n\narg_nbr part\n");
	i->p_check = 0;
	i->arg_nbr = 0;
	i->tab_nbr = -1;
	i->n_pipe = 0;
	i->arg_nbr = argument_nbr(all, 1);
	if (i->error > 0 && free_tab(i->red_tab) == NULL)
		return (-2);
	printf("i->arg_nbr: %d, i->tab_nbr %d\n", i->arg_nbr, i->tab_nbr);
	i->tmp = malloc(sizeof(char *) * (i->arg_nbr + 1));
	i->l_arg = malloc(sizeof(int) * (i->arg_nbr + 1));
	i->l_tab = malloc(sizeof(int) * (i->tab_nbr + 2));
	i->tab_nbr = -1;
	i->p_check = 0;
	argument_nbr(all, 2);
	print_intx2(i->l_tab);
	print_intx2(i->l_arg);
	argument_nbr(all, 3);
	return (0);
}
/*la creation des fichiers 
se fait avant que les commandes d'executent!! \
je dois donc mettre les > qui ne sont pas 
concernes dans un tableau separes pour etre crees avant*/

char	***cmd_tab(t_all *all, char *buffer)
{
	if (!buffer || !buffer[0])
		return (NULL);
	if (split_parse(all, buffer, &all->info) == -2)
		return (pars_error(all->info.error), NULL);
	print_tab(all->info.tmp);
	all->info.cmd = tab_assign(all);
	all->info.tmp = free_tab(all->info.tmp);
	free(all->info.l_arg);
	free(all->info.l_tab);
	free(all->info.buf);
	all->info.buf = NULL;
	if (!all->info.cmd)
		return (NULL); // faire une erreur
	print_tabx2(all->info.cmd, -1);
	//printf("\ncmd tab end\n\n");
	return (all->info.cmd);
}
/* partie du parsing + de la creation de cmd*/

/*
log: ne pas gerer ici les null mais gerer avec les tableaux de int
*/
