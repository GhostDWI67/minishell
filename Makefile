# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/24 14:40:57 by dwianni           #+#    #+#              #
#    Updated: 2025/03/09 17:53:38 by dwianni          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project name
NAME = minishell

# Compiler and compiling flags
CC = cc
#CFLAGS = -Wall
CFLAGS = -Wall -Wextra -Werror 

# Directories
SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = lib/libft
PRINTF_DIR = lib/printf

INC_DIR = include

# Source files and object files
SRC =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/check.c \
		$(SRC_DIR)/utils.c \
		$(SRC_DIR)/parsing.c \
		
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a
PRINTF = $(PRINTF_DIR)/libftprintf.a
LIBS = -L$(LIBFT_DIR) -lft -L$(PRINTF_DIR) -lftprintf

# Header files
INC_LIBFT_DIR = $(LIBFT_DIR)/include
INC_PRINTF_DIR = $(PRINTF_DIR)/include
HEADERS = -I$(INC_DIR) -I$(INC_LIBFT_DIR) -I$(INC_PRINTF_DIR)

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -lreadline -o $(NAME)
	
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/minishell.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(PRINTF_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(PRINTF_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(PRINTF_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re