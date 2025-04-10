#ifndef BUFFER_SIZE
#	define BUFFER_SIZE 42
#endif

#include <unistd.h>
#include <stdlib.h>

char *str_chr (char *s, int c)
{
	while (*s) {
		if (*s == (char)c)
			return((char *)s);
		s++;
	}
	return (NULL);
}

int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

void  str_copy(char *s, char* d)
{
	while (*d)
		*s++ = *d++;
	*s = '\0';
}

char *ft_strdup(char *s)
{
	char *c = malloc(ft_strlen(s) + 1);
	str_copy(c, s);
	return(c);
}

char *ft_strjoin(char *s, char *d)
{
	if (!s || !d)
		return (NULL);
	char *ss = malloc(ft_strlen(s) + ft_strlen(d) + 1);
	if (!ss)
		return (NULL);
	str_copy(ss ,s);
	str_copy(ss + ft_strlen(s) ,d);
	free(s);
	return(ss);
}

char *get_next_line(int fd)
{
	static char buf[BUFFER_SIZE + 1]; //? A static buffer stores leftover content between calls.
	char *line; //? the line that will be returned
	char *new_line;
	int i;
	int j;

	line = ft_strdup(buf);

	//? read from the fd and append to the last str until we found a '\n' 
	while (!(new_line = str_chr(line, '\n')) && (i = read(fd, buf, BUFFER_SIZE))) 
	{
		buf[i] = '\0';
		line = ft_strjoin(line, buf);
	}

	//? if read return 0 ( i = 0 ) which mean we reach the EOF (for example in an empty line)
	if (ft_strlen(line) == 0)
		return(free(line), NULL);

	if (new_line != NULL) //? save characters after '\n' in a the buf (if we foun the '\n')
	{
		j = new_line - line + 1; //* j = 11 - 0 + 1 = 12 ( new_line = ptr to '\n') ( line ptr to the first char of str) ( + 1 of the '\n' => j = indix after '\n' )
		str_copy(buf, new_line + 1); //* copy chars that are after '\n' in the buf ( daba lbufer fih cheyata )
	}
	else //? when we found the last line in the fd whitout a '\n'.
	{  //? we calculate it's lenght and null terminate the buffer and we null terminate the last line . then we return it
		j = ft_strlen(line);
		buf[0] = '\0';
	}

	line[j] = '\0'; //* j = indix after '\n'
	return(line);
}
