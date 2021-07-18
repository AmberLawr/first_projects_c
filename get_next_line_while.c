#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"
#include <limits.h>
#define TEST_TXT "test.txt"
#define BIG_LINE_NO_NL "big_line_no_nl"
#define FILE_PATH BIG_LINE_NO_NL

char	*check_buffer(char **buffer, int fd);
void	checkline(char **buffer, char **line);
void	checknewline(char **buffer, char **line);

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
	char	*buffer;
	char	*line;
	int		bytesread;
	
	//1. read into buffer first time:
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof (char));
	bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread < 0)
			return (NULL);
	buffer[BUFFER_SIZE + 1] = '\0';
	while (bytesread > 0)
	{
		check_buffer(&buffer, fd);
		checkline(&buffer, &line);
	}
	if (bytesread == 0)
	{
		check_buffer(&buffer, fd);
		checkline(&buffer, &line);
		return (line);
	}
}

char	*check_buffer(char **buffer, int fd)
{
	int		bytesread;
	char	*temporar;
	char	*joinedbuf;

	if (buffer[0][0] == '\0')
	{
		bytesread = read(fd, *buffer, BUFFER_SIZE);
		*buffer[bytesread + 1] = '\0';
		return (*buffer);
	}
	else
	{
		temporar = ft_strdup(*buffer);
		bytesread = read(fd, *buffer, BUFFER_SIZE);
		joinedbuf = ft_strjoin(temporar, *buffer);
		return (joinedbuf);
	}
}

void checkline(char **buffer, char **line)
{
	char	*temporar;
	char	*joinedline;

	if (*line == NULL)
	{
		checknewline(line, buffer);
	}
	else if (*line != NULL)
	{
		temporar = ft_strdup(*line);

		checknewline(line, buffer);
		
		joinedline = ft_strjoin (temporar, *line);
		free (temporar);
		*line = joinedline;
	}
}

void checknewline(char **buffer, char **line)
{
	char	*ifn;
	int		length;

	ifn = ft_strchr(*buffer, '\n');
	length = ft_strlen(ifn);
	if (ifn != NULL)
	{
		*line = ft_substr(*buffer, 0, ifn - *buffer);
		ft_memmove(*buffer, ifn + 1, length + 1);
	}
	else
	{
		*line = ft_strdup(*buffer);
		*buffer[0] = '\0';
	}
}


int	main(void)
{
	int     fd;
	char	*result;

    fd = open("test.txt", O_RDONLY);
	result = get_next_line(fd);

	while (result != NULL)
	{
    	printf("%s\n", result);
		result = get_next_line(fd);
	}

}
