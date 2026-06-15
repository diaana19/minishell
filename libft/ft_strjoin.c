#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	dest = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!dest)
		return (NULL);
	while (s1[i] != '\0')
	{
		dest[j++] = s1[i++];
	}
	i = 0;
	while (s2[i] != '\0')
	{
		dest[j++] = s2[i++];
	}
	dest[j] = '\0';
	return (dest);
}