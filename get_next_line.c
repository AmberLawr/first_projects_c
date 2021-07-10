#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#define FILE_PATH "./test"



char *get_next_line(int fd);
{
	static char	*buffer;
	char		*line;
	char		*temporar
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

	if (buffer == 0)
	{
		buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		bytesread = read(fd, buffer, BUFFER_SIZE);
		buffer[bytesread] = '\0';
	}
	else
	{
		if (buffer[0] == '\0')
		{
			bytesread = read(fd, buffer, BUFFER_SIZE);
			buffer[bytesread] = '\0';
		}
		else
		{
			temporar = ft_strdup(buffer);
			bytesread = read(fd, buffer, BUFFER_SIZE);
			buffer[bytesread] = '\0';
			joinedbuffer = ft_strjoin(temporar, buffer);
			free(buffer);
			free(temporar);
			buffer = joinedbuffer;
		}
	}

	ifn = ft_memchr(buffer, '\n', BUFFER_SIZE)
	if (ifn != 0)
	{
		length = ifn - buffer;
		line = ft_substr(buffer, 0, length + 1);
		buffer = ft_memmove(buffer, buffer[length + 1], ft_strlen(buffer));
		return (line);
	}
	else
	{
		line = ft_strdup(buffer);
		buffer[0] = '\0';
		newpart = get_next_line(fd);
		joinedline = ft_strjoin(line, newpart);
		free (line);
		free (part);
		return (joinedline);
	}
  
  int	main(void)
{
    int     fd;
    char    *str;

    fd = open("test.txt", O_RDONLY);

	get_next_line(fd);

	while (get_next_line(fd, &str) >= 0)
	{
		printf("%s\n");
		free(str);
    	printf("%d\n", get_next_line(fd));
	}

}
