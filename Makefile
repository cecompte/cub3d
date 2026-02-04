CC				= cc
CFLAGS			= -g3 -Wall -Wextra -Werror -MMD -MP
INCLUDES		= -Iincludes -Ilibft -I./minilibx-linux
LDFLAGS			= -L./minilibx-linux -lmlx -lXext -lX11 -lm
NAME			= cub3d
NAME_BONUS		= cub3d_bonus

# Mandatory Sources
SRC_PATH		= src/
SRC				= main.c \
					map.c \
					parce_config.c \
					map_grid.c \
					map_utils.c \
					init.c \
					texture_operation.c \
					utils.c \
					movements.c \
					rays.c \
					clean.c \
					render.c \
					map_grid_utils.c \

SOURCES			= $(addprefix $(SRC_PATH), $(SRC))

# Bonus Sources
SRC_PATH_BONUS	= src_bonus/
SRC_BONUS		= main.c \
					map.c \
					parce_config.c \
					map_grid.c \
					map_utils.c \
					init.c \
					texture_operation.c \
					utils.c \
					movements.c \
					rays.c \
					clean.c \
					render_frame.c \
					draw_minimap.c \
					draw_player_minimap.c \
					doors_init.c \
					doors_utils.c \
					clean_utils.c \
					mouse.c

SOURCES_BONUS	= $(addprefix $(SRC_PATH_BONUS), $(SRC_BONUS))

# Mlx
MLX_DIR 		= ./minilibx-linux
MLX_LIB 		= $(MLX_DIR)/libmlx_$(UNAME).a

# Mandatory Objects
OBJ_PATH		= obj/
OBJ				= $(SRC:.c=.o)
OBJECTS			= $(addprefix $(OBJ_PATH), $(OBJ))
DEP				= $(SRC:.c=.d)
DEPS			= $(addprefix $(OBJ_PATH), $(DEP))

# Bonus Objects
OBJ_PATH_BONUS	= obj_bonus/
OBJ_BONUS		= $(SRC_BONUS:.c=.o)
OBJECTS_BONUS	= $(addprefix $(OBJ_PATH_BONUS), $(OBJ_BONUS))
DEP_BONUS		= $(SRC_BONUS:.c=.d)
DEPS_BONUS		= $(addprefix $(OBJ_PATH_BONUS), $(DEP_BONUS))

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
	@$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT_FLAGS) $(LDFLAGS) -o $(NAME)
	@printf "$(BLUE)%s$(RESET): $(GREEN)Successfully built $(NAME)$(RESET)\n" $(NAME)

mlx:
	@make -C $(MLX_DIR) --no-print-directory

$(OBJ_PATH)%.o: $(SRC_PATH)%.c | $(OBJ_PATH)
	@printf "$(BLUE)%s$(RESET): $(MAGENTA)Compiling$(RESET) $<\n" $(NAME)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_PATH_BONUS)%.o: $(SRC_PATH_BONUS)%.c | $(OBJ_PATH_BONUS)
	@printf "$(BLUE)%s$(RESET): $(MAGENTA)Compiling$(RESET) $<\n" $(NAME_BONUS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH_BONUS):
	@mkdir -p $(OBJ_PATH_BONUS)

$(LIBFT):
	@make -C $(LIBFT_DIR) all --no-print-directory

clean:
	@printf "$(BLUE)%s$(RESET): $(RED)Cleaning object files...$(RESET)\n"
	@rm -rf obj obj_bonus
	@make -C $(LIBFT_DIR) clean --no-print-directory

fclean: clean
	@printf "$(BLUE)%s$(RESET): $(RED)Full clean...$(RESET)\n"
	@rm -f $(NAME) $(NAME_BONUS)
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	@make -C $(MLX_DIR) clean --no-print-directory

re: fclean all

bonus: $(LIBFT) mlx $(NAME_BONUS)

$(NAME_BONUS): $(OBJECTS_BONUS)
	@printf "$(BLUE)%s$(RESET): $(YELLOW)Building $(NAME_BONUS)...$(RESET)\n" $(NAME_BONUS)
	@$(CC) $(CFLAGS) $(OBJECTS_BONUS) $(LIBFT_FLAGS) $(LDFLAGS) -o $(NAME_BONUS)
	@printf "$(BLUE)%s$(RESET): $(GREEN)Successfully built $(NAME_BONUS)$(RESET)\n" $(NAME_BONUS)

-include $(DEPS)
-include $(DEPS_BONUS)

.PHONY: all clean fclean re mlx bonus
.DELETE_ON_ERROR:
