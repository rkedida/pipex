/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 20:03:27 by rkedida           #+#    #+#             */
/*   Updated: 2022/07/18 00:10:40 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*there_is_path(char *cmd, char **paths, char *path)
{
	if (access(cmd, F_OK) == 0)
	{
		paths = ft_split(cmd, ' ');
		path = paths[0];
		free(paths);
		return (path);
	}
	return (NULL);
}

void	paths_free(char **paths, int i)
{
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
}

char	*helper(char **paths, char *path, char *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	if (ft_strchr(cmd, '/'))
		return (there_is_path(cmd, paths, path));
	while (envp[i] && ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	if (envp[i] == NULL)
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	path = helper(paths, path, cmd);
	paths_free(paths, i);
	return (path);
}

char	*check_s(const char *s)
{
	if (!s)
		exit(0);
	return ((char *)s);
}
