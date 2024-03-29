/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 00:39:12 by rkedida           #+#    #+#             */
/*   Updated: 2022/07/18 00:10:35 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

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

	i = ft_strlen(str);
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

void	exe(char *av, char **envp)
{
	int		i;
	char	*path;
	char	**cmd;

	i = -1;
	cmd = ft_split(av, ' ');
	if (access(cmd[0], F_OK | X_OK) == 0)
		path = cmd[0];
	else
		path = find_path(cmd[0], envp);
	if (!path)
	{
		print_exe(cmd);
		ft_free(cmd);
		free(path);
		exit(EXIT_FAILURE);
	}
	if (execve(path, cmd, envp) == -1)
	{
		free(path);
		ft_free(cmd);
		error();
	}
	free(path);
	ft_free(cmd);
}
