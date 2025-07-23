/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:47:51 by dirituay          #+#    #+#             */
/*   Updated: 2024/11/15 14:18:25 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*temp;
	size_t	i;

	i = 0;
	temp = (char *)s;
	while (i < n)
	{
		temp[i] = 0;
		i++;
	}
}

/*int	main(void)
{
	char	buffer[20] = "holi, diana";
	int	i;

	i = 0;
	printf("antes de: %s\n", buffer);
	ft_bzero(buffer, 6);
	printf("despues de: ");
	while (i < 20)
	{
		printf("%c", buffer[i]);
		i++;
	}
	return (0);
}*/
