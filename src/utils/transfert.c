/*
erreurs:

|
entry:/|/
entry:/||?/
entry:/?| |?/
entry:/?| ||?/
entry:/?|| |?/

>
entry:/?>/
entry:/>|/
entry:/>||?/
entry:/> |?/
entry:/> ||?/
entry:/?>||?/
entry:/?>| |?/
entry:/?>| ||?/

<
entry:/?</
entry:/<?|?/
entry:/<?||?/

*/
/*int		tab_null_assign(char ***tcmd, int n, int x, int m)
{
	tcmd[n] = malloc(sizeof(char *) * (2));
	tcmd[n][0] = malloc(sizeof(char *) * (2));
	tcmd[n][0][0] = '|';
	tcmd[n][0][1] = '\0';
	tcmd[n][1] = NULL;
	if (m == 1)
		return (x + 1);
	tcmd[++n] = malloc(sizeof(char *) * (1));
	tcmd[n][0] = NULL;
	return (x + 1);
}

char	***tab_assign(t_all *a)
{
	int	ntab;
	int	x;
	int null_nbr;
	char ***tcmd;

	ntab = -1;
	x = 0;
	null_nbr = 0;
	printf("pipe nbr: %d; a->info.tab_nbr: %d\n", a->info.n_pipe, a->info.tab_nbr);
	tcmd = malloc(sizeof(char **) * (a->info.n_pipe * 2 + 1));
	if (!tcmd)
		return (NULL);
	while (++ntab + null_nbr <= (a->info.n_pipe * 2 + 1))
	{
		printf("stade %d + null_nbr %d: %s\n", x, null_nbr, a->info.tmp[x]);
		if (a->info.tmp[x] && a->info.tmp[x][0] && a->info.tmp[x][0] == '|')
		{
			if (a->info.tmp[x + 1] && a->info.tmp[x + 1][0] != '|')
				x = tab_null_assign(tcmd, ntab + null_nbr, x, 1);
			else if (++null_nbr > -1)
				x = tab_null_assign(tcmd, ntab + null_nbr - 1, x, 2);
			printf("ici\n");
		}
		else
		{
			tcmd[ntab + null_nbr] = malloc(sizeof(char *) * (a->info.l_tab[ntab]));
			if (!tcmd[ntab + null_nbr])
				printf("malloc erreur a gerer\n");
			x = tab_assign1(a, tcmd[ntab + null_nbr], x, a->info.l_tab[ntab]);
		}
	}
	tcmd[ntab] = NULL;
	return (tcmd);
}*/
/*

int	add_quotes_doll(t_all *a, int x, int save)
{
	if (a->info.buf[x] == 34 && add_red_to_34(a, ++x, save) > 0)
		return (x + skip_char(&a->info.buf[x], 34, 1) + 1);
	else if (a->info.buf[x] == 39 && ++x > 0)
	{
		save = skip_char(&a->info.buf[x], a->info.buf[x - 1], 1);
		ft_strlcpy(&a->info.new_r[a->info.w], &a->info.buf[x], save + 1);
		a->info.w = a->info.w + save - 1;
		return (x + save + 1);
	}
	a->info.w = a->info.w + red_add_dollars(a, x, a->info.w, 1);
	save = skip_char(&a->info.buf[x + 1], '_', 2) + 1;
	if (a->info.buf[x + 1] == '?')
		save = 1;
	return (x + save);
}

char	*add_red2(t_all *a, int x)
{
	int		save;

	a->info.w = -1;
	save = x;
	a->info.new_r = malloc(sizeof(char) * (a->info.red_l + 1));
	if (!a->info.new_r)
		return (a->info.error = 1, NULL);
	while (a->info.buf[save] == a->info.buf[x])
		a->info.new_r[++a->info.w] = a->info.buf[x++];
	if (a->info.q > 0)
		a->info.new_r[++a->info.w] = 39;
	x = skip_space(a->info.buf, x, 1);
	while (++a->info.w < a->info.red_l - a->info.q && a->info.buf[x])
	{
		if (a->info.buf[x] == 34 || a->info.buf[x] == 39 || a->info.buf[x] == '$')
			x = add_quotes_doll(a, x, save);
		else if (is_red(&a->info.buf[x]) == 1 || a->info.buf[x] == '|')
			break ;
		else
			a->info.new_r[a->info.w] = a->info.buf[x++];
	}
	if (a->info.q > 0)
		a->info.new_r[a->info.red_l - 1] = 39;
	a->info.new_r[a->info.red_l] = '\0';
	return (a->info.new_r);
}

*/

