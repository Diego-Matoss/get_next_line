#include "get_next_line.h"

static char	*fill_stash(int fd, char *stash)
{
	char		*tmp;
	char		buffer[BUFFER_SIZE + 1];
	ssize_t		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(stash);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		if (bytes_read == 0)
			break ;
		tmp = stash;
		stash = ft_strjoin(stash, buffer);
		free(tmp);
		if (!stash)
			return (NULL);
		if (ft_strchr(stash, '\n'))
			break ;
	}
	return (stash);
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
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = fill_stash(fd, stash);
	if (!stash || stash[0] == '\0')
	{
		free (stash);
		stash = NULL;
		return (NULL);
	}
	line = extract_line(stash);
	if (!line)
	{
		free (stash);
		stash = NULL;
		return (NULL);
	}
	stash = save_leftover(stash);
	return (line);
}

#include <stdio.h>
int main(void)
{
	char	*line;

	line = get_next_line(0);
	printf("%s", line);
	free(line);

	line = get_next_line(0);
	printf("%s", line);
	free(line);

	line = get_next_line(0);
	printf("%s", line);
	free(line);

	line = get_next_line(0);
	printf("%s", line);
	free(line);

	line = get_next_line(0);
	printf("%s", line);
	free(line);
	return (0);
}