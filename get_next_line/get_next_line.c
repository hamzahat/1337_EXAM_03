// #include <stdlib.h> // malloc | free 
// #include <unistd.h> // read fun
//
// char	*get_next_line(int fd)
// {
// 	return ();
// }
//


// #include <stdlib.h> // malloc | free
// #include <unistd.h> // read

// char	*get_next_line(int fd)
// {
	
// }

#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

static int	ft_strlen(char *s)
{
	int i = 0;
	while (s && s[i])
		i++;
	return (i);
}

static char	*ft_strchr(char *s, int c)
{
	int i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == (char)c)
			return (&s[i]);
		i++;
	}
	if (c == 0)
		return (&s[i]);
	return (0);
}

static char	*ft_strjoin(char *s1, char *s2)
{
	int i = 0, j = 0;
	char *new = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new)
		return (0);
	while (s1 && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
		new[i++] = s2[j++];
	new[i] = 0;
	free(s1);
	return (new);
}

static char	*get_line(char *stash)
{
	int i = 0;
	char *line;

	if (!stash || !stash[0])
		return (0);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (0);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i++] = '\n';
	line[i] = 0;
	return (line);
}

static char	*get_rest(char *stash)
{
	int i = 0, j = 0;
	char *rest;

	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (0);
	}
	rest = malloc(ft_strlen(stash) - i + 1);
	if (!rest)
		return (0);
	i++;
	while (stash[i])
		rest[j++] = stash[i++];
	rest[j] = 0;
	free(stash);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char *stash;
	char buffer[BUFFER_SIZE + 1];
	int bytes;
	char *line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	bytes = 1;
	while (!ft_strchr(stash, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(stash);
			stash = 0;
			return (0);
		}
		buffer[bytes] = 0;
		stash = ft_strjoin(stash, buffer);
	}
	line = get_line(stash);
	stash = get_rest(stash);
	return (line);
}

//! pased in the gradmeme test!