# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alion <alion@student.s19.be>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/27 10:03:35 by clegros           #+#    #+#              #
#    Updated: 2024/09/12 15:05:02 by alion            ###   ########.fr        #
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
SRC     = main.c\
			keymap.c\
			keymap_utils.c\
			parsing_help.c\
			parsing_map.c\
			parsing.c\
			raycasting.c\
			render.c\
			render_utils.c\
			utils/get_next_line/ft_get_next_line.c\
			utils/get_next_line/ft_get_next_line_utils.c
OBJ     = $(SRC:.c=.o)
CC      = gcc
CFLAGS  = -g -Wall -Werror -Wextra -finline-functions -fvectorize -fslp-vectorize -ffast-math -falign-functions -funroll-loops -fstrict-aliasing -fomit-frame-pointer -flto -Ofast -O1 -O2 -Os -O3 
DIR_INC = -Iutils/ -I/includes  # Adjust path to MLX headers if necessary
LIB_LIB = utils/libft.a
LINK_FLAGS = -lmlx -framework OpenGL -framework AppKit
TOT_FIL = $(words $(SRC))

all:    $(NAME)

$(NAME): $(OBJ) $(LIB_LIB)
		@$(CC) $(OBJ) -o $(NAME) $(LIB_LIB) $(LINK_FLAGS)
		@echo "$(GREEN)Compilation completed.$(STOP)"

%.o: %.c
		@$(CC) $(CFLAGS) $(DIR_INC) -c $< -o $@
		@$(eval FILES_DONE := $(shell echo $$(($(FILES_DONE) + 1))))
		@$(call PRINT_LOADING_BAR,$(FILES_DONE),$(TOT_FIL))

$(LIB_LIB):
		@$(MAKE) -C utils

clean:
		@$(RM) $(OBJ)
		@$(MAKE) -C utils clean
		@echo "$(GREEN)Cleaning completed.$(STOP)"

fclean: clean
		@$(RM) $(NAME)
		@$(MAKE) -C utils fclean

re:     fclean all
