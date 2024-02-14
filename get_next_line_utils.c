/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaari <tsaari@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 11:54:21 by tsaari            #+#    #+#             */
/*   Updated: 2023/12/14 11:35:21 by tsaari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_free(char **ptr, char **ptr2)
{
	if (ptr != NULL && *ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
	if (ptr2 != NULL && *ptr2 != NULL)
	{
		free(*ptr2);
		*ptr2 = NULL;
	}
	return (NULL);
}

char	*ft_calloc(size_t count, size_t size)
{
	char	*ret;
	size_t	i;

	ret = NULL;
	if (count && size && count > (UINT_MAX / size))
		return (0);
	ret = (char *)malloc(count * size);
	if (!ret)
		return (ft_free(&ret, NULL));
	i = 0;
	while (i < (count * size))
	{
		ret[i] = 0;
		i++;
	}
	return (ret);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (src[len] != '\0')
		len++;
	if (size <= 0)
		return (len);
	else
	{
		while (i < (size - 1) && src[i] != 0)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len);
}

size_t	ft_strlen(const char *s)
{
	size_t	l;

	l = 0;
	while (s[l] != '\0')
		l++;
	return (l);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	char	*sc;

	sc = (char *)s;
	if (!s)
		return (0);
	if (len + (size_t)start >= ft_strlen(sc))
		len = ft_strlen(sc) - start;
	if ((size_t)start >= ft_strlen(sc))
	{
		ret = ft_calloc(1, sizeof(char));
		if (!ret)
			ft_free(&ret, NULL);
		return (ret);
	}
	ret = (char *)malloc ((len + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	sc += start;
	len += 1;
	ft_strlcpy(ret, sc, len);
	return (ret);
}
