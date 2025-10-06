# **************************************************************************** #
#                             Minitalk/Libft Makefile                          #
# **************************************************************************** #

# Program Names
NAME_SERVER 	= server
NAME_CLIENT 	= client
NAME_SERVER_B 	= server_bonus
NAME_CLIENT_B 	= client_bonus

# Directories
SRC_DIR 		= srcs
SRC_BONUS_DIR 		= srcs_bonus
INC_DIR 		= includes
LIBFT_DIR 		= libft

# Compiler Flags and Tools
CC 			= cc
CFLAGS 			= -Wall -Wextra -Werror -g
RM 			= rm -f

# Include Paths (-I)
# Garante que o gcc encontre minitalk.h/minitalk_bonus.h e libft.h
INCLUDES 	= -I$(INC_DIR) -I$(LIBFT_DIR)/include

# Library Linker Flags (-L and -l)
# Linka com a libft.a que está em $(LIBFT_DIR)
LIBS 		= -L$(LIBFT_DIR) -lft

# Mandatory Sources
SRCS_SERVER 	= $(SRC_DIR)/server.c
SRCS_CLIENT 	= $(SRC_DIR)/client.c

# Bonus Sources
SRCS_SERVER_B 	= $(SRC_BONUS_DIR)/server_bonus.c
SRCS_CLIENT_B 	= $(SRC_BONUS_DIR)/client_bonus.c

# Targets List
TARGETS_MANDATORY = $(NAME_SERVER) $(NAME_CLIENT)
TARGETS_BONUS = $(NAME_SERVER_B) $(NAME_CLIENT_B)


# --- PHONY RULES ---

.PHONY: all mandatory bonus clean fclean re libft

all: mandatory

mandatory: $(TARGETS_MANDATORY)

bonus: $(TARGETS_BONUS)

# --- COMPILATION RULES ---

# Compila Libft primeiro
$(LIBFT_DIR)/libft.a:
	@echo "\n$(GREEN)--- Compilando Libft ---$(NC)"
	@make -C $(LIBFT_DIR)
	@echo "$(GREEN)----------------------$(NC)\n"

# Regra Genérica de Linkagem (Usa $^ para todas as dependências e $@ para o target)
$(TARGETS_MANDATORY) $(TARGETS_BONUS): $(LIBFT_DIR)/libft.a

$(NAME_SERVER): $(SRCS_SERVER)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)

$(NAME_CLIENT): $(SRCS_CLIENT)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)

$(NAME_SERVER_B): $(SRCS_SERVER_B)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)

$(NAME_CLIENT_B): $(SRCS_CLIENT_B)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)


# --- CLEANING RULES ---

clean:
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	$(RM) $(TARGETS_MANDATORY) $(TARGETS_BONUS)

re: fclean all

# --- COLORS (Opcional, mas útil para a 42) ---
GREEN = \033[0;32m
NC = \033[0m
