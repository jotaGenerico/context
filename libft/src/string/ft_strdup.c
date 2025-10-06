/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:21:01 by jose-cad          #+#    #+#             */
/*   Updated: 2025/09/04 14:21:05 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*duplicate;

	len = ft_strlen(s) + 1;
	duplicate = malloc(sizeof(char) * len);
	if (duplicate == NULL)
		return (NULL);
	ft_memcpy(duplicate, s, len);
	return (duplicate);
}
