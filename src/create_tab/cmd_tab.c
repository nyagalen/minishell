/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tab.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:06:07 by cbuyurha          #+#    #+#             */
/*   Updated: 2024/04/11 17:27:28 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

int	argument_nbr(t_all *a, t_infos *i, int mode)
{
	int	x;

	x = 0;
	a->info.na = 0;
	a->info.w = -1;
	while (a->info.error <= 0 && x < a->info.b_len && a->info.buf[x])
	{
		x = skip_space(a->info.buf, x, 1);
		if (mode == 2)
			x = skip_arg2(a, i, x);
		else
			x = skip_arg3(a, i, x);
	}
	if (a->info.error > 0)
		return (-2);
	a->info.l_arg[a->info.na] = 0;
	if (mode == 3)
		a->info.tmp[a->info.arg_nbr] = NULL;
	else if (mode == 2)
	{
		if (a->info.p_check >= 1)
			a->info.l_tab[++a->info.tab_nbr] = 1;
		a->info.l_tab[a->info.tab_nbr + 1] = 0;
	}
	return (a->info.na);
}

int	part_pars(t_all *a, t_infos *i, char *buffer)
{
	i->arg_nbr = 0;
	i->cmd = NULL;
	i->b_len = ft_strlen(buffer);
	i->n_pipe = 0;
	i->p_check = 0;
	i->tab_nbr = 0;
	i->error = 0;
	i->red_n = 0;
	i->er = 0;
	i->buf = ft_strdup(buffer);
	if (!i->buf)
		return (i->error = 1, -2);
	if (check_buf(i) < 0)
		return (pars_error_free(i, 0));
	if (red_init(a, i, -1, -1) < 0 && free_tab(i->red_tab) == NULL)
		return (pars_error_free(i, 0));
	return (0);
}

int	split_parse(t_all *a, char *buffer, t_infos *i)
{
	if (part_pars(a, i, buffer) < 0)
		return (-2);
	i->p_check = 0;
	i->arg_nbr = 0;
	i->tab_nbr = -1;
	i->n_pipe = 0;
	if (tab_info(a, 0) == -2)
		return (pars_error_free(i, 0));
	i->tmp = malloc(sizeof(char *) * (i->arg_nbr + 1));
	i->l_arg = malloc(sizeof(int) * (i->arg_nbr + 1));
	i->l_tab = malloc(sizeof(int) * (i->tab_nbr + 2));
	i->tab_nbr = -1;
	i->p_check = 0;
	if (argument_nbr(a, i, 2) == -2)
		return (pars_error_free(i, 1));
	if (argument_nbr(a, i, 3) == -2)
		return (pars_error_free(i, 1));
	return (0);
}

/*la creation des fichiers 
se fait avant que les commandes d'executent!! \
je dois donc mettre les > qui ne sont pas 
concernes dans un tableau separes pour etre crees avant*/

char	***cmd_tab1(t_all *all, char *buffer)
{
	if (!buffer || !buffer[0])
		return (NULL);
	if (split_parse(all, buffer, &all->info) == -2)
		return (pars_error(all->info.error), NULL);
	all->info.cmd = tab_assign(all);
	all->info.tmp = free_tab(all->info.tmp);
	free(all->info.l_arg);
	free(all->info.l_tab);
	free(all->info.buf);
	all->info.buf = NULL;
	if (all->info.error > 0 && pars_error(all->info.error) == 0)
		all->info.cmd = free_tab3(all->info.cmd);
	return (all->info.cmd);
}

char	***cmd_tab(t_all *all, char *buffer)
{
	all->info.cmd = cmd_tab1(all, buffer);
	if (all->info.error > 0)
		all->info.code = 2;
	return (all->info.cmd);
}
/* partie du parsing + de la creation de cmd*/
