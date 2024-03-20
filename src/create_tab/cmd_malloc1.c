#include "../../lib/minishell.h"

int	tab_assign1(t_all *a, char **tab, int bx, int len)
{
	int	x;

	x = -1;
	while (++x < len - 1 && a->info.tmp[bx + x])
	{
		if (a->info.tmp[bx + x][0] == '<') // '>'
		{
			printf("alternative redirection a gerer\n");
			//tab[x] = ft_strdup(a->info.redirectiontab);
		}
		//else
		tab[x] = ft_strdup(a->info.tmp[bx + x]);
		if (tab[x] == NULL)
			printf("malloc erreur a gerer\n");
	}
	printf("len: %d, x: %d\n", len, x);
	tab[x] = NULL;
	return (bx + len - 1);
}

char	***tab_assign(t_all *a)
{
	int	ntab;
	int	x;
	char ***tcmd;

	ntab = -1;
	x = 0;
	tcmd = malloc(sizeof(char **) * (a->info.tab_nbr + 2));
	if (!tcmd)
		return (NULL);
	while (++ntab <= a->info.tab_nbr)
	{
		tcmd[ntab] = malloc(sizeof(char *) * (a->info.l_tab[ntab]));
		if (!tcmd[ntab])
			printf("malloc erreur a gerer\n");
		x = tab_assign1(a, tcmd[ntab], x, a->info.l_tab[ntab]);
	}
	tcmd[ntab] = NULL;
	return (tcmd);
}

int	new_argument(t_all *a, int x, int save, int *nbr)
{
	a->info.w = -1;
	a->info.tmp[nbr[0] - 1] = malloc(sizeof(char) * a->info.l_arg[nbr[0] - 1]);
	//printf("string length: %d\n", a->info.l_arg[nbr[0] - 1]);
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
			if (a->info.buf[save] == 34 || a->info.buf[save] == 39)
				continue;
			if (a->info.buf[save] != '\0')
				a->info.tmp[nbr[0] - 1][++a->info.w] = a->info.buf[save];
		}
		++save;
	}
	a->info.tmp[nbr[0] - 1][++a->info.w] = '\0';
	return (0);
}

/*test: echo ee|cat||
echo fds|cat||
echo dsf|hjy||
echo dsf|hjy||
echo | cat |fdsfsd|
echo fdsfs| fdsf|fdsfsd*/