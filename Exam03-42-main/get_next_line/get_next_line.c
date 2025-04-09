#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
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

int slen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

void  str_cpy(char *s, char* d)
{
	while (*d)
		*s++ = *d++;
	*s = '\0';
}

char *str_dp(char *s)
{
	char *c = malloc(slen(s) + 1);
	str_cpy(c, s);
	return(c);
}
char *join(char *s, char *d)
{
	char *ss = malloc(slen(s) + slen(d) + 1);
	if (!s || !d)
		return (NULL);
	if (!ss)
		return (NULL);
	str_cpy(ss ,s);
	str_cpy(ss + slen(s) ,d);
	free(s);
	return(ss);
}

char *get_next_line(int fd)
{
	static char buf[BUFFER_SIZE + 1];
	char *line;
	char *nline;
	int i;
	int j;

	line = str_dp(buf);
	while (!(nline = str_chr(line, '\n')) &&(i = read(fd, buf, BUFFER_SIZE))) {
		buf[i] = '\0';
		line = join(line, buf);
	}
	if (slen(line) == 0)
		return(free(line), NULL);
	if (nline != NULL) {
		j = nline - line + 1;
		str_cpy(buf, nline + 1);
	}
	else {
		j = slen(line);
		buf[0] = '\0';
	}
	line[j] = '\0';
	return(line);
}