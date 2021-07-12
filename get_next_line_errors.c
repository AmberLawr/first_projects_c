#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include <limits.h>
#define FILE_PATH "./test"

char	*initialise_buffers(char **currentbuffer, int fd);
char	*process_buffers(char **currentbuffer, int fd);
char	*process_line(char **currentbuffer, int fd);


char *get_next_line(int fd)
{
	static char	*buffers[MAX_FD];
	char		*temporar;
	char		**currrentbuffer;
	int			bytesread;
	int 		length;
	char		*line;

	temporar = NULL;
	bytesread = 0;
	length = 0;
	line = NULL;
	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE < 1)
		return (0);
	currrentbuffer = &buffers[fd];
	initialise_buffers(currrentbuffer, fd);
	process_buffers(currrentbuffer, fd);
	line = process_line(currrentbuffer, fd);
	return (line);
}

char	*initialise_buffers(char **currentbuffer, int fd)
{
	int			bytesread;

	currentbuffer = NULL;
	bytesread = 0;
	bytesread = read(fd, currentbuffer, BUFFER_SIZE);
	if (bytesread < 0)
	{
		free(currentbuffer);
		currentbuffer = NULL;
		return (0);
	}
	*currentbuffer[bytesread] = '\0';
	return (*currentbuffer);
}

char	*process_buffers(char **currentbuffer, int fd)
{
	char		*temporar;
	int			bytesread;
	char		*joinedbuffers;

	temporar = 0;
	bytesread = 0;
	joinedbuffers = 0;
	if (currentbuffer == NULL)
	{
		currentbuffer = (char **)malloc((BUFFER_SIZE + 1) * sizeof(char*));
		if (!currentbuffer)
			return (0);
		*currentbuffer = initialise_buffers(currentbuffer, fd);
	}
	else
	{
		if (currentbuffer[0] == '\0')
		{
		*currentbuffer = initialise_buffers(currentbuffer, fd);
		}
		else
		{
			temporar = ft_strdup(*currentbuffer);
			bytesread = read(fd, currentbuffer, BUFFER_SIZE);
			if (bytesread < 0)
			{
				free(currentbuffer);
				currentbuffer = NULL;
				free(temporar);
				return (0);
			}
			*currentbuffer[bytesread] = '\0';
			joinedbuffers = ft_strjoin(temporar, *currentbuffer);
			free(currentbuffer);
			free(temporar);
			*currentbuffer = joinedbuffers;
		}
	}
	return (*currentbuffer);
}

char	*process_line(char **currentbuffer, int fd)
{
	char		*ifn;
	int 		length;
	char		*newpart;
	char		*joinedline;
	char		*line;

	ifn = 0;
	length = 0;
	newpart = 0;
	joinedline = 0;
	line = 0;

	ifn = ft_strchr(*currentbuffer, '\n');
	if (ifn)
	{
		length = ifn - *currentbuffer;
		line = ft_substr(*currentbuffer, 0, length + 1);
		*currentbuffer = ft_memmove(*currentbuffer, *currentbuffer + length + 1,
			ft_strlen(*currentbuffer) - length);
		return (line);
	}
	else
	{
		line = ft_strdup(*currentbuffer);
		*currentbuffer[0] = '\0';
		newpart = get_next_line(fd);
		if (!newpart)
			return (line);
		joinedline = ft_strjoin(line, newpart);
		free (line);
		free (newpart);
		line = joinedline;
		return (line);
	}
}

int	main(void)
{
	int     fd;
	char    *str;

	fd = open("test.txt", O_RDONLY);

	while ((str = get_next_line(fd)))
	{
		printf("%s", str);
		free(str);
	}
}
