#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	char			cc;
	char			*pc;

	i = 0;
	cc = (char)c;
	pc = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == cc)
			pc = ((char *) &s[i]);
		i++;
	}
	if (cc == '\0')
		return ((char *) &s[i]);
	return (pc);
}