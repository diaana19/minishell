/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dianarituay <dianarituay@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:16:13 by dirituay          #+#    #+#             */
/*   Updated: 2024/11/21 21:45:03 by dianarituay      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	cc;
	size_t			i;

	str = (unsigned char *)s;
	cc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (str[i] == cc)
			return ((void *) &str[i]);
		i++;
	}
	return (NULL);
}

/*int	main(void)
{
	char	*s = "hola lolja";
	char	c = 'j';
	char	*result = ft_memchr(s, c, 4);
	
	printf("aparicion en: %s\n", result);
	printf("posicion: %ld", result - s);
	return (0);
}*/
