/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dimatos- <dimatos-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 13:43:26 by dimatos-          #+#    #+#             */
/*   Updated: 2026/07/01 16:17:59 by dimatos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*fill_stash(int fd, char *stash)
{
	char		*tmp;
	char		*buffer;
	ssize_t		bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(stash), NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free (buffer), free(stash), NULL);
		buffer[bytes_read] = '\0';
		if (bytes_read == 0)
			break ;
		tmp = stash;
		stash = ft_strjoin(stash, buffer);
		free(tmp);
		if (!stash)
			return (free (buffer), NULL);
		if (ft_strchr(stash, '\n'))
			break ;
	}
	return (free (buffer), stash);
}

static char	*extract_line(char *stash)
{
	char	*line;
	size_t	i;

	if (!stash || stash[0] == '\0')
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = ft_substr(stash, 0, i);
	return (line);
}

static char	*save_leftover(char *stash)
{
	char	*new_stash;
	size_t	i;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\0')
	{
		free(stash);
		return (NULL);
	}
	new_stash = ft_substr(stash, i + 1, ft_strlen(stash) - i);
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd] = fill_stash(fd, stash[fd]);
	if (!stash[fd] || stash[fd][0] == '\0')
	{
		free (stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	line = extract_line(stash[fd]);
	if (!line)
	{
		free (stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	stash[fd] = save_leftover(stash[fd]);
	return (line);
}
