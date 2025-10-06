/*                                                        :::      ::::::::   */
/*   ft_ptr_hextoa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:29:06 by jose-cad          #+#    #+#             */
/*   Updated: 2025/08/12 10:29:10 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_ptr_hextoa(unsigned long ptr)
{
	const char	*base = "0123456789abcdef";
	char		buf[19];
	int			i;

	i = 18;
	buf[i--] = '\0';
	if (ptr == 0)
		buf[i--] = '0';
	while (ptr > 0)
	{
		buf[i--] = base[ptr % 16];
		ptr /= 16;
	}
	return (ft_strdup(&buf[i + 1]));
}
