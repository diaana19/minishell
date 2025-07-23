/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 19:33:04 by dirituay          #+#    #+#             */
/*   Updated: 2024/11/22 18:17:25 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size && nmemb > (__SIZE_MAX__ / size))
		return (NULL);
	ptr = (void *)malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

/*int	main(void)
{
	int *arr = ft_calloc(5, sizeof(int));
	printf("arr[0] = %d\n", arr[0]);
	printf("arr[1] = %d\n", arr[1]);
	printf("arr[2] = %d\n", arr[2]);
	printf("arr[3] = %d\n", arr[3]);
	printf("arr[4] = %d\n", arr[4]);
	free(arr);
}*/
