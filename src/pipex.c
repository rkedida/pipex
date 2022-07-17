/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 08:02:00 by rkedida           #+#    #+#             */
/*   Updated: 2022/07/18 00:10:51 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_process(char **av, char **envp, int *pfd)
{
	int		file_input;

	file_input = open(av[1], O_RDONLY, 0777);
	if (file_input == -1)
	{
		perror("Error");
		file_input = open("/dev/null", O_RDONLY, 0777);
	}
	dup2(pfd[1], STDOUT_FILENO);
	dup2(file_input, STDIN_FILENO);
	close(pfd[0]);
	exe(av[2], envp);
}

void	parent_process(char **av, char **envp, int *pfd)
{
	int		file_output;

	file_output = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file_output == -1)
		error();
	dup2(pfd[0], STDIN_FILENO);
	dup2(file_output, STDOUT_FILENO);
	close(pfd[1]);
	exe(av[3], envp);
}

int	main(int ac, char **av, char **envp)
{
	int		pfd[2];
	pid_t	pid;

	if (ac == 5)
	{
		if (pipe(pfd) == -1)
			error();
		pid = fork();
		if (pid == -1)
			error();
		if (pid == 0)
			child_process(av, envp, pfd);
		waitpid(pid, NULL, 0);
		parent_process(av, envp, pfd);
	}
	else if (ac < 5 || ac > 5)
	{
		ft_putstr_fd("Error: Bad arguments\n", 2);
		ft_putstr_fd("Ex: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
	}
	else
		ft_putstr_fd("Error: Bad arguments\n", 2);
	return (0);
}
