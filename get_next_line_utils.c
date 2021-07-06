#include <stdlib.h>
#include "get_next_line.h"

char	*ft_strdup(const char *s)
{
	int		index;
	int		length;
	char	*target;

	index = 0;
	length = ft_strlen(s);
	target = (char *)malloc((length + 1) * sizeof(char));
	if (target == 0)
		return (0);
	while (index < length)
	{
		target[index] = s[index];
		index++;
	}
	target[index] = '\0';
	return (target);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	index;
	char	*sub;

	index = 0;
	if (s == 0)
		return (0);
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (sub == 0)
		return (0);
	if (start >= ft_strlen(s))
	{
		sub[0] = '\0';
		return (sub);
	}
	while (index < len)
	{
		sub[index] = s[start + index];
		index++;
	}
	sub[index] = '\0';
	return (sub);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*csrc;
	unsigned char	*cdest;
	size_t			count;

	count = 0;
	csrc = (unsigned char *)src;
	cdest = (unsigned char *)dst;
	if ((cdest == 0) && (csrc == 0))
		return (0);
	if (csrc < cdest)
	{
		while (len > 0)
		{
			cdest[len - 1] = csrc[len - 1];
			len--;
		}
	}
	else
		ft_memcpy(cdest, csrc, len);
	return (dst);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	index;
	size_t	jindex;
	size_t	length;
	char	*newstr;

	if (s1 == 0 || s2 == 0)
		return (0);
	index = 0;
	jindex = 0;
	length = ft_strlen(s1) + ft_strlen(s2);
	newstr = (char *)malloc((length + 1) * sizeof(char));
	if (newstr == 0)
		return (0);
	while (s1[index] != '\0' && s1[index] != '\n')
	{
		newstr[index] = s1[index];
		index++;
	}
	while (s2[jindex] != '\0' && s2[index] != '\n')
	{
		newstr[index + jindex] = s2[jindex];
		jindex++;
	}
	newstr[index + jindex] = '\0';
	return (newstr);
}

size_t	ft_strlen(const char *s)
{
	int	index;

	index = 0;
	while (s[index] != '\0')
	{
		index++;
	}
	return (index);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*csrc;
	unsigned char	*cdest;
	size_t			index;

	index = 0;
	csrc = (unsigned char *)src;
	cdest = (unsigned char *)dst;
	if ((dst == 0) && (src == 0))
		return (0);
	while (index < n)
	{
		cdest[index] = csrc[index];
		index++;
	}
	return (cdest);
}

void	*ft_memchr_modified(const void *s, int c, size_t n)
{
	unsigned char	*s1;
	unsigned char	c1;
	size_t			index;

	s1 = (unsigned char *)s;
	c1 = (unsigned char)c;
	index = 0;
	while (index < n)
	{
		if (s1[index] == c1)
			return (&s1[index]);
		index++;
	}
	return (s1 + index);
}
