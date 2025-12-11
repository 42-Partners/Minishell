/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaoliv <rafaoliv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:36:12 by rafaoliv          #+#    #+#             */
/*   Updated: 2025/11/06 15:27:39 by rafaoliv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define MAX_FD 1024

static void	*free_memory(char *stash, char *buffer)
{
	free(stash);
	free(buffer);
	return (NULL);
}

static char	*get_leftovers(char *stash)
{
	char	*new_stash;
	size_t	i;
	size_t	len;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	len = 0;
	while (stash[len])
		len++;
	new_stash = ft_substr(stash, i + 1, len - (i + 1));
	free(stash);
	return (new_stash);
}

static char	*get_new_line(char *stash)
{
	char	*line;
	size_t	i;

	if (!*stash)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = ft_substr(stash, 0, i);
	return (line);
}

static char	*get_read_line(char *stash, int fd)
{
	char	*buffer;
	char	*temp;
	ssize_t	bytes_read;

	if (!stash)
		stash = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, 1);
	if (!stash || !buffer)
		return (free_memory(stash, buffer));
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(stash, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free_memory(stash, buffer));
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(stash, buffer);
		if (!temp)
			return (free_memory(stash, buffer));
		free(stash);
		stash = temp;
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = get_read_line(stash[fd], fd);
	if (!stash[fd])
		return (NULL);
	line = get_new_line(stash[fd]);
	stash[fd] = get_leftovers(stash[fd]);
	return (line);
}
