/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:41:01 by dirituay          #+#    #+#             */
/*   Updated: 2024/11/16 11:40:52 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	unsigned int	i;
	size_t			len;

	i = 0;
	len = ft_strlen(src);
	if (size != '\0')
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len);
}

/*int	main(void)
{
	char	src[] = "hola, diana";
	char	dest[20];
	int	copia_len;

	copia_len = ft_strlcpy(dest, src, 6);
	printf("%d\n", copia_len);
	printf("%s", dest);
	return (0);
}*/
