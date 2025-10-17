# ==================================================================================
# SO_LONG - MAKEFILE
# ==================================================================================

# ----------------- NOMES DOS EXECUTÁVEIS -----------------
NAME        = so_long
BONUS_NAME  = so_long_bonus

# ----------------- COMPILADOR E FLAGS -----------------
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -g
LDFLAGS     = -no-pie
INCLUDES    = -Iincludes -I$(MLX_DIR) -I$(LIBFT_DIR)/include

# ----------------- DIRETÓRIOS -----------------
LIBFT_DIR   = libft
MLX_DIR     = minilibx
SRCS_DIR    = srcs
BONUS_DIR   = srcs_bonus
OBJ_DIR     = .objects
BONUS_OBJ_DIR = .objects_bonus

# ----------------- BIBLIOTECAS -----------------
LIBFT       = $(LIBFT_DIR)/libft.a
MLX         = $(MLX_DIR)/libmlx.a
MLX_FLAGS   = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

# ----------------- ARQUIVOS FONTE (MANDATORY) -----------------
SRCS        = $(SRCS_DIR)/main.c \
              $(SRCS_DIR)/map_parsing.c \
              $(SRCS_DIR)/map_validation.c \
              $(SRCS_DIR)/map_validation_utils.c \
              $(SRCS_DIR)/map_flood_fill.c \
              $(SRCS_DIR)/game_init.c \
              $(SRCS_DIR)/game_render.c \
              $(SRCS_DIR)/game_events.c \
              $(SRCS_DIR)/utils.c

# ----------------- ARQUIVOS FONTE (BONUS) -----------------
BONUS_SRCS  = $(BONUS_DIR)/main_bonus.c \
              $(BONUS_DIR)/map_parsing_bonus.c \
              $(BONUS_DIR)/map_validation_bonus.c \
              $(BONUS_DIR)/map_validation_utils_bonus.c \
              $(BONUS_DIR)/map_flood_fill_bonus.c \
              $(BONUS_DIR)/game_init_bonus.c \
              $(BONUS_DIR)/animation_bonus.c \
              $(BONUS_DIR)/enemies_bonus.c \
              $(BONUS_DIR)/enemies_utils_bonus.c \
              $(BONUS_DIR)/ui_bonus.c \
              $(BONUS_DIR)/ui_utils_bonus.c \
              $(BONUS_DIR)/game_events_bonus.c \
              $(BONUS_DIR)/map_utils_bonus.c \
              $(BONUS_DIR)/cleanup_bonus.c \
              $(BONUS_DIR)/exit_bonus.c \
              $(BONUS_DIR)/load_sprites_bonus.c

# ----------------- ARQUIVOS OBJETO -----------------
OBJS        = $(SRCS:$(SRCS_DIR)/%.c=$(OBJ_DIR)/%.o)
BONUS_OBJS  = $(BONUS_SRCS:$(BONUS_DIR)/%.c=$(BONUS_OBJ_DIR)/%.o)

# ----------------- CORES PARA OUTPUT -----------------
GREEN       = \033[0;32m
YELLOW      = \033[0;33m
RED         = \033[0;31m
RESET       = \033[0m

# ==================================================================================
# REGRAS PRINCIPAIS
# ==================================================================================

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) $(LIBFT_FLAGS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)✓ SUCCESS: $(NAME) created$(RESET)"

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(LIBFT) $(MLX) $(BONUS_OBJS)
	@echo "$(YELLOW)Linking $(BONUS_NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(MLX_FLAGS) $(LIBFT_FLAGS) $(LDFLAGS) -o $(BONUS_NAME)
	@echo "$(GREEN)✓ SUCCESS: $(BONUS_NAME) created$(RESET)"

# ----------------- COMPILAÇÃO DE OBJETOS (MANDATORY) -----------------
$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# ----------------- COMPILAÇÃO DE OBJETOS (BONUS) -----------------
$(BONUS_OBJ_DIR)/%.o: $(BONUS_DIR)/%.c
	@mkdir -p $(BONUS_OBJ_DIR)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# ----------------- BIBLIOTECAS -----------------
$(LIBFT):
	@echo "$(YELLOW)Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@echo "$(GREEN)✓ libft compiled$(RESET)"

$(MLX):
	@echo "$(YELLOW)Building minilibx...$(RESET)"
	@$(MAKE) -C $(MLX_DIR) --no-print-directory 2>/dev/null || true
	@echo "$(GREEN)✓ minilibx compiled$(RESET)"

# ==================================================================================
# REGRAS DE LIMPEZA
# ==================================================================================

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@$(MAKE) -C $(MLX_DIR) clean --no-print-directory 2>/dev/null || true
	@echo "$(GREEN)✓ Object files removed$(RESET)"

fclean: clean
	@echo "$(RED)Removing executables...$(RESET)"
	@rm -f $(NAME) $(BONUS_NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(GREEN)✓ Executables removed$(RESET)"

re: fclean all

# ==================================================================================
# PHONY
# ==================================================================================

.PHONY: all bonus clean fclean re
