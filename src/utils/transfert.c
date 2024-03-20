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


int	new_argument(t_all *a, int x, int save, int *nbr)
{
	a->info.w = -1;
	a->info.tmp[nbr[0] - 1] = malloc(sizeof(char) * a->info.l_arg[nbr[0] - 1]);
	printf("string length: %d\n", a->info.l_arg[nbr[0] - 1]);
	if (!a->info.tmp[nbr[0] - 1] && printf("erreur a gerer\n"))
		return(-2);
	while (save < x)
	{
		if (a->info.buf[save] == 34)//""
		{
			while (++save < x && a->info.buf[save] != 34)
			{
				if (a->info.buf[save] == '$')
					save = add_dollars2(a, save);
				if (a->info.buf[save] != 34)
					a->info.tmp[nbr[0] - 1][++a->info.w] = a->info.buf[save];
			}
		}
		else if (a->info.buf[save] == 39)//''
		{
			while (++save < x && a->info.buf[save] != 39)
				a->info.tmp[nbr[0] - 1][++a->info.w] = a->info.buf[save];
		}
		else if (a->info.buf[save] == '$')
		{
			if (a->info.buf[save + 1] && (a->info.buf[save + 1] == 34 || a->info.buf[save + 1] == 39))
			{
				++save;
				continue;
			}
			save = add_dollars2(a, save);
			if (a->info.buf[save] != '\0')
				a->info.tmp[nbr[0] - 1][++a->info.w] = a->info.buf[save];
		}
		else if (a->info.buf[save] != '\0')
			a->info.tmp[nbr[0] - 1][++a->info.w] = a->info.buf[save];
		++save;
	}
	a->info.tmp[nbr[0] - 1][++a->info.w] = '\0';
	return (0);
}

int	new_argument(t_all *a, int x, int save, int *nbr)
{
	a->info.w = -1;
	a->info.tmp[nbr[0] - 1] = malloc(sizeof(char) * a->info.l_arg[nbr[0] - 1]);
	printf("string length: %d\n", a->info.l_arg[nbr[0] - 1]);
	if (!a->info.tmp[nbr[0] - 1] && printf("erreur a gerer\n"))
		return(-2);
	while (save < x)
	{
		if (a->info.buf[save] == 34)//""
		{
			while (++save < x && a->info.buf[save] != 34)
			{
				if (a->info.buf[save] == '$')
					save = add_dollars2(a, save);
				if (a->info.buf[save] != 34)
					a->info.tmp[nbr[0] - 1][++a->info.w] = a->info.buf[save];
			}
		}
		else if (a->info.buf[save] == 39)//''
		{
			while (++save < x && a->info.buf[save] != 39)
				a->info.tmp[nbr[0] - 1][++a->info.w] = a->info.buf[save];
		}
		else if (a->info.buf[save] != 34 && a->info.buf[save] != 39)
		{
			if (a->info.buf[save] == '$' && a->info.buf[save + 1] && (a->info.buf[save + 1] == 34 || a->info.buf[save + 1] == 39))
			{
				++save;
				continue;
			}
			if (a->info.buf[save] == '$')
				save = add_dollars2(a, save);
			if (a->info.buf[save] != '\0')
				a->info.tmp[nbr[0] - 1][++a->info.w] = a->info.buf[save];
		}
		++save;
	}
	a->info.tmp[nbr[0] - 1][++a->info.w] = '\0';
	return (0);
}

int	skip_arg2(t_all *a, int x, int *nbr)
{
	int	save;

	save = -1;
	printf("0");
	if (x >= a->info.b_len)
		return (x);
	printf("0\n");
	if (x == 0 || a->info.buf[x] == '|' || a->info.buf[x - 1] == '|')
	{
		nbr[0] = nbr[0] + 1;
		a->info.l_arg[nbr[0] - 1] = 1;
		save = x;
		printf("1\n");
	}
	else if (a->info.buf[x - 1] == ' ' || a->info.buf[x - 1] == '	')
	{
		nbr[0] = nbr[0] + 1;
		a->info.l_arg[nbr[0] - 1] = 1;
		save = x;
		printf("2\n");
	}
	x = skip_arg2bis(a, x, nbr);
	if (save != -1 && new_argument(a, x, save, nbr) == -2)
		printf("malloc error potentielle a gérer\n"); //a gerer
	return (x);
}

int	skip_arg2bis(t_all *a, int x, int *nbr)
{
	if (a->info.buf[x] == '|' && ++a->info.l_arg[nbr[0] - 1] >= 0)
		return (++x);
	while (x < a->info.b_len && a->info.buf[x] != ' ' && a->info.buf[x] != '	')
	{
		if (a->info.buf[x] != 34 && a->info.buf[x] != 39 && a->info.buf[x] != '|')
		{
			if (a->info.buf[x] == '$')
				x = skip_dollars(a, x, nbr);
			++a->info.l_arg[nbr[0] - 1];
		}
		if (a->info.buf[x] == 34)
			x = count_dollars(a, ++x, nbr);
		if (a->info.buf[x] == 39)
		{
			++x;
			while (a->info.buf[x] != 39 && ++x < a->info.b_len)
				++a->info.l_arg[nbr[0] - 1];
			if (x == a->info.b_len)
				printf("open single quote error\n"); //a gerer
		}
		if (a->info.buf[x] == '|')
			return (x);
		++x;
	}
	return (x);
}


