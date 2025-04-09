//get_next_line utils ==========================================================
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

#ifndef BUFFER_SIZE
#	define BUFFER_SIZE 42
#endif
size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, char c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	i;

	i = 0;
	s2 = malloc(ft_strlen(s1) + 1);
	if (!s2)
		return (NULL);
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = 0;
	return (s2);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	while (i < len)
		str[i++] = s[start++];
	str[i] = 0;
	return (str);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s2)
		return (ft_strdup(s1));
	if (!s1)
		return (ft_strdup(s2));
	i = 0;
	j = 0;
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
	{
		free((char *)s1);
		return (NULL);
	}
	while (s1[i])
		str[i++] = s1[j++];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = 0;
	free((char *)s1);
	return (str);
}

static char	*final_line(char **line_buffer)
{
	char	*leftover_data;
	char	*clean_line;
	ssize_t	i;

	i = 0;
	while ((*line_buffer)[i] != '\n' && (*line_buffer)[i] != '\0')
		i++;
	if ((*line_buffer)[i] == 0 || (*line_buffer)[1] == 0)
		return (NULL);
	leftover_data = ft_substr(*line_buffer, i + 1, ft_strlen(*line_buffer) - i);
	if (leftover_data && !*leftover_data)
	{
		free(leftover_data);
		leftover_data = NULL;
	}
	clean_line = ft_substr(*line_buffer, 0, i + 1);
	free(*line_buffer);
	*line_buffer = clean_line;
	return (leftover_data);
}

static char	*catch_the_newline(int fd, char *static_buf, char *buffer)
{
	ssize_t	bytes_read;

	bytes_read = 1;
	while (bytes_read)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(static_buf);
			return (NULL);
		}
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = 0;
		static_buf = ft_strjoin(static_buf, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (static_buf);
}

char	*get_next_line(int fd)
{
	static char	*static_buf;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE > INT_MAX)
	{
		free(static_buf);
		static_buf = NULL;
		return (NULL);
	}
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	line = catch_the_newline(fd, static_buf, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	static_buf = final_line(&line);
	if (!line)
		return (free(static_buf), NULL);
	return (line);
}

// get_next_line mandatory =====================================================

