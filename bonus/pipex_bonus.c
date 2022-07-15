/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:08:12 by rkedida           #+#    #+#             */
/*   Updated: 2022/07/15 02:53:04 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_child_process_bonus(char *av, char **envp)
{
	pid_t	pid;
	int		pfd[2];

	if (pipe(pfd) == -1)
		ft_error_message();
	pid = fork();
	if (pid == -1)
		ft_error_message();
	if (pid == 0)
	{
		close(pfd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		ft_exe_bonus(av, envp);
	}
	else
	{
		close(pfd[1]);
		dup2(pfd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

void	new_line_remove(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n')
		i++;
	line[i] = '\0';
}

void	here_doc_helper(int *pfd)
{
	close(pfd[1]);
	dup2(pfd[0], STDIN_FILENO);
	wait(NULL);
}

void	here_doc(char *limiter, int ac)
{
	pid_t	fd_reader;
	int		pfd[2];
	char	*line;

	pipe(pfd);
	if (ac < 6)
		ft_error_message();
	if (pipe(pfd) == -1)
		ft_error_message();
	fd_reader = fork();
	if (fd_reader == 0)
	{
		close(pfd[0]);
		while (1)
		{
			line = get_next_line(0);
			new_line_remove(line);
			if (strcmp(line, limiter) == 0)
				exit(EXIT_SUCCESS);
			write(pfd[1], line, ft_strlen1(line));
		}
	}
	else
		here_doc_helper(pfd);
}

int	main(int ac, char **av, char **envp)
{
	int			fileout;
	int			filein;
	int			i;

	if (ac >= 5)
	{
		if (ft_strncmp(av[1], "here_doc", 8) == 0)
		{
			i = 3;
			fileout = open_pfd(av[ac - 1], 0);
			here_doc(av[2], ac);
		}
		else
		{
			i = 2;
			fileout = open_pfd(av[ac - 1], 1);
			filein = open_pfd(av[1], 2);
			dup2(filein, STDIN_FILENO);
		}
		while (i < ac - 2)
			ft_child_process_bonus(av[i++], envp);
		dup2(fileout, STDOUT_FILENO);
		ft_exe_bonus(av[ac - 2], envp);
	}
	ft_error_message();
}
