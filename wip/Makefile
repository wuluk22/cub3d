# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clegros <clegros@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/27 10:03:35 by clegros           #+#    #+#              #
#    Updated: 2024/08/27 10:03:37 by clegros          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN=\033[0;32m
STOP=\033[0m

define PRINT_LOADING_BAR
	@progress=$$(echo "scale=2; $(1) / $(2) * 100" | bc); \
	percentage=$$(printf "%.0f" $$progress); \
	echo "Progress: [$$percentage%]"
endef

NAME    = cub3D
SRC     = main.c
OBJ     = $(SRC:.c=.o)
CC      = gcc
CFLAGS  = -g -Wall -Werror -Wextra
COMP    = $(CC) $(CFLAGS)
RM      = rm -f
DIR_INC	= -Iutils/
LIB_LIB	= utils/libft.a
MLX_DIR = minilibx_opengl_20191021
LINK	= -lmlx -framework OpenGL -framework AppKit -L $(MLX_DIR)
TOT_FIL	= $(words $(SRC))

all:    $(NAME)

$(NAME): $(OBJ) libmlx $(LIB_LIB)
		@$(COMP) $(OBJ) -o $(NAME) $(LIB_LIB) -L. -lmlx
		@echo "$(GREEN)Compilation completed.$(STOP)"

%.o: %.c
		@$(CC) $(CFLAGS) $(DIR_INC) -c $< -o $@
		@$(eval FILES_DONE := $(shell echo $$(($(FILES_DONE) + 1))))
		@$(call PRINT_LOADING_BAR,$(FILES_DONE),$(TOT_FIL))

libmlx:
		@make -C $(MLX_DIR)

$(LIB_LIB):
		@$(MAKE) -C utils

clean:
		@$(RM) $(OBJ)
		@$(MAKE) -C utils $(MLX_DIR) clean
		@echo "$(GREEN)Cleaning completed.$(STOP)"

fclean: clean
		@$(RM) $(NAME)
		@$(MAKE) -C utils $(MLX_DIR) fclean

re:     fclean all
