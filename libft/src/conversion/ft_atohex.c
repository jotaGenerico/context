/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atohex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:26:03 by jose-cad          #+#    #+#             */
/*   Updated: 2025/08/12 10:26:09 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_atohex(const char *str)
{
	long	result;

	if (!str)
		return (0);
	result = ft_atoi_base(str, "0123456789ABCDEF");
	if (result < 0)
		return (0);
	return ((unsigned int)result);
}
