/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_buffer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:38:42 by jose-cad          #+#    #+#             */
/*   Updated: 2025/08/12 10:38:44 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_flush_buffer(t_buffer *buffer)
{
	if (buffer->index > 0)
	{
		write(buffer->fd, buffer->buf, buffer->index);
		buffer->index = 0;
	}
}

void	ft_add_to_buffer(t_buffer *buffer, char c)
{
	if (buffer->index >= PF_SIZE)
		ft_flush_buffer(buffer);
	buffer->buf[buffer->index++] = c;
	buffer->printed_count++;
}

void	ft_add_str_to_buffer(t_buffer *buffer, const char *str)
{
	size_t	len;
	size_t	i;

	if (!str)
		return ;
	len = ft_strlen(str);
	i = 0;
	while (i < len)
	{
		ft_add_to_buffer(buffer, str[i]);
		i++;
	}
}
