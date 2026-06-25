#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*tmp;
	ssize_t		bytes_read;
	char		buffer[BUFFER_SIZE + 1];

	if (!stash)
		stash = NULL;
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
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (stash);
}

#include <stdio.h>
int main(void)
{
	printf("%s", get_next_line(0));
	return (0);
}