#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#define FILE_PATH "./test"

int check_firsttime(int fd, char **buffer, char **line);
void read_substr(char **line, char **buffer, char *ifnewline);
void continue_read(char **line, char **buffer);

int	get_next_line(int fd, char **line)
{
	static char	*buffer = 0;
	char		*ifnewline;
	char		*temp;
	int			ifeof;
	int			length;

	if (buffer == 0)
		ifeof = check_firsttime(fd, &buffer, line);
	else
	{
		temp = ft_strdup(buffer);
		length = ft_strlen(buffer);
		free (buffer);
		buffer = (char *)malloc((BUFFER_SIZE + length + 1) * sizeof(char));
		ft_strlcpy(buffer, temp, length + 1);
		//strjoin new line untili '\n' with buffer and store it in line.
		ifeof = read(fd, buffer + length, BUFFER_SIZE);
		*(buffer + length + ifeof) = '\0';
	}
	if (ifeof == -1)
		return (-1);
	if (ifeof < BUFFER_SIZE) /*check if EOF is reached*/
	{
		ifnewline = ft_memchr_modified(buffer, '\n', BUFFER_SIZE);
		if (*ifnewline == '\n')
		{
			//substring new line and memmove buffer
			read_substr(line, &buffer, ifnewline);
			return (1);
		}
		else
		{
			continue_read(line, &buffer);
			return (0);
		}
	}
	if (ifeof == BUFFER_SIZE) /*when EOF is not reached*/
	{
		//printf("buffer: %s\n", buffer);
		length = ft_strlen(buffer);
		ifnewline = ft_memchr_modified(buffer, '\n', length);
		if (*ifnewline != '\n')
		{
			/*checks when there is no new line found, repeat the process*/
			//continue_read(line, &buffer);
			buffer[0] = '\0';
			return (get_next_line(fd, line));
		}
		else
		{
			/*if new line is found, read until newline and memmove the buffer to the beginning*/
			read_substr(line, &buffer, ifnewline);
			return (1);
		}
	}

	return (0);
}

int check_firsttime(int fd, char **buffer, char **line)
{
	char		*ifnewline;
	char		*temp2;
	int			ifeof;
	int			length;

	/*during the first run we check if there is a new line in the buffer;
	if so, we store only a part of the string into the line and
	use memmove to rearrange the rest of the string to the beginning of buffer*/

	*buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	ifeof = read(fd, *buffer, BUFFER_SIZE);
	(*buffer)[ifeof] = '\0';
	ifnewline = ft_memchr_modified(*buffer, '\n', BUFFER_SIZE);
	length = ifnewline - *buffer;
	if (*ifnewline == '\n')
	{
		temp2 = ft_substr(*buffer, 0, length);
		*line = temp2;
		*buffer = ft_memmove(*buffer, ifnewline + 1, (BUFFER_SIZE - length));
		return (ifeof);
	}
	*line = ft_strdup(*buffer);
	return (ifeof);
}

/* this function reads the part until '\n' is reached
1. join the old buffer (which is store in temp) with the line
2. join the above with the newly created substring*/
void read_substr(char **line, char **buffer, char *ifnewline)
{
	char	*temp_substr;
	char	*joined_nob;
	//char	*joined_withb;
	int		length;

	if (*line == 0)
	{
		*line = malloc(1);
		**line = '\0';
	}
	length = ifnewline - *buffer;
	temp_substr = ft_substr(*buffer, 0, length);
	joined_nob = ft_strjoin(*line, temp_substr);
	//joined_withb = ft_strjoin(joined_nob, temp_substr);
	free(temp_substr);
	free(*line);
	*line = joined_nob;
	*buffer = ft_memmove(*buffer, ifnewline + 1, (ft_strlen(*buffer) - length));
}

/* this function will be repeated to keep reading
1. join the line with temp
2. join the above with newly read buffer*/
void continue_read(char **line, char **buffer)
{
	char	*joined_nobuf;
	//char	*joined_complete;

	joined_nobuf = ft_strjoin(*line, *buffer);
	//joined_complete = ft_strjoin(joined_nobuf, *buffer);
	free(*line);
	//free(*temp);
	free(*buffer);
	*line = joined_nobuf;

}

int	main(void)
{
    int     fd;
    char    *str;

    fd = open("test.txt", O_RDONLY);

	str = 0;
	while (get_next_line(fd, &str) >= 0)
	{
		printf("%s\n", str);
		free(str);
		str = 0;
    	//printf("%d\n", get_next_line(fd, &str));
	}

}
