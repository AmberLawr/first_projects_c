#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#include <limits.h>
#define FILE_PATH "./test"
char *get_next_line(int fd)
{
	static char	*buffer[MAX_FD];
	char		*line;
	char		*temporar;
	char		*joinedbuffer;
	int			bytesread;
	char		*ifn;
	int 		length;
	char		*newpart;
	char		*joinedline;
	line = 0;
	bytesread = 0;
	temporar = 0;
	joinedbuffer = 0;
	ifn = 0;
	length = 0;
	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE < 1)
		return (0);
	if (buffer[fd] == 0)
	{
		buffer[fd] = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer[fd])
			return (0);
		bytesread = read(fd, buffer[fd], BUFFER_SIZE);
		if (bytesread <= 0)
		{
			free(buffer[fd]);
			return (0);
		}
		buffer[fd][bytesread] = '\0';
	}
	else
	{
		if (buffer[fd][0] == '\0')
		{
			bytesread = read(fd, buffer[fd], BUFFER_SIZE);
			if (bytesread <= 0)
			{
				free(buffer[fd]);
				return (0);
			}
			buffer[fd][bytesread] = '\0';
		}
		else
		{
			temporar = ft_strdup(buffer[fd]);
			bytesread = read(fd, buffer[fd], BUFFER_SIZE);
			if (bytesread < 0)
			{
				free(buffer[fd]);
				free(temporar);
				return (0);
			}
			buffer[fd][bytesread] = '\0';
			joinedbuffer = ft_strjoin(temporar, buffer[fd]);
			free(buffer[fd]);
			free(temporar);
			buffer[fd] = joinedbuffer;
		}
	}
	ifn = ft_strchr(buffer[fd], '\n');
	if (ifn)
	{
		length = ifn - buffer[fd];
		line = ft_substr(buffer[fd], 0, length + 1);
		buffer[fd] = ft_memmove(buffer[fd], buffer[fd] + length + 1, ft_strlen(buffer[fd]) - length);
		return (line);
	}
	else
	{
		line = ft_strdup(buffer[fd]);
		buffer[fd][0] = '\0';
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
// int	main(void)
// {
//     int     fd;
//     char    *str;
//     fd = open("test.txt", O_RDONLY);
// 	while ((str = get_next_line(fd)))
// 	{
// 		printf("%s", str);
// 		free(str);
// 	}
// }
