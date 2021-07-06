#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "get_next_line.h"
#define FILE_PATH "./test"

void check_firsttime(int fd, char **buffer, char **line);
void read_substr(char **line, char **buffer, char *ifnewline, char **temp);
void read_tiln(char **line, char **buffer, char **temp);

int	get_next_line(int fd, char **line)
{
	static char	*buffer = 0;
	char		*ifnewline;
	char		*temp;
	int			ifeof;

	if (buffer == 0)
		check_firsttime(fd, &buffer, line);
	else
	{
		if (ft_strlen(buffer) != 0)
			temp = ft_strdup(buffer);
		ifeof = read(fd, buffer, BUFFER_SIZE);
		if (ifeof == -1)
			return (-1);
		if (ifeof <= BUFFER_SIZE)
		{
			ifnewline = ft_memchr_modified(buffer, '\n', BUFFER_SIZE);
			if (ifnewline == (buffer + BUFFER_SIZE))
				ifeof = 1;
			else
			{
				read_substr(line, &buffer, ifnewline, &temp);
				return (0);
			}
		}
		if (ifeof == BUFFER_SIZE)
		{
			ifnewline = ft_memchr_modified(buffer, '\n', BUFFER_SIZE);
			if (ifnewline == (buffer + BUFFER_SIZE))
			{
				/*checks when there is no new line found, repeat the process*/
				read_tiln(line, &buffer, &temp);
				return (get_next_line(fd, line));
			}
			else
			{
				/*if new line is found, read until newline and memmove the buffer to the beginning*/
				read_substr(line, &buffer, ifnewline, &temp);
				return (1);
			}
		}
	}
	return (-1);
}

void check_firsttime(int fd, char **buffer, char **line)
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
		return ;
	}
	*line = ft_strdup(*buffer);

}

/* this function reads the part until '\n' is reached
1. */
void read_substr(char **line, char **buffer, char *ifnewline, char **temp)
{
	char	*temp_substr;
	char	*joined_nob;
	char	*joined_withb;
	int		length;

	length = ifnewline - *buffer;
	temp_substr = ft_substr(*buffer, 0, length);
	joined_nob = ft_strjoin(*temp, *line);
	joined_withb = ft_strjoin(joined_nob, temp_substr);
	free(temp_substr);
	free(*line);
	*line = joined_withb;
	*buffer = ft_memmove(*buffer, ifnewline + 1, (BUFFER_SIZE - length));
}

/* this function will be repeated to keep reading
1. join the line with temp
2. join the above with newly read buffer*/
void read_tiln(char **line, char **buffer, char **temp)
{
	char	*joined_nobuf;
	char	*joined_complete;

	joined_nobuf = ft_strjoin(*line, *temp);
	joined_complete = ft_strjoin(joined_nobuf, *buffer);
	free(*line);
	free(*temp);
	free(buffer);
	*line = joined_complete;

}

int	main(void)
{
    int     fd;
    char    *str;

    fd = open("test.txt", O_RDONLY);

	get_next_line(fd, &str);

	while (get_next_line(fd, &str) >= 0)
	{
		printf("%s\n", str);
		free(str);
    	printf("%d\n", get_next_line(fd, &str));
	}

}
