# **************************************************************************** #
#                          Philosophers MAKEFILE (Norma 42)                    #
# **************************************************************************** #

# --- Nomes e Caminhos ---
NAME        = philo
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -pthread -g
INCLUDES    = -I$(INC_DIR)

# --- Diretórios ---
SRC_DIR     = srcs
OBJ_DIR     = obj
INC_DIR     = includes

# --- Arquivos ---
SRCS        = $(SRC_DIR)/init.c \
              $(SRC_DIR)/main.c \
              $(SRC_DIR)/monitor.c \
              $(SRC_DIR)/parsing.c \
              $(SRC_DIR)/routine.c \
              $(SRC_DIR)/simulation.c \
              $(SRC_DIR)/time.c \
              $(SRC_DIR)/utils.c

OBJS        = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# --- Cores ---
GREEN       = \033[0;32m
YELLOW      = \033[0;33m
RED         = \033[0;31m
BLUE        = \033[0;34m
RESET       = \033[0m

# --- Regras principais ---
.PHONY: all clean fclean re valgrind norm

# ---- Compilação completa -------------------------------------------------
all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Linkando $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compilado com sucesso!$(RESET)"

# ---- Compilação de cada objeto -------------------------------------------
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW)Compilando: $<$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# ---- Limpeza -------------------------------------------------------------
clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
		echo "$(RED)Removendo diretório $(OBJ_DIR)/ e objetos...$(RESET)"; \
		rm -rf $(OBJ_DIR); \
		echo "$(GREEN)✓ Objetos e diretório removidos$(RESET)"; \
	else \
		echo "$(BLUE)ℹ Nada para limpar ($(OBJ_DIR)/ não existe)$(RESET)"; \
	fi

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		echo "$(RED)Removendo executável $(NAME)...$(RESET)"; \
		rm -f $(NAME); \
		echo "$(GREEN)✓ $(NAME) removido$(RESET)"; \
	else \
		echo "$(BLUE)ℹ Executável $(NAME) não existe$(RESET)"; \
	fi
	@echo "$(GREEN)✓ Limpeza completa realizada$(RESET)"

re: fclean all

# ---- Valgrind ------------------------------------------------------------
ARGS ?= 5 800 200 200

valgrind: $(NAME)
	@echo "$(BLUE)[VALGRIND]$(RESET) Executando análise de memória..."
	@valgrind --track-fds=yes \
	          --leak-check=full \
	          --show-leak-kinds=all \
	          --track-origins=yes \
	          ./$(NAME) $(ARGS)

# ---- Helgrind (detecta data races) ---------------------------------------
helgrind: $(NAME)
	@echo "$(BLUE)[HELGRIND]$(RESET) Detectando data races..."
	@valgrind --tool=helgrind \
	          --history-level=approx \
	          ./$(NAME) $(ARGS)

# ---- Norminette ----------------------------------------------------------
norm:
	@echo "$(BLUE)Verificando norminette...$(RESET)"
	@norminette $(SRC_DIR) $(INC_DIR) | grep -v "OK!" || true
	@echo "$(GREEN)✓ Verificação concluída$(RESET)"

# ---- Testes da régua -----------------------------------------------------
test: $(NAME)
	@echo "$(BLUE)========================================$(RESET)"
	@echo "$(YELLOW)Executando testes da régua...$(RESET)"
	@echo "$(BLUE)========================================$(RESET)"
	@echo "\n$(RED)[DEVE MORRER]$(RESET) 1 filósofo:"
	@./$(NAME) 1 800 200 200
	@sleep 1
	@echo "\n$(GREEN)[NÃO DEVE MORRER]$(RESET) 5 filósofos:"
	@timeout 5 ./$(NAME) 5 800 200 200 || true
	@echo "\n$(GREEN)[NÃO DEVE MORRER]$(RESET) 4 filósofos (410ms):"
	@timeout 5 ./$(NAME) 4 410 200 200 || true
	@echo "\n$(RED)[DEVE MORRER]$(RESET) 4 filósofos (310ms):"
	@./$(NAME) 4 310 200 100
	@sleep 1
	@echo "\n$(YELLOW)[PARAR AO COMER 7x]$(RESET) 5 filósofos:"
	@./$(NAME) 5 800 200 200 7
	@echo "$(GREEN)✓ Testes concluídos$(RESET)"
