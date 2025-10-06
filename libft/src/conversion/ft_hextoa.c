/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hextoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 10:28:24 by jose-cad          #+#    #+#             */
/*   Updated: 2025/08/12 10:28:30 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_hextoa_lower(unsigned int nbr)
{
	return (ft_utoa_base(nbr, "0123456789abcdef"));
}

char	*ft_hextoa_upper(unsigned int nbr)
{
	return (ft_utoa_base(nbr, "0123456789ABCDEF"));
}
