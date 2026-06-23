#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define BUFFER_SIZE 1


size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*destination;
	unsigned char	*source;
	size_t			i;

	if (!dest && !src)
		return (NULL);
	destination = (unsigned char *)dest;
	source = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		destination[i] = source[i];
		i++;
	}
	return (destination);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char		*str;
	size_t		str_len;
	size_t		s1_len;
	size_t		s2_len;

	if (!s2 || !s1)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str_len = s1_len + s2_len;
	str = malloc(str_len + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, s1_len);
	ft_memcpy(str + s1_len, s2, s2_len + 1);
	return (str);
}
int ft_strchr(char *str, char c, ssize_t bytes_read)
{
	ssize_t	i;

	if (!str)
		return (0);
	i = 0;
	while (i < bytes_read)
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

#include <stdio.h>
char    *get_next_line(int fd)
{
	// static char *stash;
	char        *line;
	ssize_t     bytes_read;
	char		buffer[BUFFER_SIZE + 1];

	line = "";
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	buffer[BUFFER_SIZE] = '\0';
	while (bytes_read > 0 && !ft_strchr(buffer, '\n', bytes_read))
	{
		line = ft_strjoin(line, buffer);
		// printf("%s\n", line);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[BUFFER_SIZE] = '\0';
	}
	return (line);
}

int main(void)
{
	printf("%s\n", get_next_line(0));
	printf("%s\n", get_next_line(0));
	printf("%s\n", get_next_line(0));
	return (0);
}