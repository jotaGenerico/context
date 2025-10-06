/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ato_octa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:24:57 by jose-cad          #+#    #+#             */
/*   Updated: 2025/08/12 10:25:03 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_ato_octa(const char *str)
{
	long	result;

	if (!str)
		return (0);
	result = ft_atoi_base(str, "01234567");
	if (result < 0)
		return (0);
	return ((unsigned int)result);
}
