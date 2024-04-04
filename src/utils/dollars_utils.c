/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuyurha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:46:53 by cbuyurha          #+#    #+#             */
/*   Updated: 2024/03/15 16:46:58 by cbuyurha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
/*
spe: i->code converti en char

mode 1: récupére la taille de spé et l'ajoute a l_arg[nbr - 1] en retirant le $
	retourne: index de buf - 1
mode 2: copie spé a l'emplacement &a->info.tmp[a->info.nbr2 - 1][++a->info.w]
pour y + 1 characteres; me a jour l'index de a->info.tmp[a->info.nbr2 - 1]
	retourne: index de buf - 2
*/

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

int skip_dollars2(t_all *a, int x, int m)
{
	char	c;

	c = a->info.buf[x + 1];
	if (x + 1 < a->info.b_len && a->info.buf[x + 1])
	{
		if (m == 1 && c == '?')
			return (-3);
		if (m == 1 && (c == 34 || c == 39))
			return (-2);
		if (m == 2 && (c == 34 || c == 39))
			return (x + 1);
	}
	return (skip_char(&a->info.buf[x + 1], '_', 2)); //retourne la taille du dollars
}
/*mode 2: guillemet (si le dollars est entoure de quote)
(si le $ est entoure de quote 
akka pas forcement de l'arg a partir du premier chara non alphanum hors '_')
->retourne x + 1 en cas de quote (le nom du $ n'existe pas -> val $ == NULL)
-> retourne skip_char (la taille du nom du $ (fin $ = chara non alphanumerique hors '_'))

mode 1 : sans guillemet 
(si le $ n'est pas entoure de quote 
akka fin de l'arg a partir du premier chara non alphanum hors '_')
-> retourne -2 en cas de quote (indique val $ == NULL)
-> retourne -3 en cas de $? (comportement special)
-> retourne skip_char (la taille du nom du $ (fin $ = chara non alphanumerique hors '_'))
*/


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
		return (a->info.error = 1, -2); //a gerer
	ft_strlcpy(tmp_env, &a->info.buf[x + 1], y);
	if (find_variable(tmp_env, a->env) == 1)
		a->info.l_arg[nbr[0] - 1] = a->info.l_arg[nbr[0] - 1] + ft_strlen(find_var_val(tmp_env, a->env)) - 1;
	else if (y != 1)
		a->info.l_arg[nbr[0] - 1] = a->info.l_arg[nbr[0] - 1] - 1;
	free(tmp_env);
	return (y - 1);
}
/*
tmp_env: destine a contenir le nom du $ (ex: |ls $USER"fds"| : |USER|)

y = skip_dollars2(a, x, 1); -> verifie que le nom 
ne commence pas par un quote ou un ?

si y = -2 (buf[x] -> quote) 
	retourne: l'index mis a jour au niveau de la quote + decremente le $ de l_arg[nbr[0] - 1]

si y = -3 (buf[x] -> ?)
	retourne: l'indexe mis a jour renvoye par special_dollars qui traite les $?

malloc tmp_env avec la taille du nom du $

copie dans tmp_env a partir de buf[x] (char apres le $) pour 'y' chara (taille du nom du $)
tmp_env contient maintenant le nom du $ (ex: |echo $USER"fdsf"| -> |USER|; |echo $USERfdsf | -> |USERfdsf|)

find_variable renvoie 1 si le nom dans tmp_env existe

si le nom du $ existe additionne 
la taille de la valeur du $ a l_arg[nbr[0] - 1] 
pour mettre a jour la taille de l'arg actuel
	retourne: la taille du nom du $

si il n'exite pas mais que la taille du nom du $
(y) est different de 1 soustrait 1 a l_arg[nbr[0] - 1]
(si le nom != |$| mais n'existe pas, alors le dollars 
et son nom disparaissent de la chaine( = NULL), 
il faut donc soustraire le $ qui a deja ete compte)
	retourne: 0;
*/

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
/*mode 1: 
additionne la taille d'un argument entre ""
dans le cas de la presence d'un $,
additionne la taille du nom du dollar obtenu par skip dollars
a x pour mettre l'index a jour
(skip dollars additionne la taille de la valeur du dollars
nomme a la taille de l'argument en cours (nbr) 
dans l_arg[nbr[0] - 1])
si ce n'est pas un dollars, incremente l_arg[nbr[0] - 1]
jusqu'a atteindre '\0' ou un "

mode 2:

retourne l'index de buf[x]*/
/*entree a tester et corriger: |""    f   ""|*/
