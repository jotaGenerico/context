/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 23:50:02 by jose-cad          #+#    #+#             */
/*   Updated: 2025/10/03 23:50:08 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_BONUS_H
# define MINITALK_BONUS_H

# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include "libft.h"

typedef struct s_server
{
	unsigned char	current_char;
	int				bits_received;
	pid_t			client_pid;
}	t_server;

#endif
