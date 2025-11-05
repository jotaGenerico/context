#include "minishell.h"

// FUNÇÃO 1/1: Junta 3 strings em uma nova alocada
char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	size_t	total_len;
	char	*new_str;

	if (!s1 || !s2 || !s3)
		return (NULL);

	// Calcula o tamanho total (incluindo o '\0')
	total_len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;

	new_str = malloc(sizeof(char) * total_len);
	if (!new_str)
		return (NULL);

	new_str[0] = '\0'; // Inicializa para usar ft_strlcat

	// ft_strlcat é mais seguro para concatenação (tenta adicionar até o tamanho total)
	ft_strlcat(new_str, s1, total_len);
	ft_strlcat(new_str, s2, total_len);
	ft_strlcat(new_str, s3, total_len);

	return (new_str);
}
