/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_red.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuyurha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:15:13 by cbuyurha          #+#    #+#             */
/*   Updated: 2024/03/14 12:15:23 by cbuyurha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

int	skip_red_to_34(t_all *a, char *buf, int x, int len)
{
	int	quote;
	int	dol;

	quote = skip_char(&buf[x], 34, 1);
	if (a->info.q <= 0 && ft_c_count(' ', &buf[x], 2) <= quote)
		a->info.q = 1;
	quote = quote + x;
	dol = x;
	while (x < quote && a->info.error <= 0)
	{
		len = skip_char(&buf[x], '$', 4);
		dol = dol + len;
		x = x + len;
		a->info.red_l = a->info.red_l + len;
		if (buf[x] == '$')
		{
			if (buf[x + 1] == 34)
				a->info.red_l--;
			x = x + red_skip_dollars(a, buf, x, 3);
			if (x == quote)
				a->info.red_l++;
		}
	}
	return (x + 1);
}

int	skip_quotes(t_all *a, char *buf, int x)
{
	int	len;

	if (buf[x - 1] == 34)
		return (skip_red_to_34(a, buf, x, 0));
	len = skip_char(&buf[x], buf[x - 1], 1);
	if (ft_c_count(' ', &buf[x], 2) < len || ft_c_count('$', &buf[x], 2 < len))
		a->info.q = 1;
	a->info.red_l = a->info.red_l + len;
	return (len + x + 1);
}

int	red_len(t_all *a, char *buf)
{
	int	x;

	x = -1;
	while (buf[0] == buf[++x])
		++a->info.red_l;
	x = skip_space(buf, x, 1);
	while (x < a->info.b_len && buf[x] && (buf[x] != ' ' && buf[x] != '	'))
	{
		if (buf[x] == 34 || buf[x] == 39)
			x = skip_quotes(a, buf, ++x);
		else if (buf[x] == '<' || buf[x] == '>' || buf[x] == '|')
			break ;
		else if (buf[x] == '$')
			x = x + red_skip_dollars(a, buf, x, 1);
		else if (++a->info.red_l > 0)
			++x;
		if (a->info.error > 0)
			break ;
	}
	return (x);
}

int	add_red(t_all *a, int x, int n)
{
	int	save;

	a->info.red_l = 0;
	a->info.new_r = NULL;
	save = red_len(a, &a->info.buf[x]);
	if (a->info.error > 0)
		return (-2);
	printf("	red_l: %d -> ", a->info.red_l);
	if (a->info.q > 0)
		a->info.red_l = a->info.red_l + 2;
	printf("%d\n", a->info.red_l);
	add_red2(a, x);
	printf("new_r: %s\n", a->info.new_r);
	a->info.red_tab[n] = a->info.new_r;
	if (a->info.error > 0)
		return (-2);
	if (!a->info.red_tab[n] || remove_red(&a->info, x, save) == -2)
		return (a->info.error = 1, -2);
	return (0);
}
/*		>fdasf' ' >"$USER">fdsaf*/

int	red_init(t_all *a, t_infos *i, int x, int n)
{
	int	nb;

	nb = a->info.red_n + i->n_pipe + 1;
	if (i->red_n == 0)
		return (i->red_tab = NULL, 0);
	i->red_tab = malloc(sizeof(char *) * (nb));
	if (!i->red_tab)
		return (i->error = 1, -2);
	while (n < nb - 2 && ++x < i->b_len && i->buf[x] && i->error <= 0)
	{
		if ((i->buf[x] == 34 || i->buf[x] == 39) && ++x < i->b_len)
			x = x + skip_char(&i->buf[x], i->buf[x - 1], 1);
		else if (is_red(&i->buf[x]) == 1 && add_red(a, x, ++n) != -2)
			--x;
		else if (i->buf[x] == '|')
			is_pipe(a, &i->red_tab[++n]);
	}
	if (i->error > 0)
		return (-2);
	i->red_tab[++n] = NULL;
	print_tab(i->red_tab);
	return (0);
}

/*cbuyurha@paul-f4Ar5s6:~/Desktop/test$ ls
'$'   0   cbuyurhacbuyurha
cbuyurha@paul-f4Ar5s6:~/Desktop/test$ cat $
sd
cbuyurha@paul-f4Ar5s6:~/Desktop/test$ cat <0>$
bash: syntax error near unexpected token `0'
cbuyurha@paul-f4Ar5s6:~/Desktop/test$ cat <0 >$
cbuyurha@paul-f4Ar5s6:~/Desktop/test$ cat $
*/
