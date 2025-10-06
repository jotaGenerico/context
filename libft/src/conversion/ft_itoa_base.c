/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 23:44:23 by jose-cad          #+#    #+#             */
/*   Updated: 2025/08/12 23:44:28 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_check_base(char *base);
static int	ft_nbrlen(unsigned int n, int b_len);
static void	ft_fill_edge(char *result, char *base, int n_len, int nbr);

char	*ft_itoa_base(int nbr, char *base)
{
	char			*result;
	int				b_len;
	int				n_len;
	unsigned int	n;

	if (nbr < 0)
		n = (unsigned int)(-(long)nbr);
	else
		n = nbr;
	b_len = ft_check_base(base);
	if (b_len < 2)
		return (NULL);
	n_len = ft_nbrlen(n, b_len);
	if (nbr < 0)
		n_len++;
	result = malloc(sizeof(char) * (n_len + 1));
	if (!result)
		return (NULL);
	ft_fill_edge(result, base, n_len, nbr);
	while (n > 0)
	{
		result[--n_len] = base[n % b_len];
		n /= b_len;
	}
	return (result);
}

static void	ft_fill_edge(char *result, char *base, int n_len, int nbr)
{
	result[n_len] = '\0';
	if (nbr < 0)
		result[0] = '-';
	if (nbr == 0)
		result[0] = base[0];
}

static int	ft_nbrlen(unsigned int n, int b_len)
{
	int	n_len;

	n_len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= b_len;
		n_len++;
	}
	return (n_len);
}

static int	ft_check_base(char *base)
{
	int	i;
	int	j;

	i = 0;
	while (base[i])
	{
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		if (base[i] == '+' || base[i] == '-' || ft_isspace(base[i]))
			return (0);
		i++;
	}
	return (i);
}
