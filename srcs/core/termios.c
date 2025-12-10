/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:35:50 by jose-cad          #+#    #+#             */
/*   Updated: 2025/12/10 16:37:43 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static struct termios	g_original_termios;

void	setup_terminal(void)
{
	struct termios	current_termios;

	if (tcgetattr(STDIN_FILENO, &g_original_termios) == -1)
		return ;
	current_termios = g_original_termios;
	current_termios.c_cc[VQUIT] = _POSIX_VDISABLE;
	current_termios.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &current_termios) == -1)
		perror("tcsetattr");
}

void	restore_terminal(void)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &g_original_termios) == -1)
		perror("tcsetattr");
}

void	set_heredoc_tty(void)
{
	struct termios	heredoc_termios;

	if (tcgetattr(STDIN_FILENO, &heredoc_termios) == -1)
		return ;
	heredoc_termios.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &heredoc_termios) == -1)
		perror("tcsetattr");
}

void	restore_heredoc_tty(void)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, &g_original_termios) == -1)
		perror("tcsetattr");
}
