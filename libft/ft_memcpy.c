/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:20:18 by dirituay          #+#    #+#             */
/*   Updated: 2024/11/22 18:44:19 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*temp1;
	unsigned char	*temp2;
	size_t			i;

	i = 0;
	if (dest == (void *)0 && src == (void *)0)
		return (dest);
	temp1 = (unsigned char *)dest;
	temp2 = (unsigned char *)src;
	while (i < n)
	{
		temp1[i] = temp2[i];
		i++;
	}
	return (dest);
}

/*int	main(void)
{
	char	*src;
	char	dest[20];

	src = "hola, diana";
	ft_memcpy(dest, src, 20);
	printf("%s", dest);
	return (0);
}*/	
