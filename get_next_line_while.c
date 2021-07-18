#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "get_next_line.h"
#include <limits.h>
#define TEST_TXT "test.txt"
#define BIG_LINE_NO_NL "big_line_no_nl"
#define FILE_PATH BIG_LINE_NO_NL

int 	check_buffer(char **buffer, int fd);
int		checkline(char **buffer, char **line);
int		checknewline(char **buffer, char **line);

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
	static char *buffer;
	char	    *line;
	int		    bytesread;

	//1. read into buffer first time:
	if (!buffer)
    {
        buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof (char));
        bytesread = read(fd, buffer, BUFFER_SIZE);
        if (bytesread < 0)
            return (NULL);
        buffer[bytesread] = '\0';
    }
	line = NULL;
	while (1)
	{
		if (!check_buffer(&buffer, fd))
            break ;
		if (checkline(&buffer, &line))
            break ;
        if (line && *line == '\0')
        {
            return (NULL);
        }
	}
	if (line)
        return (line);
    return (NULL);
}

int    check_buffer(char **buffer, int fd)
{
	int		bytesread;
	char	*temporar;
	char	*joinedbuf;

	if (buffer[0][0] == '\0')
	{
		bytesread = read(fd, *buffer, BUFFER_SIZE);
		if (!bytesread)
			return (0);
		(*buffer)[bytesread] = '\0';
	}
	else
	{
		temporar = ft_strdup(*buffer); // temporar and buffer
		bytesread = read(fd, *buffer, BUFFER_SIZE);
		(*buffer)[bytesread] = '\0';
		joinedbuf = ft_strjoin(temporar, *buffer); // joinedbuf and temporar and buffer
		free(temporar);
		free(*buffer);
		*buffer = joinedbuf;
	}
	return (1);
}

int checkline(char **buffer, char **line)
{
	char	*temporar;
	char	*joinedline;
	int     readsuccess;

	if (*line == NULL)
		readsuccess = checknewline(buffer, line);
	else if (*line != NULL)
	{
		temporar = ft_strdup(*line);
		readsuccess = checknewline(buffer, line);
		joinedline = ft_strjoin(temporar, *line);
		free(temporar);
		free(*line);
		*line = joinedline;
	}
	return (readsuccess);
}

int checknewline(char **buffer, char **line)
{
	char	*ifn;

	ifn = ft_strchr(*buffer, '\n');
	if (ifn != NULL)
	{
		*line = ft_substr(*buffer, 0, ifn - *buffer + 1);
		ft_memmove(*buffer, ifn + 1, ft_strlen(ifn + 1) + 1);
		return (1);
	}
	else
	{
		*line = ft_strdup(*buffer);
		(*buffer)[0] = '\0';
		return (0);
	}
}

// int	main(void)
// {
// 	int     fd;
// 	char	*result;

//     fd = open("test.txt", O_RDONLY);
// 	result = get_next_line(fd);

// 	while (result != NULL)
// 	{
//     	printf("%s\n", result);
// 		result = get_next_line(fd);
// 	}
// }
