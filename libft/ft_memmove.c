/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:27:57 by dirituay          #+#    #+#             */
/*   Updated: 2024/11/23 17:34:18 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
/*#include <string.h>
int	main(void)
{
	char	buffer1[40] = "holitas";
	char	buffer2[40] = "holitas";

	ft_memmove(buffer1 + 2, buffer1, 9);
	printf("%s\n", buffer1);
	memmove(buffer2 + 2, buffer2, 9);
	printf("%s", buffer2);
	return (0);
}*/
