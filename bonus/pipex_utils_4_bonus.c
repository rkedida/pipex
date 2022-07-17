/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_4_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 19:56:35 by rkedida           #+#    #+#             */
/*   Updated: 2022/07/18 00:09:59 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	n;

	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		n = 0;
		while (needle[n] && haystack[i + n]
			&& haystack[i + n] == needle[n] && i + n < len)
			n++;
		if (needle[n] == '\0')
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}

char	*ft_strchr(const char *str, int c)
{
	int		i;

	i = ft_strlen1(str);
	if (c == '\0')
		return ((char *)&str[i]);
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}

char	*check_s(const char *s)
{
	if (!s)
		exit(0);
	return ((char *)s);
}

char	*check_dest(char **dest)
{
	if (!dest)
		exit(0);
	return (*dest);
}

void	erron(void)
{
	ft_putstr_fd_bonus("Error: Bad arguments\n", 2);
	ft_putstr_fd_bonus("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 2);
	ft_putstr_fd_bonus("Error: ./pipex file1 cmd1 cmd2 ... cmdn file2\n", 2);
}
