/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-cad <jose-cad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 16:04:03 by jose-cad          #+#    #+#             */
/*   Updated: 2025/12/01 16:04:04 by jose-cad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin3(char const *s1, char const *s2, char const *s3)
{
	size_t	total_len;
	char	*new_str;

	if (!s1 || !s2 || !s3)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;
	new_str = malloc(sizeof(char) * total_len);
	if (!new_str)
		return (NULL);
	new_str[0] = '\0';
	ft_strlcat(new_str, s1, total_len);
	ft_strlcat(new_str, s2, total_len);
	ft_strlcat(new_str, s3, total_len);
	return (new_str);
}

void	clean_exit_child(t_shell *shell, int status)
{
	if (shell->ast)
		ast_free(shell->ast);
	cleanup_shell(shell);
	exit(status);
}
