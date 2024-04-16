/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_buf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 10:02:02 by cbuyurha          #+#    #+#             */
/*   Updated: 2024/04/11 17:28:25 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

int	check_begin5(t_infos *i, int x, int y)
{
	if (rev_red_err1(i, x + 2, 2) == -2)
		return (-2);
	y = skip_space(i->buf, x + 3, 1);
	if (two_pipe_err(i, y, 1) == -2)
		return (-2);
	if (i->buf[y] == '<')
	{
		if (i->buf[y + 1] && i->buf[y + 1] == '<')
		{
			if (i->buf[y + 2] && i->buf[y + 2] == '<')
				return (i->error = 13, -2);
			return (i->error = 10, -2);
		}
		return (rev_red_err1(i, y + 1, 4));
	}
	return (i->error = 11, -2);
}

int	check_begin4(t_infos *i, int x, int y)
{
	if (rev_red_err1(i, x + 1, 2) == -2)
		return (-2);
	if (i->buf[x + 2] && i->buf[x + 2] == '<')
		return (check_begin5(i, x, y));
	y = skip_space(i->buf, x + 2, 1);
	if (two_pipe_err(i, y, 1) == -2)
		return (-2);
	if (i->buf[y] == '<')
	{
		if (i->buf[y + 1] && i->buf[y + 1] == '<')
			return (i->error = 10, -2);
		return (i->error = 11, -2);
	}
	return (0);
}

int	check_begin3(t_infos *i, int x, int y)
{
	if (i->buf[x] == '<')
	{
		if (rev_red_err1(i, x + 1, 1) == -2)
			return (-2);
		if (i->buf[x + 1] && i->buf[x + 1] == '<')
			return (check_begin4(i, x, y));
		y = skip_space(i->buf, x + 1, 1);
		if (two_pipe_err(i, y, 1) == -2)
			return (-2);
		if (i->buf[y] == '<')
		{
			if (i->buf[y + 1] && i->buf[y + 1] == '<')
				return (i->error = 10, -2);
			return (i->error = 11, -2);
		}
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
		if (check_begin3(i, x, y) == -2)
			return (-2);
	}
	return (0);
}

int	check_buf(t_infos *i)
{
	int	x;

	i->error = 0;
	x = skip_space(i->buf, 0, 1);
	if (check_begin1(i, x) != 0)
		return (-2);
	while (x < i->b_len && i->buf[x] && i->error <= 0)
	{
		x = skip_space(i->buf, x, 1);
		if (x >= i->b_len)
			break ;
		x = check_middle(i, x);
	}
	if (i->error > 0)
		return (-2);
	return (x);
}
