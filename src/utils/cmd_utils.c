/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:03:19 by cbuyurha          #+#    #+#             */
/*   Updated: 2024/04/02 17:13:29 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

char	**free_tab(char **tab)
{
	int	x;

	x = -1;
	if (!tab)
		return (NULL);
	while (tab[++x])
	{
		if (tab[x])
		{
			free(tab[x]);
			tab[x] = NULL;
		}
	}
	free(tab);
	tab = NULL;
	return (NULL);
}
/*free un tab, 
renvoie NULL peut importe le resultat*/

char	***free_tab3(char ***cmd)
{
	int	index;
	int	x;

	index = -1;
	x = -1;
	if (!cmd)
		return (NULL);
	while (cmd[++index])
		cmd[index] = free_tab(cmd[index]);
	if (cmd[index])
		free(cmd[index]);
	free(cmd);
	cmd = NULL;
	return (NULL);
}

/* fsdf fezsfsd fds |sdf*/
int	pars_error_free(t_infos *i, int m)
{
	if (i->buf)
		free(i->buf);
	if (i->red_tab)
		i->red_tab = free_tab(i->red_tab);
	if (m == 0)
		return (-2);
	if (i->tmp)
		i->tmp = free_tab(i->tmp);
	if (i->l_arg)
		free(i->l_arg);
	if (i->l_tab)
		free(i->l_tab);
	if (m == 1)
		return (-2);
	return (-2);
}
