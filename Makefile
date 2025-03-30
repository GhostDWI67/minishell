# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/24 14:40:57 by dwianni           #+#    #+#              #
#    Updated: 2025/03/30 18:41:48 by dwianni          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project name
NAME = minishell

# Compiler and compiling flags
CC = cc
#CFLAGS = -Wall
#CFLAGS = -Wall -Wextra -Werror -g3
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

# Directories
SRC_DIR = src
OBJ_DIR = obj
LIBFT_DIR = lib/libft
PRINTF_DIR = lib/printf

INC_DIR = include

# Source files and object files
SRC =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/utils/check.c \
		$(SRC_DIR)/utils/utils.c \
		$(SRC_DIR)/parsing/parsing.c \
		$(SRC_DIR)/parsing/parsing_utils.c \
		$(SRC_DIR)/lexer/lexer.c \
		$(SRC_DIR)/exec/exec.c \
		$(SRC_DIR)/exec/exec_child.c \
		$(SRC_DIR)/exec/exec_utils.c \
		$(SRC_DIR)/error/error_mgt.c \
		$(SRC_DIR)/utils/free_utils.c \
		$(SRC_DIR)/redirection/redirection.c \
		$(SRC_DIR)/redirection/heredoc.c \
		
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