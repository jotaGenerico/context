# **************************************************************************** #
#                          Philosophers MAKEFILE (Norma 42)                    #
# **************************************************************************** #

# --- Nomes e Caminhos ---
NAME		= philo
CC		= cc
CFLAGS		= -Wall -Wextra -Werror -pthread -g
INCLUDES	= -I$(INC_DIR)


# --- Diretórios ---
SRC_DIR		= srcs
OBJ_DIR		= obj
INC_DIR		= includes

# --- All ---
SRCS	= $(SRC_DIR)/init.c \
			$(SRC_DIR)/main.c \
			$(SRC_DIR)/monitor.c \
			$(SRC_DIR)/parsing.c \
			$(SRC_DIR)/routine.c \
			$(SRC_DIR)/simulation.c \
			$(SRC_DIR)/time.c \
			$(SRC_DIR)/utils.c

# --- Lista geral ---
OBJS		= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# --- Cores ---
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
RED			= \033[0;31m
RESET		= \033[0m

# --- Regras principais ---
.PHONY: all clean fclean re valgrind

# ---- Compilação completa -------------------------------------------------
all: $(NAME)
$(NAME): $(OBJS)
	@echo "$(YELLOW)Linkando $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compilado com sucesso!$(RESET)"

# ---- Compilação de cada objeto -------------------------------------------
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)                     # garante que o diretório exista
	@echo "$(YELLOW)Compilando: $<$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# ---- Limpeza -------------------------------------------------------------
clean:
	@echo "$(RED)Removendo objetos...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)✓ Objetos removidos$(RESET)"
fclean: clean
	@echo "$(RED)Removendo executável $(NAME)...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)✓ Limpeza completa$(RESET)"
re: fclean all

# ---- Valgrind (mantido, sem supressão de readline) -----------------------
ARGS ?= 5 800 200 200

valgrind: $(NAME)
	@echo "\033[1;36m[VALGRIND]\033[0m Executando análise de memória..."
	@valgrind --track-fds=yes \
			--leak-check=full \
			--show-leak-kinds=all \
			--suppressions=pthread.supp \
			--suppressions=glibc.supp ./$(NAME) $(ARGS)