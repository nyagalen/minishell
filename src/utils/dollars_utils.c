/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 16:46:53 by cbuyurha          #+#    #+#             */
/*   Updated: 2024/04/11 17:17:08 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

int	special_dollars(t_all *a, int x, int nbr, int mode)
{
	int		y;
	char	*spe;

	spe = ft_itoa(a->info.code);
	if (!spe)
		return (a->info.error = 1, 1);
	y = ft_strlen(spe);
	if (mode == 2)
	{
		ft_strlcpy(&a->info.tmp[nbr - 1][++a->info.w], spe, y + 1);
		a->info.w = a->info.w + y - 1;
	}
	if (mode == 1)
		a->info.l_arg[nbr - 1] = a->info.l_arg[nbr - 1] + y - 1;
	free(spe);
	if (mode == 2)
		return (x + 1);
	return (1);
}
/*
spe: i->code converti en char

mode 1: récupére la taille de spé et 
l'ajoute a l_arg[nbr - 1] en retirant le $
	retourne: index de buf - 1
mode 2: copie spé a l'emplacement &a->info.tmp[a->info.na - 1][++a->info.w]
pour y + 1 characteres; me a jour l'index de a->info.tmp[a->info.na - 1]
	retourne: index de buf - 2
*/

int	add_dollars2(t_all *a, t_infos *i, int save)
{
	char	*tmp_env;
	int		len;

	tmp_env = NULL;
	len = 1;
	if (i->buf[save + 1] && i->buf[save + 1] == '?')
		return (special_dollars(a, save, i->na, 2));
	len = skip_char(&i->buf[save + 1], '_', 2);
	if (i->buf[save + 1] && ft_isdigit(i->buf[save + 1]) == 1)
		return (save + 1);
	tmp_env = malloc(sizeof(char) * (++len));
	if (!tmp_env)
		return (i->error = 1, save);
	ft_strlcpy(tmp_env, &i->buf[save + 1], len);
	if (find_variable(tmp_env, a->env) == 1)
		var_copy(a, i->tmp[i->na - 1], find_var_val(tmp_env, a->env));
	else if (len == 1)
		i->tmp[i->na - 1][++i->w] = '$';
	save = save + len - 1;
	free(tmp_env);
	return (save);
}

int	skip_dollars2(t_all *a, int x, int m)
{
	char	c;

	c = a->info.buf[x + 1];
	if (x + 1 < a->info.b_len && a->info.buf[x + 1])
	{
		if ((m == 1 || m == 3) && c == '?')
			return (-3);
		if (m == 1 && (c == 34 || c == 39))
			return (-2);
		if (m == 2 && (c == 34 || c == 39))
			return (1);
		if (ft_isdigit(c) == 1)
			return (1);
	}
	return (skip_char(&a->info.buf[x + 1], '_', 2));
}
//retourne la taille du dollars
/*mode 2: guillemet (si le dollars est entoure de quote)
(si le $ est entoure de quote 
akka pas forcement de l'arg a partir du premier chara non alphanum hors '_')
->retourne x + 1 en cas de quote (le nom du $ n'existe pas -> val $ == NULL)
-> retourne skip_char 
	(la taille du nom du $ (fin $ = chara non alphanumerique hors '_'))

mode 1 : sans guillemet 
(si le $ n'est pas entoure de quote 
akka fin de l'arg a partir du premier chara non alphanum hors '_')
-> retourne -2 en cas de quote (indique val $ == NULL)
-> retourne -3 en cas de $? (comportement special)
-> retourne skip_char (la taille du nom du $ 
	(fin $ = chara non alphanumerique hors '_'))
*/

int	skip_dollars(t_all *a, t_infos *i, int x)
{
	char	*tmp_env;
	int		len;

	tmp_env = NULL;
	len = skip_dollars2(a, x, 1);
	if (len == -2)
		return (--i->l_arg[i->na - 1], len);
	if (len == -3)
		return (special_dollars(a, x, i->na, 1));
	if (i->buf[x + 1] && ft_isdigit(i->buf[x + 1]) == 1)
		len = 1;
	tmp_env = malloc(sizeof(char) * (++len));
	if (!tmp_env)
		return (i->error = 1, len);
	ft_strlcpy(tmp_env, &i->buf[x + 1], len);
	if (find_variable(tmp_env, a->env) == 1)
		x = ft_strlen(find_var_val(tmp_env, a->env)) - 1;
	if (find_variable(tmp_env, a->env) == 1)
		i->l_arg[i->na - 1] = i->l_arg[i->na - 1] + x;
	else if (len != 1)
		i->l_arg[i->na - 1] = i->l_arg[i->na - 1] - 1;
	free(tmp_env);
	return (len - 1);
}
/*
tmp_env: destine a contenir le nom du $ (ex: |ls $USER"fds"| : |USER|)

y = skip_dollars2(a, x, 1); -> verifie que le nom 
ne commence pas par un quote ou un ?

si y = -2 (buf[x] -> quote) 
	retourne: l'index mis a jour au niveau de la quote 
			+ decremente le $ de l_arg[nbr[0] - 1]

si y = -3 (buf[x] -> ?)
	retourne: l'indexe mis a jour renvoye par special_dollars qui traite les $?

malloc tmp_env avec la taille du nom du $

copie dans tmp_env a partir de buf[x] (char apres le $) 
pour 'y' chara (taille du nom du $)
tmp_env contient maintenant le nom du $ 
(ex: |echo $USER"fdsf"| -> |USER|; |echo $USERfdsf | -> |USERfdsf|)

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
//dsadd

int	count_dollars(t_all *a, int x, int mode)
{	
	if (x >= a->info.b_len)
		return (x);
	while (x < a->info.b_len && a->info.buf[x] != 34)
	{
		if (mode == 1 && a->info.buf[x] == '$')
		{
			if (a->info.buf[x + 1] && a->info.buf[x + 1] == 34)
			{
				++a->info.l_arg[a->info.na - 1];
				return (x++);
			}
			else
				x = x + skip_dollars(a, &a->info, x);
		}
		else if (mode == 2 && a->info.buf[x] == '$')
			x = x + skip_dollars2(a, x, 2);
		if (mode == 1)
			++a->info.l_arg[a->info.na - 1];
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
