/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dispatch_specifier.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:38:48 by jose-cad          #+#    #+#             */
/*   Updated: 2025/08/12 10:38:50 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_dispatch_specifier(char spec, va_list args, t_format *fmt)
{
	int			i;
	static char	*(*handlers[])(t_format *, va_list) = {
		ft_handle_char, ft_handle_string, ft_handle_decimal, ft_handle_integer,
		ft_handle_unsigned, ft_handle_hex, ft_handle_hex, ft_handle_pointer,
		ft_handle_percent, ft_handle_float, ft_handle_octal, NULL
	};
	static char	handlers_spec[] = {'c', 's', 'd', 'i', 'u', 'x', 'X',
		'p', '%', 'f', 'o', 0};

	i = 0;
	while (handlers_spec[i])
	{
		if (handlers_spec[i] == spec)
			return (handlers[i](fmt, args));
		i++;
	}
	return (NULL);
}
