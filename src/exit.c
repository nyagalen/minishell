/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 01:29:46 by svydrina          #+#    #+#             */
/*   Updated: 2024/03/15 17:16:37 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	exitcode(int code)
{
	if (code >= 256)
		return (code / 256);
	return (code);
}

int	ft_exit(t_infos *infos, t_env **env, int i)
{	
	if (g_sig)
		infos->code = g_sig;
	if (infos->n_pipe == 0)
		printf("exit\n");
	if (infos->cmd && infos->cmd[i]
		&& check_ex_args(infos, infos->cmd[i]) == -1)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		if (!infos->code)
			infos->code = 1;
		return (infos->code);
	}
	if (infos->cmd && infos->cmd[i] && !check_ex_args(infos, infos->cmd[i]))
	{
		exit_blabla(infos, i);
		if (infos->n_pipe)
			return (infos->code);
	}
	else if (infos->cmd && infos->cmd[i])
		infos->code = atoi_exitcode(infos, infos->cmd[i][1]);
	if (!infos->n_pipe)
	{	
		free_tab3(infos->cmd);
		infos->red_tab = free_tab(infos->red_tab);
		free_env(env);
		rl_clear_history();
	}
	infos->code = exitcode(infos->code);
	exit(exitcode(infos->code));
}

int	check_ex_args(t_infos *infos, char **ex_cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (ex_cmd[++i])
	{
		if (i > 1)
			return (-1);
		if (ex_cmd[i][j] == '+' || ex_cmd[i][j] == '-')
		{
			if (ft_strlen(ex_cmd[i]) == 1)
				return (0);
			j++;
		}
		while (ex_cmd[i][j])
		{
			if (!(ft_isdigit(ex_cmd[i][j++])))
				return (0);
		}
		if (atoi_exitcode(infos, ex_cmd[i]) == -1)
			return (0);
	}
	return (1);
}

static int	check_zeros(char *num)
{
	int	i;
	int	zeros;

	i = 0;
	zeros = 0;
	if (num[i] == '+' || num[i] == '-')
		i++;
	while (num[i] && num[i] == '0')
	{
		zeros++;
		i++;
	}
	if (ft_strlen(num) - zeros > 20)
		return (0);
	return (1);
}

int	atoi_exitcode(t_infos *infos, char *num)
{
	unsigned long long	result;
	int					i;

	i = 0;
	result = 0;
	if (num == NULL)
		return (infos->code);
	if (!check_zeros(num))
		return (-1);
	if (num[i] == '+' || num[i] == '-')
		i++;
	while (num[i])
		result = result * 10 + num[i++] - 48;
	if (result == 9223372036854775808LLU && num[0] == '-')
		return (255);
	if (result > 9223372036854775807LLU)
		return (-1);
	if ((num[0] == '-' && result != 0) || result > 255)
		return (255);
	return ((int)result);
}
