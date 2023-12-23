/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:11:48 by svydrina          #+#    #+#             */
/*   Updated: 2023/05/10 19:05:24 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 && n == 0)
		return (0);
	if (s2[0] == '\0')
		return ((char *)s1);
	while (s1[i] && i + j < n)
	{
		while (j + i < n && s1[i + j] && s2[j]
			&& s1[j + i] == s2[j])
		{
			j++;
			if (j == ft_strlen(s2))
				return ((char *)s1 + i);
		}
		j = 0;
		i++;
	}
	return (NULL);
}
