/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:38:54 by dirituay          #+#    #+#             */
/*   Updated: 2024/11/16 15:59:37 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	slen;
	size_t	dlen;
	size_t	i;

	i = 0;
	slen = ft_strlen(src);
	dlen = ft_strlen(dst);
	if (size == 0)
		return (slen);
	if (dlen >= size)
		return (slen + size);
	while (src[i] != '\0' && dlen + i < size - 1)
	{
		dst[dlen + i] = src[i];
		i++;
	}
	dst[dlen + i] = '\0';
	return (dlen + slen);
}

/*int	main(void)
{
	char dest[20] = "hola ";
	char src[] = "amigos";
	size_t	result = ft_strlcat(dest, src, 3);
	printf("%zu\n", result);
	printf("%s", dest);	
	return (0);
}*/
