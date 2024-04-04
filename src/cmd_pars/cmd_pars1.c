/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pars1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuyurha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 20:49:22 by cbuyurha          #+#    #+#             */
/*   Updated: 2024/02/29 20:49:26 by cbuyurha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"
/*
int	cmd_check_pipe2(t_infos *i, int x, int check)
{
	while (i->buf[++i->w])
	{
		if (i->buf[i->w] == '|')
		{
			if (i->buf[i->w + 1] && i->buf[i->w + 1] == '|')
			{
				if (check == 1 && i->buf[i->w - 1] != '|' && ++i->error > 0)
					write(2, &"-minishell: syntax error near unexpected token `||'\n", 52);
				else if (check == 2 && i->buf[i->w - 1] && i->buf[i->w - 1] == '|' && ++i->error > 0)
					write(2, &"-minishell: syntax error near unexpected token `|'\n", 51);
				else if (check == 2 && ++i->error > 0)
					write(2, &"-minishell: syntax error near unexpected token `||'\n", 52);
			}
			else if (!i->buf[i->w + 1] || (i->buf[i->w + 1] && i->buf[i->w + 1] != '|'))
			{
				if ((check == 2 || (check == 1 && i->buf[i->w - 1] != '|')) && ++i->error > 0)
					write(2, &"-minishell: syntax error near unexpected token `|'\n", 51);
			}
			if (i->error > 0)
			{
				i->b_len = x - 1;
				return (-2);
			}
		}
		if (i->buf[i->w] != ' ' && i->buf[i->w] != '	' && i->buf[i->w] != '|')
			check = 0;
		if (i->buf[i->w] == 34)
		{
			while (i->buf[++i->w] && i->buf[i->w] != 34)
				check = 0;
		}
		if (i->buf[i->w] && i->buf[i->w] == 39)
		{
			while (i->buf[++i->w] && i->buf[i->w] != 39)
				check = 0;
		}
		if (i->buf[i->w] && i->buf[i->w] == '|')
			++check;
	}
	if (!i->buf[i->w] && check > 0 && ++i->error > 0)
	{
		write(2, &"`|' opened\n", 12);
		i->b_len = x - 1;
		return (-2);
	}
	return (0);
}

int	cmd_check_pipe1(t_infos *i, int x)
{
//	printf("	i->n_pipe: %d\n", i->n_pipe);
	i->w = x;
	if (i->n_pipe <= 1 && i->arg_nbr <= 1)
	{
		if (i->buf[i->w + 1] && i->buf[i->w + 1] == '|')
			write(2, &"-minishell: syntax error near unexpected token `||'\n", 52);
		else
			write(2, &"-minishell: syntax error near unexpected token `|'\n", 51);
		++i->error;
		i->b_len = x - 1;
		return (x);
	}
	if (i->buf[i->w + 1] && i->buf[i->w + 1] == '|' && ++i->w > 0)
	{
		if (i->n_pipe <= 1 && cmd_check_pipe2(i, x, 2) == -2)
			return (x);
		i->buf[x] = ' ';
		ft_memset(&i->buf[x + 1], 0, i->b_len - x);
		i->n_pipe--;
		i->b_len = x + 1;
		--i->arg_nbr;
		--i->tab_nbr;
	}
	else if (i->n_pipe <= 1 && cmd_check_pipe2(i, x, 1) == -2)
		return (x);
	return (++x);
}*/ /*fdsf dfssd |||"|dsf" dsf dsfdsf*/


int	skip_arg1bis(t_infos *i, int x)
{
	/*if (i->buf[x] == '|')
		return (cmd_check_pipe1(i, x));*/
	if (i->buf[x] == '|')
		return (++x);
	while (x < i->b_len && i->buf[x] != '	' && i->buf[x] != ' ')
	{
		if (i->buf[x] == 34 && ++x <= i->b_len)
			x = x + skip_char(&i->buf[x], 34, 1);
		if (x < i->b_len && i->buf[x] == 39 && ++x <= i->b_len)
			x = x + skip_char(&i->buf[x], 39, 1);
		if (x == i->b_len && ++i->error > 0)
			write(2, &"open quote error\n", 17); //a gerer
		if (i->buf[x] == '|')
			return (x);
		++x;
	}
	return (x);
}

int	skip_arg1(t_infos *i, int x)
{
	//printf("	1 i->p_check: %d (x: %d/b_len: %d), tab_nbr: %d\n", i->p_check, x, i->b_len, i->tab_nbr);
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
//	printf("	2 i->p_check: %d -> tqb_nbr: %d\n", i->p_check, i->tab_nbr);
	x = skip_arg1bis(i, x);
	return (x);
}

/* recupere l'argument c et boucle (en ++arg_nbr si il y a un espace avant) 
jusqu'a le renconrer une deuxieme fois ou a depasser b_len (taille du buffer), dans ce cas message d'erreur a gerer
si c = ' ', meme chose*/
/*skip les parties qui ne concernent pas les commandes, 
ajouter les | et les < ici plus tard*/
/*sdf'fsdf'" fdsf"*/