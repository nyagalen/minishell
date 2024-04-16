/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuyurha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 19:44:51 by cbuyurha          #+#    #+#             */
/*   Updated: 2024/04/05 19:44:55 by cbuyurha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

int	tab_assign1(t_all *a, char **tab, int bx, int len)
{
	int	x;

	x = -1;
	while (a->info.error <= 0 && ++x < len - 1 && a->info.tmp[bx + x])
	{
		tab[x] = ft_strdup(a->info.tmp[bx + x]);
		if (tab[x] == NULL)
			return (a->info.error = 1, len);
	}
	if (a->info.error <= 0)
		tab[x] = NULL;
	return (bx + len - 1);
}

char	***assign_null(t_all *a, char ***tcmd)
{
	tcmd = malloc(sizeof(char **) * 2);
	if (!tcmd)
		return (a->info.error = 1, NULL);
	tcmd[0] = malloc(sizeof(char *) * 1);
	if (!tcmd[0])
	{
		free(tcmd);
		return (a->info.error = 1, NULL);
	}
	tcmd[0][0] = NULL;
	tcmd[1] = NULL;
	return (tcmd);
}

char	***tab_assign(t_all *a)
{
	int		ntab;
	int		x;
	char	***tcmd;

	ntab = -1;
	x = 0;
	if (a->info.tab_nbr == -1)
		return (assign_null(a, NULL));
	tcmd = malloc(sizeof(char **) * (a->info.tab_nbr + 2));
	if (!tcmd)
		return (a->info.error = 1, NULL);
	while (++ntab <= a->info.tab_nbr && a->info.error <= 0)
	{
		tcmd[ntab] = malloc(sizeof(char *) * (a->info.l_tab[ntab]));
		if (!tcmd[ntab])
			a->info.error = 1;
		x = tab_assign1(a, tcmd[ntab], x, a->info.l_tab[ntab]);
	}
	if (a->info.error > 0)
	{
		tcmd = free_tab3(tcmd);
		return (NULL);
	}
	tcmd[ntab] = NULL;
	return (tcmd);
}

/*test: echo ee|cat||
echo fds|cat||
echo dsf|hjy||
echo dsf|hjy||
echo | cat |fdsfsd|
echo fdsfs| fdsf|fdsfsd*/
