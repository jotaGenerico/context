/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:19:44 by jose-cad          #+#    #+#             */
/*   Updated: 2025/09/04 14:19:48 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *base, const char *target, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*target == '\0')
		return ((char *)base);
	while (i < len && base[i])
	{
		j = 0;
		while (target[j] && (i + j) < len && base[i + j] == target[j])
			j++;
		if (target[j] == '\0')
			return ((char *)&base[i]);
		i++;
	}
	return (NULL);
}
