// srcs/core/termios.c
#include "minishell.h"

// Variável global para salvar o estado original (assumindo que existe)
static struct termios	g_saved_termios;

/* Salva o estado atual e configura o terminal para o modo shell (sem ECHO/ICANON) */
void	set_shell_mode(void)
{
	struct termios	new_termios;

	// Salva o estado original do terminal ANTES da primeira alteração
	if (tcgetattr(STDIN_FILENO, &g_saved_termios) == -1)
		return ;

	new_termios = g_saved_termios;

	// O mais importante é desabilitar ISIG, mas vamos manter o modo 'raw' base
    // que a 42 costuma usar, onde readline é responsável pelo resto.
	new_termios.c_lflag &= ~(ISIG);

	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

/* Restaura o terminal para o modo canônico (com ECHO e ICANON) */
void	set_canonical_mode(void)
{
	struct termios	canonical_termios;

	if (tcgetattr(STDIN_FILENO, &canonical_termios) == -1)
		return ;

	// Habilita ICANON e ECHO (Modo padrão de entrada por linha)
	canonical_termios.c_lflag |= (ICANON | ECHO);

	tcsetattr(STDIN_FILENO, TCSANOW, &canonical_termios);
}

/* Restaura o terminal para o estado inicial salvo */
void	restore_termios(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_saved_termios);
}
