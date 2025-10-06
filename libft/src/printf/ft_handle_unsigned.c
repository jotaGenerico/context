/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:40:09 by jose-cad          #+#    #+#             */
/*   Updated: 2025/08/12 10:40:11 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char	*ft_handle_unsigned(t_format *fmt, va_list args)
{
	unsigned int	n;
	char			*num_str;

	n = va_arg(args, unsigned int);
	num_str = ft_utoa_base(n, "0123456789");
	if (!num_str)
		return (NULL);
	num_str = ft_format_output(num_str, fmt);
	return (num_str);
}
