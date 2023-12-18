# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ftomaz-c <ftomaz-c@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/12 12:23:08 by pmessett          #+#    #+#              #
#    Updated: 2023/11/15 15:40:31 by ftomaz-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC =	src/ft_isalpha.c		src/ft_isdigit.c	src/ft_isalnum.c	src/ft_isascii.c	src/ft_isprint.c		\
		src/ft_strlen.c			src/ft_memset.c		src/ft_bzero.c		src/ft_memcpy.c		src/ft_strlcat.c		\
		src/ft_memmove.c		src/ft_strlcpy.c	src/ft_toupper.c	src/ft_tolower.c		\
		src/ft_strchr.c			src/ft_strrchr.c	src/ft_strncmp.c	src/ft_memchr.c		src/ft_memcmp.c			\
		src/ft_strnstr.c		src/ft_atoi.c		src/ft_calloc.c		src/ft_strdup.c		src/ft_substr.c			\
		src/ft_strjoin.c		src/ft_strtrim.c	src/ft_split.c		src/ft_itoa.c		src/ft_strmapi.c		\
		src/ft_striteri.c		src/ft_putchar_fd.c	src/ft_putstr_fd.c	src/ft_putendl_fd.c	src/ft_putnbr_fd.c		\
		src/ft_putnbr_base_fd.c	src/ft_isspace.c	src/ft_atol.c

#ft_printf
SRC +=	src/ft_printf/ft_printf.c	src/ft_printf/format_len.c	src/ft_printf/hex_format.c	src/ft_printf/nbr_format.c	\
		src/ft_printf/ptr_format.c	src/ft_printf/str_format.c	src/ft_printf/unsg_format.c

#get_next_line
SRC +=	src/get_next_line/get_next_line.c	src/get_next_line/get_next_line_utils.c

OBJ = $(SRC:.c=.o)

INCLUDES = -I./includes

LIB_CMD = ar -r -c -s

CC = cc

CFLAGS = -Wall -Wextra -Werror $(INCLUDES)

REMOVE = rm -rf

GREEN = \033[0;32m
CYAN = \033[0;36m
NC = \033[0m

all:	$(NAME)

$(OBJ): %.o: %.c
	@echo "$(CYAN)	Compiling $@...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME):	$(OBJ)
	@echo "$(CYAN)\n# Creating $(NAME) library...\n$(NC)"
	$(LIB_CMD) $(NAME) $(OBJ)
	@echo "$(GREEN)\n# $(NAME) library created!\n$(NC)"

clean:
	@echo "$(CYAN)\n# Cleaning object files...\n$(NC)"
	$(REMOVE) $(OBJ)
	@echo "$(GREEN)\n# $(NAME) object files cleaned!\n$(NC)"

fclean: clean
	@echo "$(CYAN)\n# Cleaning libft.a library...\n$(NC)"
	$(REMOVE) $(NAME)
	@echo "$(GREEN)\n# libft.a library cleaned!\n$(NC)"

re:	fclean all

.PHONY: all clean fclean re bonus
