/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_digits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:35:47 by jose-cad          #+#    #+#             */
/*   Updated: 2025/08/12 10:35:52 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_digits(unsigned int nbr, size_t base_len)
{
	size_t	count;

	count = 1;
	while (nbr >= base_len)
	{
		nbr /= base_len;
		count++;
	}
	return (count);
}
