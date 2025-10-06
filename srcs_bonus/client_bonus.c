/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 23:50:02 by jose-cad          #+#    #+#             */
/*   Updated: 2025/10/03 23:50:08 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	confirmation_handler(int sig);
static void	send_char(pid_t server_pid, unsigned char c);
static int	validate_args(int argc, char **argv);

int	main(int argc, char **argv)
{
	pid_t	server_pid;
	char	*message;
	int		i;

	if (!validate_args(argc, argv))
		return (1);
	server_pid = ft_atoi(argv[1]);
	message = argv[2];
	signal(SIGUSR1, confirmation_handler);
	signal(SIGUSR2, confirmation_handler);
	i = 0;
	while (message[i] != '\0')
	{
		send_char(server_pid, message[i]);
		i++;
	}
	send_char(server_pid, '\0');
	while (1)
		pause();
	return (0);
}

static void	confirmation_handler(int sig)
{
	if (sig == SIGUSR2)
	{
		ft_putstr_fd("Success: Message delivered\n", 1);
		exit(0);
	}
}

static int	validate_args(int argc, char **argv)
{
	pid_t	server_pid;

	if (argc != 3)
	{
		ft_putstr_fd("Uso: ./client <PID_DO_SERVIDOR> <MENSAGEM>\n", 2);
		return (0);
	}
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
	{
		ft_putstr_fd("Erro: PID inválido.\n", 2);
		return (0);
	}
	return (1);
}

static void	send_char(pid_t server_pid, unsigned char c)
{
	int	i;

	i = 8;
	while (i--)
	{
		if ((c >> i) & 1)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		pause();
		usleep(50);
	}
}
