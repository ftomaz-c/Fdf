NAME := fdf

SRC :=	src/main.c \
		src/read_map.c \
		src/draw_map.c

OBJ := $(SRC:.c=.o)

CC := cc

CFLAGS := -Wall -Wextra -Werror -g

INCLUDES := -I./src/libft/includes

LIBFT := src/libft/libft.a

MLX := -Lsrc/mlx_linux -lmlx -L/usr/lib -Isrc/mlx_linux -lXext -lX11 -lm -lz

GREEN := \033[0;32m
CYAN := \033[0;36m
RED := \033[0;31m
NC := \033[0m

all:	$(LIBFT) $(OBJ) $(NAME)

$(LIBFT):
	@echo "$(CYAN)\n# Compiling libft...\n$(NC)"
	@$(MAKE) -C src/libft || (rm -f $(NAME)  && exit 1)

	@echo "$(CYAN)\n# Compiling $(NAME)...\n$(NC)"
	@echo "cc -Wall -Wextra -Werror -g -I./src/libft/includes -c *.c -o *.o"

$(OBJ): %.o: %.c
	@echo "$(CYAN)	Compiling $@...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -I/usr/include -Isrc/mlx_linux -O3 -c $< -o $@

$(NAME): $(OBJ)
	@echo "$(CYAN)\n# Linking $(NAME) with libft...\n$(NC)"
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFT) $(MLX) -o $(NAME)
	@echo "$(GREEN)\n###############################$(NC)"
	@echo "$(GREEN)	$(NAME) is ready!$(NC)"
	@echo "$(GREEN)###############################$(NC)"

clean:
	@echo "$(CYAN)\n# Cleaning libft...\n$(NC)"
	$(MAKE) -C src/libft clean
	@echo "$(CYAN)\n# Cleaning object files...\n$(NC)"
	rm -f $(OBJ)
	@echo "$(GREEN)\n###########################################$(NC)"
	@echo "$(GREEN)	$(NAME) object files cleaned!$(NC)"
	@echo "$(GREEN)###########################################$(NC)"

fclean: clean
	@echo "$(CYAN)\n# Cleaning $(NAME) and libft...\n$(NC)"
	rm -f $(NAME)
	$(MAKE) -C src/libft fclean
	@echo "$(GREEN)\n########################################$(NC)"
	@echo "$(GREEN)	$(NAME) and libft cleaned!$(NC)"
	@echo "$(GREEN)########################################$(NC)"

re: fclean all

.PHONY: all clean fclean re
