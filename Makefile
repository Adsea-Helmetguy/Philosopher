# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlow <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/27 18:14:15 by mlow              #+#    #+#              #
#    Updated: 2023/11/29 16:11:30 by mlow             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc
CFLAGS = -g -Wall -Werror -Wextra #-fsanitize=thread#need to remove -g?
#There is no deadlock or data_race, Only potential deadlock.

SRC_DIR = ./main_src
INC_DIR = ./includes

#LIBFT file names and paths
#LIBFT_SRC_DIR = ./other_srcs/libft_project
#LIBFT = $(LIBFT_SRC_DIR)/libft.a
#LIB_FLAGS = -L $(LIBFT_SRC_DIR) -lft

#PRINTF file names and paths
#PRINTF_SRC_DIR = ./other_srcs/printf_project
#PRINTF = $(PRINTF_SRC_DIR)/libftprintf.a
#PRINTF_FLAGS = -L $(PRINTF_SRC_DIR) -lftprintf

#GET_NEXT_LINE file names and paths
#GNL_SRC_DIR = ./other_srcs/get_next_line_project
#GNL = $(GNL_SRC_DIR)/libft_get_next_line.a
#GNL_FLAGS = -L $(GNL_SRC_DIR) -lft_get_next_line

# -l : tells it which library to use
# -L : tells it which path to look for the library
# -I : where to look for .h file

#MLX file names and paths
#MLX_DIR = ./minilibx-linux
#MLX_LIB = $(MLX_DIR)/libmlx.a #could be /usr/lib, 
#MLX_INC_HEADER_DIR = -I/usr/include -I $(MLX_DIR)
#MLX_FLAGS  = -L $(MLX_LIB) -lmlx -L/usr/lib/X11 -lXext -lX11




# ************************************************************************** */
#	SOURCE                                                               */
# ************************************************************************** */
#List of SOURCE(SRC) files
SRC_FILE_NAMES = philosopher.c \
			checker.c \
			ft_atol.c \
			utils.c \
			monitoring.c \
			routine.c \
			rules.c 
			
		
		

# ************************************************************************** */
#	FILE_LOCATION                                                        */
# ************************************************************************** */
SRC_FILE_PATHS = $(addprefix $(SRC_DIR)/, $(SRC_FILE_NAMES))
GNL_FILE_PATHS = $(addprefix $(GNL_SRC_DIR)/, $(GNL_FILE_NAMES))

OBJ_FILE_PATHS = $(SRC_FILE_PATHS:.c=.o)
GNL_OBJ_FILE_PATHS = $(SRC_FILE_PATHS:.c=.o)

# ************************************************************************** */
#	RULES                                                                */
# ************************************************************************** */
all: $(NAME)

$(NAME): $(OBJ_FILE_PATHS)
	$(CC) $(CFLAGS) $(OBJ_FILE_PATHS) -o $(NAME)

$(OBJ_FILE_PATHS): $(SRC_DIR)/%.o : $(SRC_DIR)/%.c 
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

#Creating rules to compile individual source files for bonus to object files
clean: 
	rm -f $(OBJ_FILE_PATHS) $(GNL_OBJ_FILE_PATHS)
	
#clear .o files including static library $(NAME)
fclean: clean
	rm -f $(NAME)
#	@make fclean -sC $(MLX_DIR) Dont need cause the make file no fclean

#clean files and remake "all"
re: fclean all

.PHONY: all clean fclean re