int	fct_test_big_tab(t_all *a,int x, int *nbr)
{
	printf("			1 a->info.p_check: %d -> tqb_nbr: %d\n", a->info.p_check, a->info.tab_nbr);
	if (x == 0 || a->info.tab_nbr == -1)
	{
		a->info.l_tab[++a->info.tab_nbr] = 1;
	}
	if (x < a->info.b_len && (x == 0 || a->info.buf[x] == '|' || a->info.buf[x - 1] == '|'))
	{
		if (x != 0 && (a->info.buf[x] == '|'))
		{
			if (a->info.tab_nbr == 0)
				a->info.l_tab[a->info.tab_nbr]++;
			a->info.p_check = 1;
		}
		else if (x != 0)
			a->info.p_check = 0;
		if (a->info.buf[x] == '|' || a->info.buf[x - 1] == '|')
			a->info.l_tab[++a->info.tab_nbr] = 2;
		else if (x == 0)
			a->info.l_tab[++a->info.tab_nbr] = 1;
		nbr[0] = nbr[0] + 1;
		a->info.l_arg[nbr[0] - 1] = 1;
	}
	else if (x < a->info.b_len && (a->info.buf[x - 1] == ' ' || a->info.buf[x - 1] == '	'))
	{
		if (a->info.p_check == 1 || a->info.tab_nbr == -1)
			a->info.l_tab[++a->info.tab_nbr] = 1;
		a->info.p_check = 0;
		a->info.l_tab[a->info.tab_nbr]++;
		nbr[0] = nbr[0] + 1;
		a->info.l_arg[nbr[0] - 1] = 1;
	}
	printf("			2 a->info.p_check: %d -> l_tab[tqb_nbr:%d] %d\n", a->info.p_check, a->info.tab_nbr, a->info.l_tab[a->info.tab_nbr]);
	x = skip_arg2bis(a, x, nbr);
	return (x);
}
//sdf'fsdf'" fdsf"

int	skip_dollars(t_all *a, int x, int *nbr)
{
	char	*tmp_env;
	int		y;

	tmp_env = NULL;
	y = 1;
	if (x + y < a->info.b_len && a->info.buf[x + y] && (a->info.buf[x + y] == 34 || a->info.buf[x + y] == 39))
		return (--a->info.l_arg[nbr[0] - 1], x + 1);
	printf("	buf[%d(x)]: %c, buf[%d(x + y)]: %c\n", x, a->info.buf[x], x + y, a->info.buf[x + y]);
	while (x + y < a->info.b_len && a->info.buf[x + y] && (ft_isalnum(a->info.buf[x + y]) == 1 || a->info.buf[x + y] == '_'))
		y++;
	tmp_env = malloc(sizeof(char) * (y));
	if (!tmp_env)
		return(-2); //a gerer
	ft_strlcpy(tmp_env, &a->info.buf[x + 1], y);
	if (find_variable(tmp_env, a->env) == 1)
		a->info.l_arg[nbr[0] - 1] = a->info.l_arg[nbr[0] - 1] + ft_strlen(find_var_val(tmp_env, a->env)) - 1;
	else if (y != 1)
		a->info.l_arg[nbr[0] - 1] = a->info.l_arg[nbr[0] - 1] - 1;
	x = x + y - 1;
	printf("buf[%d(x)]: %c, buf[%d(x + y)]: %c\n", x, a->info.buf[x], x + y, a->info.buf[x + y]);
	//printf("a->info.l_arg[nbr[0] - 1]: %d\n", a->info.l_arg[nbr[0] - 1]);
	free(tmp_env);
	return (x);
}

int	skip_dollars(t_all *a, int x, int *nbr)
{
	char	*tmp_env;
	int		y;

	tmp_env = NULL;
	y = skip_dollars2(a, x, 1);
	if (y == -2)
		return (--a->info.l_arg[nbr[0] - 1], x + 1);
	printf("	buf[%d(x)]: %c, buf[%d(x + y)]: %c\n", x, a->info.buf[x], x + y, a->info.buf[x + y]);
	tmp_env = malloc(sizeof(char) * (y));
	if (!tmp_env)
		return(-2); //a gerer
	ft_strlcpy(tmp_env, &a->info.buf[x + 1], y);
	if (find_variable(tmp_env, a->env) == 1)
		a->info.l_arg[nbr[0] - 1] = a->info.l_arg[nbr[0] - 1] + ft_strlen(find_var_val(tmp_env, a->env)) - 1;
	else if (y != 1)
		a->info.l_arg[nbr[0] - 1] = a->info.l_arg[nbr[0] - 1] - 1;
	x = x + y - 1;
	printf("buf[%d(x)]: %c, buf[%d(x + y)]: %c\n", x, a->info.buf[x], x + y, a->info.buf[x + y]);
	//printf("a->info.l_arg[nbr[0] - 1]: %d\n", a->info.l_arg[nbr[0] - 1]);
	free(tmp_env);
	return (x);
}

