# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/13 03:02:41 by rkedida           #+#    #+#              #
#    Updated: 2022/07/13 03:05:17 by rkedida          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex
CFLAGS	= -Wall -Wextra -Werror

SRCS	= $(shell find -iname "*.c")
OBJS	= ${SRCS:.c=.o}

BOLD	= \033[1m
BLACK	= \033[30;1m
RED	= \033[31;1m
GREEN	= \033[32;1m
YELLOW	= \033[33;1m
BLUE	= \033[34;1m
MAGENTA	= \033[35;1m
CYAN	= \033[36;1m
WHITE	= \033[37;1m
RESET	= \033[0m

# //= Recipes =//

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< && printf "$(GREEN)$(BOLD)\rCompiling: $(notdir $<)\r\e[35C[OK]\n$(RESET)"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx, libft