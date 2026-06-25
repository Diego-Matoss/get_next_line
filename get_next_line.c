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

char	*ft_strjoin(char *s1, char *s2)
{
	char		*str;
	size_t		i;
	size_t		j;

	if (!s2)
		return (NULL);
	if (!s1)
		s1 = "";
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	return (str[i] = '\0', str);
}
char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (str[i])
	{
		if (str[i] == (char)c)
			return (&str[i]);
		i++;
	}
	if ((char)c == '\0')
		return (&str[i]);
	return (NULL);
}

#include <stdio.h>
char    *get_next_line(int fd)
{
	// static char *stash;
	char        *line;
	char		*tmp;
	ssize_t     bytes_read;
	char		buffer[BUFFER_SIZE + 1];

	line = NULL;
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(line);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		if (bytes_read == 0)
			break ;
		tmp = line;
		line = ft_strjoin(line, buffer);
		free(tmp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (line);
}

int main(void)
{
	printf("%s\n", get_next_line(0));
	return (0);
}