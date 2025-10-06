/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atohex_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:37:32 by jose-cad          #+#    #+#             */
/*   Updated: 2025/08/12 10:37:38 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long	ft_atohex_ptr(const char *hex_str)
{
	long	result;

	if (!hex_str)
		return (0);
	result = ft_atoi_base(hex_str, "0123456789abcdef");
	if (result < 0)
		return (0);
	return ((unsigned long)result);
}
