#include "../../lib/minishell.h"

int	special_dollars(t_all *a, int x, int *nbr, int mode)
{
	int	y;
	char *spe;

	spe = ft_itoa(a->info.code);
	//printf("%d - > spe: %s\n", a->info.code, spe);
	y = ft_strlen(spe);
	if (mode == 2)
	{
		ft_strlcpy(&a->info.tmp[a->info.nbr2 - 1][++a->info.w], spe, y + 1);
		//printf("y: %d a->info.tmp[a->info.nbr2 - 1][a->info.w %d]: %s\n", y, a->info.w, &a->info.tmp[a->info.nbr2 - 1][a->info.w]);
		a->info.w = a->info.w + y - 1;
	}
	if (mode == 1)
		a->info.l_arg[nbr[0] - 1] = a->info.l_arg[nbr[0] - 1] + y - 1;
	free(spe);
	if (mode == 2)
		return (x + 2);
	return (x + 1);
}

int	add_dollars2(t_all *a, int save)
{
	char	*tmp_env;
	int		y;

	tmp_env = NULL;
	y = 1;
	if (a->info.buf[save + 1] && a->info.buf[save + 1] == '?')
		return (special_dollars(a, save, 0, 2));
	while (a->info.buf[save + y] && (ft_isalnum(a->info.buf[save + y]) == 1 || a->info.buf[save + y] == '_'))
		y++;
	tmp_env = malloc(sizeof(char) * (y));
	if (!tmp_env)
		return(-2); //a gerer
	ft_strlcpy(tmp_env, &a->info.buf[save + 1], y);
	printf("y: %d, tmp_env(save + 1: %d): %s\n", y, save + 1, tmp_env);
	if (find_variable(tmp_env, a->env) == 1)
		var_copy(a, a->info.tmp[a->info.nbr2 - 1], find_var_val(tmp_env, a->env));
	else if (y == 1)
		a->info.tmp[a->info.nbr2 - 1][++a->info.w] = '$';
	save = save + y;
	free(tmp_env);
	return (save);
}

int skip_dollars2(t_all *a, int x, int mode)
{
	if (x + 1 < a->info.b_len && a->info.buf[x + 1])
	{
		if (mode == 1 && a->info.buf[x + 1] == '?')
			return (-3);
		if (mode == 1 && a->info.buf[x + 1] == 34)
			return (-2);
		if (mode == 1 && a->info.buf[x + 1] == 39)
			return (-2);
		if (mode == 2 && a->info.buf[x + 1] == 34)
			return (x + 1);
		if (mode == 2 && a->info.buf[x + 1] == 39)
			return (x + 1);
	}
	return (skip_char(&a->info.buf[x + 1], '_', 2));
}/*mode 2: guillemet
mode 1 : sans guillemet*/


int	skip_dollars(t_all *a, int x, int *nbr)
{
	char	*tmp_env;
	int		y;

	tmp_env = NULL;
	y = skip_dollars2(a, x, 1);
	if (y == -2)
		return (--a->info.l_arg[nbr[0] - 1], x + 1);
	if (y == -3)
		return (special_dollars(a, x, nbr, 1));
	tmp_env = malloc(sizeof(char) * (++y));
	if (!tmp_env)
		return (-2); //a gerer
	ft_strlcpy(tmp_env, &a->info.buf[x + 1], y);
	if (find_variable(tmp_env, a->env) == 1)
		a->info.l_arg[nbr[0] - 1] = a->info.l_arg[nbr[0] - 1] + ft_strlen(find_var_val(tmp_env, a->env)) - 1;
	else if (y != 1)
		a->info.l_arg[nbr[0] - 1] = a->info.l_arg[nbr[0] - 1] - 1;
	free(tmp_env);
	return (y - 1);
}

int count_dollars(t_all *a, int x, int *nbr, int mode)
{
	while (a->info.buf[x] != 34 && x < a->info.b_len)
	{
		if (mode == 1 && a->info.buf[x] == '$')
			x = x + skip_dollars(a, x, nbr);
		else if (mode == 2 && a->info.buf[x] == '$')
			x = x + skip_dollars2(a, x, 2);
		if (mode == 1)
			++a->info.l_arg[nbr[0] - 1];
		x++;
	}
	return (x);
}
/*entree a tester et corriger: |""    f   ""|*/
