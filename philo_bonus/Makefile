# **************************************************************************** #
#                            PHILOSOPHERS BONUS                                 #
# **************************************************************************** #

NAME        = philo_bonus
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -pthread -g
INCLUDES    = -I$(INC_DIR)

# Diretórios
SRC_DIR     = srcs
OBJ_DIR     = obj
INC_DIR     = includes

# Arquivos
SRCS        = $(SRC_DIR)/main_bonus.c \
              $(SRC_DIR)/parsing_bonus.c \
              $(SRC_DIR)/actions_bonus.c \
              $(SRC_DIR)/simulation_bonus.c \
              $(SRC_DIR)/process_bonus.c \
              $(SRC_DIR)/time_bonus.c \
              $(SRC_DIR)/utils_bonus.c

OBJS        = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
DEPS        = $(INC_DIR)/philo_bonus.h

# Cores
GREEN       = \033[0;32m
YELLOW      = \033[0;33m
RED         = \033[0;31m
RESET       = \033[0m

# ---- Regras ----
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)Linkando $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) compilado com sucesso!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW)Compilando: $<$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)✓ Objetos removidos$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(GREEN)✓ Executável removido$(RESET)"

re: fclean all
