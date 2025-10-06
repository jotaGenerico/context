/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@42sp.org.br>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:22:17 by jose-cad          #+#    #+#             */
/*   Updated: 2025/09/04 14:22:20 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_count_words(const char *str, char sep);
static char	*ft_get_word(const char *str, char sep);
static void	ft_free_split(char **arr, int last);

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		words;
	int		i;

	words = ft_count_words(s, c);
	arr = malloc(sizeof(char *) * (words + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			arr[i] = ft_get_word(s, c);
			if (!arr[i++])
				return (ft_free_split(arr, i), NULL);
			while (*s && *s != c)
				s++;
		}
	}
	arr[i] = NULL;
	return (arr);
}

static void	ft_free_split(char **arr, int last)
{
	while (last > 0)
		free(arr[--last]);
	free(arr);
}

static char	*ft_get_word(const char *str, char sep)
{
	int		len;
	char	*word;

	len = 0;
	while (str[len] && str[len] != sep)
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	len = 0;
	while (str[len] && str[len] != sep)
	{
		word[len] = str[len];
		len++;
	}
	word[len] = '\0';
	return (word);
}

static int	ft_count_words(const char *str, char sep)
{
	int	count;

	count = 0;
	while (*str && *str == sep)
		str++;
	while (*str)
	{
		count++;
		while (*str && *str != sep)
			str++;
		while (*str && *str == sep)
			str++;
	}
	return (count);
}
