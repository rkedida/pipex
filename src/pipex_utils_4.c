/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/17 20:40:39 by rkedida           #+#    #+#             */
/*   Updated: 2022/07/18 00:10:45 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_free(char**strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	strs = NULL;
}

char	*free_split(char **dest)
{
	ft_free(dest);
	exit(0);
}

char	*check_dest(char **dest)
{
	if (!dest)
		exit(0);
	return (*dest);
}

void	print_exe(char **cmd)
{
	ft_putstr_fd("pipex: command not found : ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd("\n", 2);
}
