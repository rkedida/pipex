/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:08:28 by rkedida           #+#    #+#             */
/*   Updated: 2022/07/15 01:42:51 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>

// functions in pipex.c

void			child_process(char **av, char **envp, int *pfd);
void			parent_process(char **av, char **envp, int *pfd);

// functions in pipex_utils_1.c

char			**ft_split(char const *s, char c);
size_t			ft_strlen(const char *s);
char			*ft_strjoin(char *s, char *buff);

// functions in pipex_utils_2.c

void			error(void);
void			ft_putstr_fd(char *s, int fd);
char			*ft_strnstr(const char *haystack, \
					const char *needle, size_t len);
char			*find_path(char *cmd, char **envp);
void			exe(char *av, char **envp);

#endif