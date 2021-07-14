#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include <limits.h>
#define TEST_TXT "test.txt"
#define BIG_LINE_NO_NL "big_line_no_nl"
#define FILE_PATH BIG_LINE_NO_NL

static char	*process_line(char **buf, int fd);
static int	initialise_buffer(char **buf, int fd);
static int	join_buffer(char **buf, int fd);
static char	*ft_strchr(const char *s, int c);

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

static char	*process_line(char **buf, int fd)
{
	char		*ifn;
	char		*line;
	char		*newpart;
	char		*joinedline;

	ifn = ft_strchr(*buf, '\n');
	if (ifn != NULL)
	{
		line = ft_substr(*buf, 0, (ifn - *buf) + 1);
		ft_memmove(*buf, *buf + (ifn - *buf) + 1,
			ft_strlen(*buf) - (ifn - *buf));
	}
	else
	{
		line = ft_strdup(*buf);
		**buf = '\0';
		newpart = get_next_line(fd);
		if (newpart == NULL)
			return (line);
		joinedline = ft_strjoin(line, newpart);
		free (line);
		free (newpart);
		line = joinedline;
	}
	return (line);
}

static int	initialise_buffer(char **buf, int fd)
{
	int			bytesread;

	bytesread = read(fd, *buf, BUFFER_SIZE);
	if (bytesread <= 0)
	{
		free(*buf);
		*buf = NULL;
		return (0);
	}
	else
		(*buf)[bytesread] = '\0';
	return (1);
}

static int	join_buffer(char **buf, int fd)
{
	char		*temporar;
	char		*joinedbuffer;
	int			bytesread;

	temporar = ft_strdup(*buf);
	bytesread = read(fd, *buf, BUFFER_SIZE);
	if (bytesread < 0)
	{
		free(*buf);
		free(temporar);
		return (0);
	}
	*(*buf + bytesread) = '\0';
	joinedbuffer = ft_strjoin(temporar, *buf);
	free(*buf);
	free(temporar);
	*buf = joinedbuffer;
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*buffer[MAX_FD];

	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE < 1)
		return (0);
	if (buffer[fd] == 0)
	{
		buffer[fd] = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (buffer[fd] == NULL || initialise_buffer(&buffer[fd], fd) == 0)
			return (0);
	}
	else
	{
		if (buffer[fd][0] == '\0')
		{
			if (initialise_buffer(&buffer[fd], fd) == 0)
				return (0);
		}
		else if (join_buffer(&buffer[fd], fd) == 0)
			return (0);
	}
	return (process_line(&buffer[fd], fd));
}
