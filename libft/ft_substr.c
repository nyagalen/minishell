/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 17:57:46 by svydrina          #+#    #+#             */
/*   Updated: 2023/05/14 22:41:58 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	act_len;
	size_t	i;
	size_t	new_i;
	char	*new;

	act_len = 0;
	new_i = 0;
	i = (size_t)start;
	if (start >= ft_strlen(s))
		act_len = 0;
	else
	{
		while (s[i++] && act_len < len)
			act_len++;
	}
	new = malloc(act_len + 1);
	if (!new)
		return (NULL);
	while (new_i < act_len)
		new[new_i++] = s[start++];
	new[new_i] = '\0';
	return (new);
}
