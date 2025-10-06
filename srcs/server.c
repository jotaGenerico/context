/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 23:50:02 by jose-cad          #+#    #+#             */
/*   Updated: 2025/10/03 23:50:08 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	display_pid(void);
static void	process_complete_char(t_server *data);
static void	signal_handler(int sig, siginfo_t *info, void *context);

int	main(void)
{
	struct sigaction	sa;

	display_pid();
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}

static void	display_pid(void)
{
	pid_t	pid;

	pid = getpid();
	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
}

static void	process_complete_char(t_server *data)
{
	if (data->current_char == '\0')
	{
		write(1, "\n", 1);
		data->client_pid = 0;
	}
	else
		write(1, &data->current_char, 1);
	data->bits_received = 0;
	data->current_char = 0;
}

static void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static t_server	data;
	pid_t			pid_to_ack;

	(void)context;
	if (data.client_pid == 0)
		data.client_pid = info->si_pid;
	pid_to_ack = data.client_pid;
	data.current_char |= (sig == SIGUSR2);
	data.bits_received++;
	if (data.bits_received == 8)
		process_complete_char(&data);
	else
		data.current_char <<= 1;
	if (pid_to_ack != 0)
		kill(pid_to_ack, SIGUSR1);
}
