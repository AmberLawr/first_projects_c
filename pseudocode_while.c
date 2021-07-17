#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include <limits.h>
#define TEST_TXT "test.txt"
#define BIG_LINE_NO_NL "big_line_no_nl"
#define FILE_PATH BIG_LINE_NO_NL

static char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c)
		return ((char *)0);
	return ((char *)s);
}

char *get_next_line(int fd)
{
	/*
	0. variables definition

	1. read into buffer first time:
	buffer = (char)malloc((BUFFER_SIZE + 1) * sizeof (char));
	bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread == -1)
			return (-1);
	buffer[BUFFER_SIZE + 1] = '\0';

	2. while (bytesread > 0 && strchr() == NULL)
	{
		check_buffer();
		joinline();
	}

	3. if (strchr() != NULL || bytesread == 0)
	{
		check_buffer();
		substringline();
		return (line);
	}

	*/
}

/*
check_buffer()
{
	if (buffer == filled)
	{
		if (buffer[0] == '\0)
		{
			buffer = (char)malloc((BUFFER_SIZE + 1) * sizeof (char));
			bytesread = read(fd, buffer, BUFFER_SIZE);
			buffer[bytesread + 1] = '\0';
			return (buffer);
		}
		else
		{
			temporar = ft_strdup(buffer);
			buffer = (char)malloc((BUFFER_SIZE + 1) * sizeof (char));
			bytesread = read(fd, buffer, BUFFER_SIZE);
			joinedbuf = ft_strjoin(temporar, buffer);
			return (joinedbuf);
		}

	}
	else
	{
		buffer = (char)malloc((BUFFER_SIZE + 1) * sizeof (char));
		bytesread = read(fd, buffer, BUFFER_SIZE);
		buffer[bytesread + 1] = '\0';
		return (buffer);
	}
}
*/


/*
joinline()
{
	if (line == filled)
	{
		temporar = ft_strdup(line);
		joinedline = ft_strjoin(temporar, buffer);
		free line;
		free buffer;
		line = joinedline;
		return (line);

	}
	else if (line == NULL)
	{
		line = ft_strdup(buffer);
		free buffer;
		return (line);
	}
*/


/*
substringline()
{
	newline = ft_strdup(line);
	tempbuf = ft_substr(buffer, 0, length);
	free buffer;
	free line;
	line = ft_strjoin(newline, tempbuf);
	return (line);
}
*/
