#include "../../lib/minishell.h"

void	print_tabx2(char ***tab, int x)
{
	int	y;

	y = -1;
	printf("\n------------------------tabtab\n");
	while (tab && tab[++x] != NULL)
	{
		printf("tab[%d]:\n", x);
		while (tab[x] != NULL && tab[x][++y] != NULL)
			printf("  tab[%d][%d]: %s\n", x, y, tab[x][y]);
		printf("  tab[%d][%d]: %s\n", x, y, tab[x][y]);
		y = -1;
	}
	if (tab && tab[x] == NULL)
		printf("tab[%d]: NULL\n", x);
	printf("------------------------------\n\n");
	return ;
}
/*imprime un tableau de tableau a partir de x + 1
(akka si on veut imprimer tout le tableau, il faut entrer -1)*/

int	print_tab(char **tab)
{
	int	x;

	x = -1;
	printf("\n\n********* TAB ********\n\n");
	while (tab && tab[++x] != NULL)
		printf("tab[%d]: %s\n", x, tab[x]);
	printf("\n\n**********************\n\n");
	return (x);
}
/*imprime le tableau de chaine "tab" */

int	print_intx2(int *tab)
{
	int x;

	x = -1;
	printf("\n----------\n");
	while (tab && tab[++x])
	{
		printf("tab[%d]: %d\n", x, tab[x]);
	}
	printf("----------\n\n");
	return (0);
}
