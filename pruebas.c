#include "get_next_line.h"

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

static char	*save_leftover(char *stash)
{
	char	*new_stash;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (stash[i])
	{
		i++;
		if (stash[i] == '\n')
			i++;
			break ;
	}
	new_stash = malloc(sizeof(char) * (ft_strlen(stash) - i));
	while (stash[i])
	{
		new_stash[j] = stash[i];
		j++;
		i++;
	}
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

#include <stdio.h>
int main(void)
{
    char *string;

    printf("%s", save_leftover(string));
    return (0);
}