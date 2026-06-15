#include "libft.h"

static size_t	trim_start(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && ft_strchr(set, s1[i]))
		i++;
	return (i);
}

static size_t	trim_end(char const *s1, char const *set, size_t start)
{
	size_t	i;

	i = ft_strlen(s1) - 1;
	while (i >= start && ft_strchr(set, s1[i]))
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	len;
	size_t	start;
	size_t	end;
	char	*new_s1;

	if (!s1 || !set)
		return (NULL);
	start = trim_start(s1, set);
	end = trim_end(s1, set, start);
	len = end - start + 1;
	while (len <= 0 || start >= ft_strlen(s1))
		return (ft_strdup(""));
	i = 0;
	new_s1 = (char *)malloc(len + 1);
	if (!new_s1)
		return (NULL);
	while (i < len)
	{
		new_s1[i] = s1[start + i];
		i++;
	}
	new_s1[len] = '\0';
	return (new_s1);
}