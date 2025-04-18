# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/24 17:49:58 by dwianni           #+#    #+#              #
#    Updated: 2024/10/26 17:53:07 by dwianni          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project name
NAME = libft.a

# Compiler and compiling flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Source files and object files
SRC = 	$(SRC_DIR)/ft_isalpha.c \
		$(SRC_DIR)/ft_isdigit.c \
		$(SRC_DIR)/ft_isalnum.c \
		$(SRC_DIR)/ft_isascii.c \
		$(SRC_DIR)/ft_isprint.c \
		$(SRC_DIR)/ft_strlen.c \
		$(SRC_DIR)/ft_memset.c \
		$(SRC_DIR)/ft_bzero.c \
		$(SRC_DIR)/ft_memcpy.c \
		$(SRC_DIR)/ft_memmove.c \
		$(SRC_DIR)/ft_toupper.c \
		$(SRC_DIR)/ft_tolower.c \
		$(SRC_DIR)/ft_strchr.c \
		$(SRC_DIR)/ft_strrchr.c \
		$(SRC_DIR)/ft_strncmp.c \
		$(SRC_DIR)/ft_memchr.c \
		$(SRC_DIR)/ft_memcmp.c \
		$(SRC_DIR)/ft_strnstr.c \
		$(SRC_DIR)/ft_atoi.c \
		$(SRC_DIR)/ft_strlcpy.c \
		$(SRC_DIR)/ft_strlcat.c \
		$(SRC_DIR)/ft_calloc.c \
		$(SRC_DIR)/ft_strdup.c \
		$(SRC_DIR)/ft_substr.c \
		$(SRC_DIR)/ft_strjoin.c \
		$(SRC_DIR)/ft_strjoin.c \
		$(SRC_DIR)/ft_strtrim.c \
		$(SRC_DIR)/ft_split.c \
		$(SRC_DIR)/ft_itoa.c \
		$(SRC_DIR)/ft_strmapi.c \
		$(SRC_DIR)/ft_striteri.c \
		$(SRC_DIR)/ft_putchar_fd.c \
		$(SRC_DIR)/ft_putstr_fd.c \
		$(SRC_DIR)/ft_putendl_fd.c \
		$(SRC_DIR)/ft_putnbr_fd.c \
		$(SRC_DIR)/ft_lstnew.c \
		$(SRC_DIR)/ft_lstadd_front.c \
		$(SRC_DIR)/ft_lstsize.c \
		$(SRC_DIR)/ft_lstlast.c \
		$(SRC_DIR)/ft_lstadd_back.c \
		$(SRC_DIR)/ft_lstdelone.c \
		$(SRC_DIR)/ft_lstclear.c \
		$(SRC_DIR)/ft_lstiter.c \
		$(SRC_DIR)/ft_lstmap.c \
		$(SRC_DIR)/get_next_line.c

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Libraries

# Header files
HEADERS = -I$(INC_DIR)

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/libft.h
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re