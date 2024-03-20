/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 20:08:43 by svydrina          #+#    #+#             */
/*   Updated: 2023/12/01 19:49:46 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	sep(char c, char *se)
{
	int	i;

	i = 0;
	while (se[i])
	{
		if (se[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	word_cnt(char const *s, char *se)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((i == 0 && !sep(s[i], se))
			|| (i > 0 && sep(s[i - 1], se) && !sep(s[i], se)))
			count++;
		i++;
	}
	return (count);
}

static char	**malloc_arr(char **arr, char const *str, char *se)
{
	int	str_i;
	int	arr_i;
	int	len;

	str_i = 0;
	arr_i = 0;
	while (str[str_i])
	{
		len = 0;
		while (str[str_i] && sep(str[str_i], se))
			str_i++;
		if (str[str_i] && !sep(str[str_i], se))
		{
			while (str[str_i] && !sep(str[str_i], se))
			{
				len++;
				str_i++;
			}
			arr[arr_i] = malloc(len + 1);
			ft_memcpy(arr[arr_i], str + str_i - len, len);
			arr[arr_i++][len] = '\0';
		}
	}
	arr[arr_i] = 0;
	return (arr);
}

char	**ft_split(char const *s, char *se)
{
	char	**new_arr;
	int		word_count;

	word_count = word_cnt(s, se);
	new_arr = malloc((word_count + 1) * sizeof(char **));
	if (!new_arr)
		return (NULL);
	new_arr = malloc_arr(new_arr, s, se);
	return (new_arr);
}
