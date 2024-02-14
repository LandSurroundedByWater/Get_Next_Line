/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 08:45:30 by tsaari            #+#    #+#             */
/*   Updated: 2023/12/14 11:37:07 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*srcc;
	size_t	len;
	size_t	i;

	srcc = (char *)src;
	i = 0;
	if ((!dst || !src) && !size)
		return (0);
	while (dst[i] != 0 && i < size)
		i++;
	if (i < size)
		len = i + ft_strlen(srcc);
	else
		return (size + ft_strlen(srcc));
	while (*srcc != 0 && (i + 1) < size)
	{
		dst[i] = *srcc++;
		i++;
	}
	dst[i] = '\0';
	return (len);
}

static char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	char	*s1c;
	char	*s2c;
	size_t	len;
	size_t	i;

	i = 0;
	if (!s1 || ! s2)
		return (0);
	s2c = (char *)s2;
	s1c = (char *)s1;
	len = (ft_strlen(s1c) + ft_strlen(s2c)) * sizeof(char) + 1;
	res = (char *)ft_calloc(len, sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1c, ft_strlen(s1c) + 1);
	ft_strlcat(res, s2c, len);
	return (res);
}

static char	*ft_strchr(const char *s, int c)
{
	char	*sc;
	int		i;
	int		len;

	i = 0;
	sc = (char *)s;
	len = ft_strlen(sc);
	while (len >= 0)
	{
		if (sc[i] != (char)c)
		{
			i++;
			len--;
		}
		else
			return (sc + i);
	}
	return (0);
}

static char	*read_file_until_nl(int fd, char *buffer)
{
	char	readed[BUFFER_SIZE + 1];
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	if (!buffer)
		buffer = ft_calloc(1, 1);
	while (bytes_read > 0)
	{
		bytes_read = read(fd, readed, BUFFER_SIZE);
		if (bytes_read == -1 || (!buffer) || \
		(bytes_read == 0 && ft_strlen(buffer) == 0))
			return (ft_free(&buffer, NULL));
		readed[bytes_read] = '\0';
		temp = buffer;
		buffer = ft_strjoin (buffer, readed);
		ft_free(&temp, NULL);
		if (!buffer)
			return (ft_free(&buffer, NULL));
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;
	char		*temp;
	size_t		newline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_file_until_nl(fd, buffer);
	if (!buffer)
		return (ft_free(&buffer, NULL));
	newline = (ft_strchr(buffer, '\n') - buffer);
	line = ft_substr(buffer, 0, newline + 1);
	if (!line)
		return (ft_free(&buffer, &line));
	temp = buffer;
	buffer = ft_substr(buffer, newline + 1, ft_strlen(buffer) - newline);
	free(temp);
	if (!buffer && !line)
		return (ft_free(&buffer, &line));
	return (line);
}
