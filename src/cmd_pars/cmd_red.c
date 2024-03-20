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

int	is_red(char *s)
{
	int	x;

	x = 0;
	if (s[x] == '<' || s[x] == '>')
		return (1);
	return (0);
}

char	*is_pipe(char *s)
{
	printf("ispipe\n");
	s = malloc(sizeof(char) * 2);
	if (!s)
		return (NULL);
	s[0] = '|';
	s[1] = '\0';
	printf("s[n]: %s\n", s);
	return (s);
}

int	red_len(t_all *a, char *buf, int mode)
{
	int	len;
	int x;

	len = 0;
	x = -1;
	while (buf[0] == buf[++x])
		++len;
	x = skip_space(buf, x, 1);
	while (buf[x] && (buf[x] != ' ' && buf[x] != '	'))
	{
		if ((buf[x] == 39 || buf[x] == 34) && ++x > 0)
		{
			printf("len : %d", len);
			len = len + skip_char(&buf[x], buf[x - 1], 1);
			printf(" -> %d\n", len);
			x = x + len;
		}
		else if (buf[x] == '<' || buf[x] == '>' || buf[x] == '|')
			break;
		else if (++len > 0)
			++x;
	}
	printf("result of reb_len : %d, a->info.buf: %s\n", len, a->info.buf);
	if (mode == 2)
		return (x);
	return (len);
}

char	*add_red2(t_all *a, int x, int len)
{
	char	*add;
	int		y;
	int		save;

	y = -1;
	save = x;
	add = malloc(sizeof(char) * (len + 1));
	if (!add)
		return (a->info.error = 1, NULL);
	while (a->info.buf[save] == a->info.buf[x])
		add[++y] = a->info.buf[x++];
	printf("add[y: %d]: |%c|\n", y, add[y]);
	x = skip_space(a->info.buf, x, 1);
	while (++y < len && a->info.buf[x])
	{
		if (a->info.buf[x] == 39 || a->info.buf[x] == 34)
		{
			save = skip_char(&a->info.buf[x + 1], a->info.buf[x], 1);
			printf("	add: %s, save: %d, y: %d, buf[x: %d + 1]: %s\n", add, y, save, x, &a->info.buf[x + 1]);
			ft_strlcpy(&add[y], &a->info.buf[x + 1], save + 1);
			printf("	add[y: %d]: %s\n", y, &add[y]);
			y = y + save - 2;
			x = x + save;
			continue ;
		}
		else if (a->info.buf[x] == '>' || a->info.buf[x] == '<' || a->info.buf[x] == '|')
			break ;
		/*else if (a->info.buf[x] == '$')
		{
			save = skip_dollar
		}*/
		printf("		add[y: %d]: %s\n", y, &add[y]);
		add[y] = a->info.buf[x++];
		printf("		add[y: %d]: %s\n", y, &add[y]);
		
	}
	add[y] = '\0';
	return (add);
}

int	remove_red(t_infos *i, int x, int len, int save)
{
	char	*tmp;

	tmp = malloc(sizeof(char) +(i->b_len - len + 1));
	printf("i->b_len(%d) - len(%d) + 1: %d\n", i->b_len, len, i->b_len - len + 1);
	if (!tmp)
		return (i->error = 1, -2);
	ft_strlcpy(tmp, i->buf, x + 1);
	printf("tmp: |%s|\n", tmp);
	ft_strlcpy(&tmp[x], &i->buf[x + save], i->b_len - x - len + 1);
	printf("tmp: |%s|\n", tmp);
	tmp[i->b_len - len + 1] = '\0';
	printf("tmp: |%s|\n", tmp);
	i->b_len = ft_strlen(tmp);
	free(i->buf);
	i->buf = tmp;
	return (0);
}

char	*add_red(t_all *a, int x)
{
	char	*add;
	int 	len;
	int		save;
	
	len = red_len(a, &a->info.buf[x], 1);
	save = red_len(a, &a->info.buf[x], 2);
	printf("		len: %d, save: %d\n", len, save);
	add = add_red2(a, x, len);
	printf("add: |%s|\n", add);
	if (!add)
		return (NULL);
	if (remove_red(&a->info, x, len, save) == -2)
		return (a->info.error = 1, NULL);
	return (add);
}

int	red_init(t_all *a, t_infos *i)
{
	int	n;
	int	nb;
	int	x;

	n = -1;
	x = -1;
	nb = a->info.red_n + i->n_pipe + 1;
	if (i->red_n == 0)
		return (i->red_tab = NULL, 0);
	i->red_tab = malloc(sizeof(char *) * (nb));
	if (!i->red_tab)
		return (i->error = 1, -2);
	while (++x < i->b_len && n < nb && i->buf[x])
	{
		if ((i->buf[x] == 34 || i->buf[x] == 39) && ++x < i->b_len)
		{
			x = x + skip_char(&i->buf[x], i->buf[x - 1], 1);
			printf("pppppppppp: i->buf[x: %d]: |%c|\n", x, i->buf[x]);
		}
		else if (is_red(&i->buf[x]) == 1 && ++n < nb)
		{
			printf("detected at %d : |%s|\n", x, &i->buf[x]);
			i->red_tab[n] = add_red(a, x);
			if (!i->red_tab[n])
				return (i->error = 1, -2);
			x--;
		}
		else if (i->buf[x] == '|' && ++n < nb)
		{
			i->red_tab[n] = is_pipe(i->red_tab[n]);
			if (!i->red_tab[n])
				return (i->error = 1, -2);
		}
			
	}
	i->red_tab[++n] = NULL;
	printf("n: %d/ nb: %d - 1, printf: %s\n", n, nb, i->buf);
	print_tab(i->red_tab);
	return (0);
}

/*ls >dsf|">dfe" l*/
/*">fds" > l | ">fd"*/
/*cbuyurha@paul-f4Ar5s6:~/Desktop/test$ ls
'$'   0   cbuyurhacbuyurha
cbuyurha@paul-f4Ar5s6:~/Desktop/test$ cat $
sd
cbuyurha@paul-f4Ar5s6:~/Desktop/test$ cat <0>$
bash: syntax error near unexpected token `0'
cbuyurha@paul-f4Ar5s6:~/Desktop/test$ cat <0 >$
cbuyurha@paul-f4Ar5s6:~/Desktop/test$ cat $
*/