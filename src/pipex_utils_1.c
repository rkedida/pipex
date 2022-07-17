/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:08:24 by rkedida           #+#    #+#             */
/*   Updated: 2022/07/18 00:10:27 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char
	*ft_strcpyt(char *str, char c)
{
	char	*dest;
	int		i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	dest = (char *)malloc(sizeof(char) * i + 1);
	if (!dest)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static int	count_words(char *str, char c)
{
	int	i;

	i = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str && *str != c)
		{
			i++;
			while (*str && *str != c)
				str++;
		}
	}
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	*str;
	char	**dest;
	int		i;

	check_s(s);
	str = (char *)s;
	i = 0;
	dest = malloc(sizeof(char *) * (count_words(str, c) + 1));
	check_dest(dest);
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str && *str != c)
		{
			dest[i] = ft_strcpyt(str, c);
			if (dest[i] == NULL)
				free_split(dest);
			i++;
			while (*str && *str != c)
				str++;
		}
	}
	dest[i] = NULL;
	return (dest);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s, char *buff)
{
	size_t	i;
	size_t	j;
	char	*s1;

	if (!buff || !s)
		return (NULL);
	s1 = malloc((ft_strlen(s) + ft_strlen(buff) + 1) * sizeof(char *));
	if (s1 == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (s)
		while (s[++i] != '\0')
			s1[i] = s[i];
	while (buff[j] != '\0')
		s1[i++] = buff[j++];
	s1[ft_strlen(s) + ft_strlen(buff)] = '\0';
	return (s1);
}
