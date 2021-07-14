#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# define MAX_FD 5050

char	*get_next_line(int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_memmove(void *dst, const void *src, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);

#endif
