/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svydrina <svydrina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 19:19:28 by svydrina          #+#    #+#             */
/*   Updated: 2024/04/03 20:44:56 by svydrina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

static char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		len1;
	int		len2;
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new = malloc(len1 + len2 + 1);
	if (!new)
		return (NULL);
	ft_strcpy(new, s1);
	ft_strcpy(new + len1, s2);
	free(s1);
	return (new);
}

static void	manage_rest(char *line, char *buf)
{
	char	*rest;
	int		index;

	rest = ft_strchr(line, '\n');
	if (rest)
	{
		index = rest - line + 1;
		ft_strcpy(buf, rest + 1);
	}
	else
	{
		index = ft_strlen(line);
		ft_strcpy(buf, "");
	}
	line[index] = '\0';
}

	// rest = ft_strchr(line, '\n');
	// if (rest)
	// {
	// 	index = rest - line + 1;
	// 	ft_strcpy(buf, rest + 1);
	// }
	// else
	// {
	// 	index = ft_strlen(line);
	// 	ft_strcpy(buf, "");
	// }
	// line[index] = '\0';

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	int			bytes;

	bytes = read(fd, buf, BUFFER_SIZE);
	line = ft_strdup(buf);
	while (!ft_strchr(line, '\n') && bytes > 0)
	{
		buf[bytes] = '\0';
		line = ft_strjoin_gnl(line, buf);
		bytes = read(fd, buf, BUFFER_SIZE);
	}
	if (!ft_strlen(line))
		return (free(line), NULL);
	manage_rest(line, buf);
	return (line);
}
