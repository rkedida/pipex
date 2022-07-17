# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkedida <rkedida@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/13 03:02:41 by rkedida           #+#    #+#              #
#    Updated: 2022/07/17 20:42:32 by rkedida          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex
BONUS	= pipex_bonus

CFLAGS				= -Wall -Wextra -Werror
HEADERS				= -I ./includes
OBJ_DIR				= ./obj/

SRC_DIR				= ./src/
SRCS_FILES			= pipex.c pipex_utils_1.c pipex_utils_2.c pipex_utils_3.c \
						pipex_utils_4.c
SRC					= $(addprefix $(SRC_DIR), $(SRCS_FILES))

OBJS_FILES			= $(addprefix $(OBJ_DIR), $(SRCS_FILES))
OBJS	 			= $(OBJS_FILES:.c=.o)

BONUS_DIR			= ./bonus/
SRCS_FILES_BONUS	= pipex_bonus.c pipex_utils_1_bonus.c pipex_utils_2_bonus.c \
						get_next_line_bonus.c get_next_line_utils_1_bonus.c \
						get_next_line_utils_2_bonus.c pipex_utils_3_bonus.c \
						pipex_utils_4_bonus.c
SRCS_BONUS			=	$(addprefix $(BONUS_DIR), $(SRCS_FILES_BONUS))

OBJS_FILES_BONUS	= $(addprefix $(OBJ_DIR), $(SRCS_FILES_BONUS))
OBJS_BONUS	 		= $(OBJS_FILES_BONUS:.c=.o)


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

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@$(CC) ${FLAGS} ${HEADERS} -c $< -o $@ && printf "$(GREEN)$(BOLD)\rCompiling: $(notdir $<)\r\e[35C[OK]\n$(RESET)"

$(OBJ_DIR)%.o : $(BONUS_DIR)%.c
	@$(CC) ${FLAGS} ${HEADERS} -c $< -o $@ && printf "$(GREEN)$(BOLD)\rCompiling: $(notdir $<)\r\e[35C[OK]\n$(RESET)"

$(NAME): $(OBJ_DIR) $(OBJS)
	@$(CC) $(HEADERS) $(CFLAGS) $(OBJS) -o $(NAME)

bonus: $(BONUS)

$(BONUS): $(OBJ_DIR) $(OBJS_BONUS)
	@$(CC) $(HEADERS) $(CFLAGS) $(OBJS_BONUS) -o $(BONUS)

norm: 
	@norminette

git:
	git add .
	git commit -m "Update"
	git push

clean:
	@rm -f $(OBJS)
	@rm -f $(OBJS_BONUS)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(BONUS)

re: clean all

.PHONY: all, clean, fclean, re, libmlx, libft