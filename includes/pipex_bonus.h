/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 03:16:30 by rkedida           #+#    #+#             */
/*   Updated: 2022/07/17 23:53:43 by rkedida          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <sys/wait.h>
# include <limits.h>
# include <string.h>
# include <fcntl.h>
# include "get_next_line.h"

// functions in pipex_bonus.c

void			ft_child_process_bonus(char *av, char **envp);
void			here_doc_helper_2(int *pfd);
void			here_doc_helper_1(int ac, int pfd[2]);
void			here_doc(char *limiter, int ac);

// functions in pipex_utils_1_bonus.c

void			ft_putstr_fd_bonus(char *s, int fd);
void			ft_error_message(void);
void			ft_exe_bonus(char *av, char **envp);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				open_pfd(char *av, int i);

// functions in pipex_utils_2_bonus.c

char			*free_split(char **dest);
char			**ft_split(char const *s, char c);

// functions in pipex_utils_3_bonus.c

char			*there_is_path(char *cmd, char **paths, char *path);
void			paths_free(char **paths, int i);
char			*helper(char **paths, char *path, char *cmd);
char			*find_path(char *cmd, char **envp);
char			*ft_strdup(const char *s1);

// functions in pipex_utils_4_bonus.c

char			*ft_strnstr(const char *haystack, const char *needle, \
															size_t len);
char			*ft_strchr(const char *str, int c);
char			*check_s(const char *s);
char			*check_dest(char **dest);
void			erron(void);

#endif