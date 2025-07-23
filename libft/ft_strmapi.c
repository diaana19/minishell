/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dianarituay <dianarituay@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 15:34:19 by dirituay          #+#    #+#             */
/*   Updated: 2024/11/22 18:28:01 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*dest;

	i = 0;
	if (!s)
		return (NULL);
	dest = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	while (i < ft_strlen(s))
	{
		dest[i] = (*f)(i, s[i]);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/*char	ft_upper(unsigned int index, char c)
{
	if (index % 2 != 0 && c >= 'a' && c <= 'z')
		return (c - 'a' + 'A');
	return (c);
}

int	main(void)
{
	char	*s = "hola mundo";
	char	*result = ft_strmapi(s, ft_upper);

	if (!result)
		return (1);
	printf("%s", result);
	free(result);
	return (0);	
}*/
