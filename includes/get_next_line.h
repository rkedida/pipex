/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 20:07:53 by rkedida           #+#    #+#             */
/*   Updated: 2022/07/15 01:42:36 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

typedef struct s_read
{
	int				fd;
	char			*str;
	struct s_read	*next;
}				t_read;

// functions in get_next_line_bonus.c

char	*free_and_cpy_reminder(char *str);
int		new_line_checker(char *s);
char	*return_line(char *str);
char	*read_file(int fd, char *str);
char	*get_next_line(int fd);

// functions in get_next_line_utils_1_bonus.c
char	*ft_strjoin(char *s, char *buff);
t_read	*clear_head(t_read *read, int fd);
size_t	ft_strlen1(char *s);
void	ft_strlcpy1(char *dst, char *src, size_t dstsize);
t_read	*init_struct(int fd);

// functions in get_next_line_utils_2_bonus.c

t_read	*check_fd(t_read *read, int fd);

#endif