/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 02:48:51 by rkedida           #+#    #+#             */
/*   Updated: 2022/07/15 01:05:34 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char *s, char *buff)
{
	size_t	i;
	size_t	j;
	char	*s1;

	if (!buff || !s)
		return (NULL);
	s1 = malloc((ft_strlen1(s) + ft_strlen1(buff) + 1) \
												* sizeof(char *));
	if (s1 == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (s)
		while (s[++i] != '\0')
			s1[i] = s[i];
	while (buff[j] != '\0')
		s1[i++] = buff[j++];
	s1[ft_strlen1(s) + ft_strlen1(buff)] = '\0';
	return (s1);
}

t_read	*clear_head(t_read *read, int fd)
{
	t_read	*after;
	t_read	*curr;

	curr = read;
	after = curr->next;
	if (curr->fd == fd)
	{
		free(curr->str);
		free(curr);
		return (after);
	}
	while (after != NULL)
	{
		if (after->fd == fd)
		{
			curr->next = after->next;
			if (after->str != NULL)
				free(after->str);
			free(after);
			return (read);
		}
		curr = curr->next;
		after = curr->next;
	}
	return (read);
}

size_t	ft_strlen1(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_strlcpy1(char *dst, char *src, size_t dstsize)
{
	size_t	i;

	if (!dstsize || !src)
		return ;
	i = 0;
	while (i < (dstsize - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return ;
}

t_read	*init_struct(int fd)
{
	t_read	*new;

	new = (t_read *)malloc(sizeof(t_read));
	if (!new)
		return (NULL);
	new->fd = fd;
	new->str = (char *)malloc(sizeof(char));
	new->str[0] = '\0';
	new->next = NULL;
	return (new);
}
