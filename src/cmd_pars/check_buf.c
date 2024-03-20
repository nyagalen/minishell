/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_buf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuyurha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:02:02 by cbuyurha          #+#    #+#             */
/*   Updated: 2024/03/11 10:02:04 by cbuyurha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

int	pars_error(int error);

int	two_pipe_err(t_infos *i, int x, int mode)
{
	if (mode == 1 && !i->buf[x])
		return (i->error = 6, -2);
	if (mode == 2 && !i->buf[x])
		return (i->error = 5, -2);
	if (i->buf[x] == '|')
	{
		if (i->buf[x + 1] && i->buf[x + 1] == '|')
			return (i->error = 4, -2);
		return (i->error = 3, -2);
	}
	return (0);
}

int	check_begin2(t_infos *i, int x, int y)
{
	if (i->buf[x] == '>')
	{
		if (i->buf[x + 1] && i->buf[x + 1] == '|')
		{
			if (i->buf[x + 2] && i->buf[x + 2] == '|')
				return (i->error = 3, -2);
			y = skip_space(i->buf, x + 2, 1);
			if (two_pipe_err(i, y, 1) == -2)
				return (-2);
			if (i->buf[y] == '>')
			{
				if (i->buf[y + 1] && i->buf[y + 1] == '|')
					return (i->error = 8, -2);
				return (i->error = 7, -2);
			}
			return (0);
		}
		y = skip_space(i->buf, x + 1, 1);
		if (two_pipe_err(i, y, 1) == -2)
			return (-2);
	}
	return (0);
}

int	check_begin1(t_infos *i, int x)
{
	int	y;

	y = 0;
	if (x < i->b_len && i->buf[x])
	{
		if (two_pipe_err(i, x, 2) == -2)
			return (-2);
		if (check_begin2(i, x, y) == -2)
			return (-2);
		if (i->buf[x] == '<')
		{
			y = skip_space(i->buf, x + 1, 1);
			if (two_pipe_err(i, y, 1) == -2)
				return (-2);
		}
	}
	return (0);
}

int check_pipes(t_infos *i, int x);
int	check_middle(t_infos *i, int save);

int	check_buf(t_infos *i)
{
	int	x;

	printf("buf: %s\n", i->buf);
	x = skip_space(i->buf, 0, 1);
	if (check_begin1(i, x) != 0)
		return (-2);
	while (x < i->b_len && i->buf[x] && i->error <= 0)
	{
		printf("\nx: %d ", x);
		x = skip_space(i->buf, x, 1);
		printf("- > x: %d\n", x);
		if (x >= i->b_len)
			break ;
		x = check_middle(i, x);
	}
	printf("\n\ni->buf: %s", i->buf);
	printf("\n		i->red_n: %d\n", i->red_n);
	printf("		i->arg_nbr: %d, i->tab_nbr: %d, n_pipe: %d\n", i->arg_nbr, i->tab_nbr, i->n_pipe);
	printf("		x: %d / b_len: %d ; error: %d\n\n", x, i->b_len, i->error);
	if (i->error > 0)
		return (-2);
	return (x);
}
