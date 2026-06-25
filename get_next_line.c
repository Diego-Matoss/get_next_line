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

char	*get_next_line(int fd)
{
	static char	*stash;

	if (!stash)
		stash = NULL;
	stash = fill_stash(fd, stash);
	return (stash);
}

#include <stdio.h>
int main(void)
{
	char	*linea;
	char	*linea2;
	linea = get_next_line(0);
	printf("%s", linea);
	free(linea);
	linea2 = get_next_line(0);
	printf("%s", linea2);
	return (0);
}