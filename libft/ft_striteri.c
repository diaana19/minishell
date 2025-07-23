/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:56:01 by dirituay          #+#    #+#             */
/*   Updated: 2024/11/24 22:15:51 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i] != '\0')
	{
		(*f)(i, &s[i]);
		i++;
	}
}

/*void	print_char_with_index(unsigned int index, char *c) 
{
    printf("Index: %u, Character: %c\n", index, *c);
}

int	main(void)
{
	char	str[] = "Hello, world!";

	ft_striteri(str, print_char_with_index);
	return (0);
}*/
