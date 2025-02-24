# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/02 11:23:42 by dwianni           #+#    #+#              #
#    Updated: 2024/11/08 10:31:20 by dwianni          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project name
NAME = libftprintf.a

# Compiler and compiling flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Source files and object files
SRC = 	$(SRC_DIR)/ft_printf.c \
		$(SRC_DIR)/ft_printf_utils.c \
		$(SRC_DIR)/ft_printf_sc.c \
		$(SRC_DIR)/ft_printf_diu.c \
		$(SRC_DIR)/ft_printf_pxux.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Libraries

# Header files
HEADERS = -I$(INC_DIR)

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/ft_printf.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
