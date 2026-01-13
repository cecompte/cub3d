CC				= cc
CFLAGS			= -g3 -Wall -Wextra -Werror -MMD -MP
ifeq ($(shell uname), Linux)
	INCLUDES 	= -Iincludes -Ilibft -I/usr/include -Imlx
else
	INCLUDES 	= -Iincludes -Ilibft -I/opt/X11/include -Imlx 
endif
NAME			= cub3d

# Sources
SRC_PATH		= src/
SRC				= main.c \
					map.c \
					parce_config.c \
					init.c \
					mlx_utils.c \
					draw_minimap/get_next_line.c \
					draw_minimap/draw_minimap.c \
					draw_minimap/parsing_so_long.c
SOURCES			= $(addprefix $(SRC_PATH), $(SRC))

# Mlx
MLX_DIR 		= ./mlx
MLX_LIB 		= $(MLX_DIR)/libmlx_$(UNAME).a
ifeq ($(shell uname), Linux)
	MLX_FLAGS 	= -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
else
	MLX_FLAGS 	= -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif

# Objects
OBJ_PATH		= obj/
OBJ				= $(SRC:.c=.o)
OBJECTS			= $(addprefix $(OBJ_PATH), $(OBJ))
DEP				= $(SRC:.c=.d)
DEPS			= $(addprefix $(OBJ_PATH), $(DEP))

# libft
LIBFT			= libft.a
LIBFT_FLAGS		= -Llibft -lft
LIBFT_DIR		= ./libft

# Colors for display
RED				= \e[31m
GREEN			= \e[32m
YELLOW			= \e[33m
BLUE			= \e[34m
MAGENTA			= \e[35m
CYAN			= \e[36m
RESET			= \e[m

all: $(LIBFT) mlx $(NAME)

$(NAME): $(OBJECTS)
	@printf "$(BLUE)%s$(RESET): $(YELLOW)Building $(NAME)...$(RESET)\n" $(NAME)
	@$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT_FLAGS) $(MLX_FLAGS) -o $(NAME)
	@printf "$(BLUE)%s$(RESET): $(GREEN)Successfully built $(NAME)$(RESET)\n" $(NAME)

mlx:
	@make -C $(MLX_DIR) --no-print-directory

$(OBJ_PATH)%.o: $(SRC_PATH)%.c | $(OBJ_PATH)
	@printf "$(BLUE)%s$(RESET): $(MAGENTA)Compiling$(RESET) $<\n" $(NAME)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(LIBFT):
	@make -C $(LIBFT_DIR) all --no-print-directory

clean:
	@printf "$(BLUE)%s$(RESET): $(RED)Cleaning object files...$(RESET)\n"
	@rm -rf obj
	@make -C $(LIBFT_DIR) clean --no-print-directory

fclean: clean
	@printf "$(BLUE)%s$(RESET): $(RED)Full clean...$(RESET)\n"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	@make -C $(MLX_DIR) clean --no-print-directory

re: fclean all

bonus: all

-include $(DEPS)

.PHONY: all clean fclean re mlx bonus
.DELETE_ON_ERROR:
