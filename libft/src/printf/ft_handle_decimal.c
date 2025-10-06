/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_decimal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:39:14 by jose-cad          #+#    #+#             */
/*   Updated: 2025/08/12 10:39:17 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf.h"

char	*ft_handle_decimal(t_format *fmt, va_list args)
{
	int		n;
	char	*str;

	n = va_arg(args, int);
	str = ft_itoa(n);
	if (!str)
		return (NULL);
	return (ft_format_output(str, fmt));
}
