/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pars1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 20:49:22 by cbuyurha          #+#    #+#             */
/*   Updated: 2024/04/13 19:11:38 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

int	wipe_dollars2(t_all *a, char *tmp, int x, int len)
{
	int	l;

	l = a->info.b_len - len;
	free(tmp);
	tmp = malloc(sizeof(char) * (l + 2));
	if (!tmp)
		return (a->info.error = 1, -2);
	ft_strlcpy(tmp, a->info.buf, x + 1);
	tmp[x] = ' ';
	ft_strlcpy(&tmp[x + 1], &a->info.buf[x + len], (l - x + 1));
	free(a->info.buf);
	a->info.buf = ft_strdup(tmp);
	if (!a->info.buf)
		return (a->info.error = 1, -2);
	free(tmp);
	a->info.b_len = ft_strlen(a->info.buf);
	if (a->info.buf[x + 1] == '$')
		return (wipe_dollars(a, &a->info, x + 1));
	return (0);
}

int	wipe_dollars(t_all *a, t_infos *i, int x)
{
	char	*tmp_env;
	int		len;

	tmp_env = NULL;
	len = skip_dollars2(a, x, 1);
	if (len == -2 || len == -3)
		return (1);
	++len;
	if (i->buf[x + len] && i->buf[x + len] != ' ' && i->buf[x + len] != '	')
	{
		if (i->buf[x + len] != '$' && i->buf[x + len] != '|')
			return (1);
	}
	tmp_env = malloc(sizeof(char) * (len));
	if (!tmp_env)
		return (i->error = 1, -2);
	ft_strlcpy(tmp_env, &i->buf[x + 1], len);
	if (find_variable(tmp_env, a->env) == 1)
		return (free(tmp_env), 1);
	else if (len != 1)
		return (wipe_dollars2(a, tmp_env, x, len));
	free(tmp_env);
	return (1);
}

int	skip_arg1bis(t_infos *i, int x)
{
	if (x < i->b_len && i->buf[x] == '|')
		return (++x);
	while (x < i->b_len && i->buf[x] != '	' && i->buf[x] != ' ')
	{
		if (i->buf[x] == 34 && ++x <= i->b_len)
			x = x + skip_char(&i->buf[x], 34, 1);
		if (x < i->b_len && i->buf[x] == 39 && ++x <= i->b_len)
			x = x + skip_char(&i->buf[x], 39, 1);
		if (i->buf[x] == '|')
			return (x);
		++x;
	}
	return (x);
}

int	skip_arg1(t_all *a, t_infos *i, int x)
{
	if (x < i->b_len && i->buf[x] == '$' && wipe_dollars(a, i, x) <= 0)
		return (++x);
	if (x < i->b_len && i->buf[x] == ' ')
		x = skip_space(a->info.buf, x, 1);
	if (x < i->b_len && (x == 0 || i->buf[x] == '|' || i->buf[x - 1] == '|'))
	{
		if (i->buf[x] == '|')
			++i->n_pipe;
		if ((i->p_check >= 1 || i->arg_nbr <= 0) && i->buf[x] == '|')
			i->tab_nbr++;
		if (i->buf[x] == '|')
			i->p_check = 1;
		else if (x != 0)
			i->p_check = 0;
		i->tab_nbr++;
		++i->arg_nbr;
	}
	else if (x < i->b_len && (i->buf[x - 1] == ' ' || i->buf[x - 1] == '	'))
	{
		if (i->p_check == 1 || i->tab_nbr == -1)
			i->tab_nbr++;
		i->p_check = 0;
		++i->arg_nbr;
	}
	return (skip_arg1bis(i, x));
}
/* recupere l'argument c et boucle (en ++arg_nbr si il y a un espace avant) 
jusqu'a le renconrer une deuxieme fois ou a depasser b_len (taille du buffer)
 dans ce cas message d'erreur a gerer
si c = ' ', meme chose*/
/*skip les parties qui ne concernent pas les commandes, 
ajouter les | et les < ici plus tard*/
/*sdf'fsdf'" fdsf"*/

int	tab_info(t_all *a, int x)
{
	if (!a->info.buf)
		return (-1);
	while (x < a->info.b_len && a->info.buf[x])
	{
		x = skip_space(a->info.buf, x, 1);
		x = skip_arg1(a, &a->info, x);
		if (a->info.error > 0)
			return (-2);
	}
	if (a->info.error > 0)
		return (-2);
	if (a->info.p_check == 1)
		a->info.tab_nbr++;
	return (a->info.arg_nbr);
}
