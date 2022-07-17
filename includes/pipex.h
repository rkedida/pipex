/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:08:28 by rkedida           #+#    #+#             */
/*   Updated: 2022/07/17 23:50:47 by rkedida          ###   ########.fr       */
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
# include <stdbool.h>

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
char			*ft_strchr(const char *str, int c);
void			exe(char *av, char **envp);

// functions in pipex_utils_3.c

char			*there_is_path(char *cmd, char **paths, char *path);
void			paths_free(char **paths, int i);
char			*helper(char **paths, char *path, char *cmd);
char			*find_path(char *cmd, char **envp);
char			*check_s(const char *s);

// functions in pipex_utils_4.c

void			ft_free(char**strs);
char			*free_split(char **dest);
char			*check_dest(char **dest);
void			print_exe(char **cmd);

#endif