/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbuyurha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:17:00 by cbuyurha          #+#    #+#             */
/*   Updated: 2024/03/12 21:17:01 by cbuyurha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/minishell.h"

int	pars_error2(int error)
{
	if (error == 8)
		write(2, &"syntax error near unexpected token `>|'\n", 40);
	else if (error == 9)
		write(2, &"syntax error near unexpected token `>>'\n", 40);
	else if (error == 10)
		write(2, &"syntax error near unexpected token `<<'\n", 40);
	else if (error == 11)
		write(2, &"syntax error near unexpected token `<'\n", 39);
	else if (error == 12)
		write(2, &"syntax error near unexpected token `<>'\n", 40);
	else if (error == 13)
		write(2, &"syntax error near unexpected token `<<<'\n", 41);
	return (0);
}

int	pars_error(int error)
{
	if (error > 0)
		write(2, &"-minishell: ", 12);
	if (error == 1)
		write(2, &"malloc error\n", 13);
	else if (error == 2)
		write(2, &"open quote error\n", 17);
	else if (error == 3)
		write(2, &"syntax error near unexpected token `|'\n", 39);
	else if (error == 4)
		write(2, &"syntax error near unexpected token `||'\n", 40);
	else if (error == 5)
		write(2, &"`|' opened\n", 12);
	else if (error == 6)
		write(2, &"syntax error near unexpected token `newline'\n", 45);
	else if (error == 7)
		write(2, &"syntax error near unexpected token `>'\n", 39);
	else if (error > 7)
		return (pars_error2(error));
	return (0);
}
