# **************************************************************************** #
#                          Philosophers MAKEFILE (Norma 42)                    #
# **************************************************************************** #

# --- Nomes e Caminhos ---
NAME        = philo
BONUS_NAME  = philo_bonus
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -pthread -g
INCLUDES    = -I$(INC_DIR)

# --- Debug flag (logs alinhados em stderr) ---
ifeq ($(DEBUG),1)
	CFLAGS += -DDEBUG_PRINT
endif

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
DEPS        = $(INC_DIR)/philo.h

# --- Cores ---
GREEN       = \033[0;32m
YELLOW      = \033[0;33m
RED         = \033[0;31m
BLUE        = \033[0;34m
RESET       = \033[0m

# --- Valgrind suppressions ---
SUPP_FLAGS  = --suppressions=glibc.supp --suppressions=pthread.supp

# --- Regras principais ---
.PHONY: all clean fclean re valgrind norm bonus bonus_clean bonus_fclean bonus_re bonus_valgrind bonus_helgrind

# ---- Compilação completa -------------------------------------------------
all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Linkando $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compilado com sucesso!$(RESET)"

# ---- Compilação de cada objeto -------------------------------------------
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
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
	@$(MAKE) -s bonus_clean || true

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		echo "$(RED)Removendo executável $(NAME)...$(RESET)"; \
		rm -f $(NAME); \
		echo "$(GREEN)✓ $(NAME) removido$(RESET)"; \
	else \
		echo "$(BLUE)ℹ Executável $(NAME) não existe$(RESET)"; \
	fi
	@$(MAKE) -s bonus_fclean || true
	@echo "$(GREEN)✓ Limpeza completa realizada$(RESET)"

re: fclean all

# ---- Bônus (processos + semáforos) --------------------------------------
BONUS_SRC_DIR = bonus/srcs
BONUS_OBJ_DIR = bonus/obj
BONUS_INC_DIR = bonus/includes

BONUS_SRCS = $(BONUS_SRC_DIR)/main_bonus.c \
             $(BONUS_SRC_DIR)/parsing_bonus.c \
             $(BONUS_SRC_DIR)/routine_bonus.c \
             $(BONUS_SRC_DIR)/simulation_bonus.c \
             $(BONUS_SRC_DIR)/time_bonus.c \
             $(BONUS_SRC_DIR)/utils_bonus.c

BONUS_OBJS = $(patsubst $(BONUS_SRC_DIR)/%.c,$(BONUS_OBJ_DIR)/%.o,$(BONUS_SRCS))
BONUS_DEPS = $(BONUS_INC_DIR)/philo_bonus.h

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJS)
	@echo "$(YELLOW)Linkando $(BONUS_NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME)
	@echo "$(GREEN)✓ $(BONUS_NAME) compilado com sucesso!$(RESET)"

$(BONUS_OBJ_DIR)/%.o: $(BONUS_SRC_DIR)/%.c $(BONUS_DEPS)
	@mkdir -p $(BONUS_OBJ_DIR)
	@echo "$(YELLOW)Compilando (bonus): $<$(RESET)"
	@$(CC) $(CFLAGS) -I$(BONUS_INC_DIR) -c $< -o $@

bonus_clean:
	@if [ -d "$(BONUS_OBJ_DIR)" ]; then \
		echo "$(RED)Removendo diretório $(BONUS_OBJ_DIR)/ e objetos...$(RESET)"; \
		rm -rf $(BONUS_OBJ_DIR); \
		echo "$(GREEN)✓ Objetos e diretório removidos (bonus)$(RESET)"; \
	else \
		echo "$(BLUE)ℹ Nada para limpar ($(BONUS_OBJ_DIR)/ não existe)$(RESET)"; \
	fi

bonus_fclean: bonus_clean
	@if [ -f "$(BONUS_NAME)" ]; then \
		echo "$(RED)Removendo executável $(BONUS_NAME)...$(RESET)"; \
		rm -f $(BONUS_NAME); \
		echo "$(GREEN)✓ $(BONUS_NAME) removido$(RESET)"; \
	else \
		echo "$(BLUE)ℹ Executável $(BONUS_NAME) não existe$(RESET)"; \
	fi

bonus_re: bonus_fclean bonus

# ---- Valgrind ------------------------------------------------------------
ARGS ?= 5 800 200 200

valgrind: $(NAME)
	@echo "$(BLUE)[VALGRIND]$(RESET) Executando análise de memória..."
	@valgrind $(SUPP_FLAGS) --track-fds=yes \
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

# ---- Valgrind/Helgrind para bônus --------------------------------------
bonus_valgrind: $(BONUS_NAME)
	@echo "$(BLUE)[VALGRIND BONUS]$(RESET) Executando análise de memória..."
	@valgrind $(SUPP_FLAGS) --track-fds=yes \
	          --leak-check=full \
	          --show-leak-kinds=all \
	          --track-origins=yes \
	          ./$(BONUS_NAME) $(ARGS)

bonus_helgrind: $(BONUS_NAME)
	@echo "$(BLUE)[HELGRIND BONUS]$(RESET) Detectando data races..."
	@valgrind --tool=helgrind \
	          --history-level=approx \
	          ./$(BONUS_NAME) $(ARGS)

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
