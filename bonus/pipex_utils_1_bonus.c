/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_1_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:08:17 by rkedida           #+#    #+#             */
/*   Updated: 2022/07/15 01:08:50 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_putstr_fd_bonus(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen1(s));
}

void	ft_error_message(void)
{
	ft_putstr_fd_bonus("Error: Bad argument\n", 2);
	ft_putstr_fd_bonus("Ex: ./pipex <file1> <cmd1> <cmd2> <...> <file2>\n", 2);
	ft_putstr_fd_bonus("    ./pipex \"here_doc\" <LIMITER> \
<cmd> <cmd1> <...> <file>\n", 2);
	exit(EXIT_SUCCESS);
}

void	ft_exe_bonus(char *av, char **envp)
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
		while (cmd[++i])
			free(cmd[i]);
		free(cmd);
		ft_error_message();
	}
	if (execve(path, cmd, envp) == -1)
		ft_error_message();
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while ((str1[i] == str2[i]) && str1[i] != 0 && str2[i] != 0 && i < n - 1)
		i++;
	return (str1[i] - str2[i]);
}

int	open_pfd(char *av, int i)
{
	int	pfd;

	pfd = 0;
	if (i == 0)
		pfd = open(av, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		pfd = open(av, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		pfd = open(av, O_RDONLY, 0777);
	if (pfd == -1)
		ft_error_message();
	return (pfd);
}
