/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:29:23 by jose-cad          #+#    #+#             */
/*   Updated: 2025/08/12 10:29:28 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digits(unsigned int nbr, size_t base_len);

char	*ft_utoa_base(unsigned int nbr, const char *base)
{
	char	*str;
	size_t	base_len;
	size_t	len;

	if (!ft_base_is_valid(base))
		return (NULL);
	base_len = ft_strlen(base);
	len = ft_count_digits(nbr, base_len);
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = base[nbr % base_len];
		nbr /= base_len;
	}
	return (str);
}

static int	ft_count_digits(unsigned int nbr, size_t base_len)
{
	int	count;

	if (nbr == 0)
		return (1);
	count = 0;
	while (nbr > 0)
	{
		nbr /= base_len;
		count++;
	}
	return (count);
}