int	red_special_dollars(t_all *a, int x, int *nbr, int mode)
{
	int	y;
	char *spe;

	spe = ft_itoa(a->info.code);
	//printf("%d - > spe: %s\n", a->info.code, spe);
	y = ft_strlen(spe);
	/*if (mode == 2)
	{
		ft_strlcpy(&a->info.tmp[a->info.nbr2 - 1][++a->info.w], spe, y + 1);
		//printf("y: %d a->info.tmp[a->info.nbr2 - 1][a->info.w %d]: %s\n", y, a->info.w, &a->info.tmp[a->info.nbr2 - 1][a->info.w]);
		a->info.w = a->info.w + y - 1;
	}*/
	if (mode == 1)
		a->info.red_l = a->info.red_l + y - 1;
	free(spe);
	/*if (mode == 2)
		return (x + 2);*/
	return (x + 1);
}


int	red_skip_dollars(t_all *a, int x)
{
	char	*tmp_env;
	int		y;

	tmp_env = NULL;
	y = skip_dollars2(a, x, 1);
	if (y == -2)
		return (--a->info.red_l, x + 1);
	if (y == -3)
		return (special_dollars(a, x, nbr, 1));
	tmp_env = malloc(sizeof(char) * (++y));
	if (!tmp_env)
		return (a->info.error = 1, -2); //a gerer
	ft_strlcpy(tmp_env, &a->info.buf[x + 1], y);
	if (find_variable(tmp_env, a->env) == 1)
		a->info.red_l = a->info.red_l + ft_strlen(find_var_val(tmp_env, a->env)) - 1;
	else if (y != 1)
	{
		free(tmp_env);
		a->info.red_l = a->info.red_l + 3;
		return (x + 1);
	}
	free(tmp_env);
	return (y - 1);
}

int	red_len(t_all *a, char *buf)
{
	int x;
	int skip;

	x = -1;
	skip = 0;
	while (buf[0] == buf[++x])
		++a->info.red_l;
	x = skip_space(buf, x, 1);
	while (buf[x] && (buf[x] != ' ' && buf[x] != '	'))
	{
		if ((buf[x] == 39 || buf[x] == 34) && ++x > 0)
		{
			printf("a->info.red_l : %d", a->info.red_l);
			skip = skip_char(&buf[x], buf[x - 1], 1);
			a->info.red_l = a->info.red_l + skip;
			printf(" -> %d\n", a->info.red_l);
			x = x + skip;
		}
		else if (buf[x] == '<' || buf[x] == '>' || buf[x] == '|')
			break;
		else if (buf[x] == '$')
		{
			printf("	x: %d; a->info.red_l: %d -> ", x, a->info.red_l);
			x = x + red_skip_dollars(a, x);
			printf("	x: %d; a->info.red_l: %d\n", x, a->info.red_l);
		}
		else if (++a->info.red_l > 0)
			++x;
	}
	printf("result of reb_l : %d, a->info.buf: %s\n", a->info.red_l, a->info.buf);
	return (x);
}

char	*add_red2(t_all *a, int x, int len)
{
	char	*add;
	int		y;
	int		save;

	y = -1;
	save = x;
	a->info.new_red = NULL;
	a->info.new_red = malloc(sizeof(char) * (len + 1));
	if (!a->info.new_red)
		return (a->info.error = 1, NULL);
	while (a->info.buf[save] == a->info.buf[x])
		a->info.new_red[++y] = a->info.buf[x++];
	printf("a->info.new_red[y: %d]: |%c|\n", y, add[y]);
	x = skip_space(a->info.buf, x, 1);
	while (++y < len && a->info.buf[x])
	{
		if (a->info.buf[x] == 39 || a->info.buf[x] == 34)
		{
			save = skip_char(&a->info.buf[x + 1], a->info.buf[x], 1);
			printf("	a->info.new_red: %s, save: %d, y: %d, buf[x: %d + 1]: %s\n", a->info.new_red, y, save, x, &a->info.buf[x + 1]);
			ft_strlcpy(&a->info.new_red[y], &a->info.buf[x + 1], save + 1);
			printf("	a->info.new_red[y: %d]: %s\n", y, &a->info.new_red[y]);
			y = y + save - 1;
			x = x + save + 2;
			printf("a->info.new_red: %s, a->info.new_red[y: %d]: %s, buf[x: %d]: %s\n", a->info.new_red, y, &a->info.new_red[y], x, &a->info.buf[x]);
			continue ;
		}
		else if (a->info.buf[x] == '>' || a->info.buf[x] == '<' || a->info.buf[x] == '|')
			break ;
		/*else if (a->info.buf[x] == '$')
		{
			save = skip_dollar
		}*/
		printf("		a->info.new_red[y: %d]: %s\n", y, &a->info.new_red[y]);
		a->info.new_red[y] = a->info.buf[x++];
		printf("		a->info.new_red[y: %d]: %s\n", y, &a->info.new_red[y]);
		
	}
	a->info.new_red[y] = '\0';
	return (a->info.new_red);
}

