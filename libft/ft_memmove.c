#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*temp1;
	char	*temp2;
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	temp1 = (char *)dest;
	temp2 = (char *)src;
	if (temp1 > temp2)
	{
		while (n-- > 0)
			temp1[n] = temp2[n];
	}
	else
	{
		while (i < n)
		{
			temp1[i] = temp2[i];
			i++;
		}
	}
	return (dest);
}