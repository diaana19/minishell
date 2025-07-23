/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dianarituay <dianarituay@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:01:16 by dirituay          #+#    #+#             */
/*   Updated: 2024/11/21 21:45:38 by dianarituay      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*temp;
	size_t			i;

	i = 0;
	temp = (unsigned char *)b;
	while (i < len)
	{
		temp[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

/*int	main(void)
{
	char	buffer[20] = "holi, diana";
	
	ft_memset(buffer, '*', 4);
	printf("%s\n", buffer);
	memset(buffer, '!', 4);
	printf("%s", buffer);
	return (0);
}*/