char	*add_red(t_all *a, int x)
{
	int	save;

	a->info.red_l = 0;	
	a->info.new_red = NULL;
	save = red_len(a, &a->info.buf[x], 2);
	add_red2(a, x);
	if (!a->info.new_red)
		return (NULL);
	if (remove_red(&a->info, x, save) == -2)
		return (a->info.error = 1, NULL);
	return (a->info.new_red);
}
/*
save: dernier chara de la red - 1er chara de la red = save
(taille du nom de la redirection avec chara en plus)
(ex: |ls > ici|: 5; |ls >ici |: 4; |ls >"ici "| : 7)
		 11111			1111		   1111111
a->info.red_l: taille finale de la red sans prendre en compte les guillemets
(ex: |ls > ici|: 4; |ls >ici |: 4; |ls >"ici "| : 5)
		 1 111			1111		   1 1111
a->info.new_red: nouvelle redirection a ajouter
*/

/*int	skip_quotes(t_all *a, char *buf, int x)
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
	int	skip;

	x = -1;
	skip = 0;
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
	}
	return (x);
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
			x = x + skip_char(&i->buf[x], i->buf[x - 1], 1);
		else if (is_red(&i->buf[x]) == 1 && add_red(a, --x, ++n) == -2)
			return (i->error = 1, -2);
		else if (i->buf[x] == '|' && is_pipe(&i->red_tab[++n]) == -2)
			return (i->error = 1, -2);
	}
	i->red_tab[++n] = NULL;
	print_tab(i->red_tab);
	return (0);
}

>fdasf' ' |>"$USER"

*/

/*
int	skip_red_to_34(t_all *a, char *buf, int x, int len)
{
	int	quote;
	int	dol;

	quote = skip_char(&buf[x], 34, 1); // buf[quote] = |"|
	if (a->info.q <= 0 && ft_c_count(' ', &buf[x], 2) <= quote)
		a->info.q = 1;
	quote = quote + x;
	dol = x;
	while (x < quote)
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

int	red_len(t_all *a, char *buf)
{
	int x;
	int skip;

	x = -1;
	skip = 0;
	while (buf[0] == buf[++x])
		++a->info.red_l;
	x = skip_space(buf, x, 1);
	while (x < a->info.b_len && buf[x] && (buf[x] != ' ' && buf[x] != '	'))
	{
		if (buf[x] == 34 && ++x > 0)
			x = skip_red_to_34(a, buf, x, skip);
		else if (buf[x] == 39 && ++x > 0)
		{
			skip = skip_char(&buf[x], buf[x - 1], 1);
			if (a->info.q <= 0 && (ft_c_count(' ', &buf[x], 2) < skip || ft_c_count('$', &buf[x], 2 < skip)))
				a->info.q = 1;
			a->info.red_l = a->info.red_l + skip;
			x = x + skip + 1;
		}
		else if (buf[x] == '<' || buf[x] == '>' || buf[x] == '|')
			break;
		else if (buf[x] == '$')
			x = x + red_skip_dollars(a, buf, x, 1);
		else if (++a->info.red_l > 0)
			++x;
	}
	return (x);
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
			x = x + skip_char(&i->buf[x], i->buf[x - 1], 1);
		else if (is_red(&i->buf[x]) == 1 && ++n < nb)
		{
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
	return (0);*/