/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_3_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 23:42:09 by rkedida           #+#    #+#             */
/*   Updated: 2022/07/15 01:21:42 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_read	*check_fd(t_read *read, int fd)
{
	t_read	*curr;
	t_read	*ret;

	if (!read)
	{
		read = init_struct(fd);
		if (!read)
			return (NULL);
	}
	curr = read;
	while (curr->next != NULL)
	{
		if (curr->fd == fd)
			return (curr);
		curr = curr->next;
	}
	if (curr->fd != fd)
	{
		ret = init_struct(fd);
		if (!ret)
			return (NULL);
		curr->next = ret;
		return (ret);
	}
	return (curr);
}
