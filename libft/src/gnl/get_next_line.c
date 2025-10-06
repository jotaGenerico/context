/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jota <jota@student.42sp.org.br>             +#+  +:+       +#+       */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 21:45:00 by jota              #+#    #+#             */
/*   Updated: 2025/07/27 22:00:00 by jota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*gnl_read_until_newline(int fd, char *storage);
static char	*gnl_extract_line(char *storage);
static char	*gnl_save_remainder(char *storage);

char	*get_next_line(int fd)
{
	static char	*storage[1024];
	char		*line;

	if (fd < 0 || fd >= 1024 || GNL_SIZE <= 0)
		return (NULL);
	storage[fd] = gnl_read_until_newline(fd, storage[fd]);
	if (!storage[fd])
		return (NULL);
	line = gnl_extract_line(storage[fd]);
	if (!line)
	{
		storage[fd] = gnl_free(storage[fd], NULL);
		return (NULL);
	}
	storage[fd] = gnl_save_remainder(storage[fd]);
	return (line);
}

static char	*gnl_save_remainder(char *storage)
{
	size_t	i;
	size_t	j;
	char	*new_storage;

	if (!storage)
		return (NULL);
	i = 0;
	while (storage[i] && storage[i] != '\n')
		i++;
	if (!storage[i])
		return (gnl_free(storage, NULL));
	i++;
	new_storage = malloc(gnl_strlen(storage + i) + 1);
	if (!new_storage)
		return (gnl_free(storage, NULL));
	j = 0;
	while (storage[i])
		new_storage[j++] = storage[i++];
	new_storage[j] = '\0';
	free(storage);
	return (new_storage);
}

static char	*gnl_extract_line(char *storage)
{
	size_t	i;
	char	*line;

	if (!storage || !storage[0])
		return (NULL);
	i = 0;
	while (storage[i] && storage[i] != '\n')
		i++;
	if (storage[i] == '\n')
		line = malloc(i + 2);
	else
		line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (storage[i] && storage[i] != '\n')
	{
		line[i] = storage[i];
		i++;
	}
	if (storage[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*gnl_read_until_newline(int fd, char *storage)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = malloc(GNL_SIZE + 1);
	if (!buffer)
		return (gnl_free(storage, NULL));
	bytes_read = 1;
	while (!gnl_strchr(storage, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, GNL_SIZE);
		if (bytes_read < 0)
			return (gnl_free(storage, buffer));
		buffer[bytes_read] = '\0';
		storage = gnl_strjoin(storage, buffer);
		if (!storage)
			return (gnl_free(buffer, NULL));
	}
	free(buffer);
	return (storage);
}
