/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:00:52 by dirituay          #+#    #+#             */
/*   Updated: 2024/11/24 22:14:54 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			cc;

	i = 0;
	cc = (char)c;
	while (s[i] != '\0')
	{
		if (s[i] == cc)
		{
			return ((char *) &s[i]);
		}
		i++;
	}
	if (cc == '\0')
	{
		return ((char *) &s[i]);
	}
	return (NULL);
}

/*int	main(void)
{
	char	*s = "hola lola";
	char	c = 'o';
	char	*result = ft_strchr(s, c);
	
	printf("ocurrencia en: %s\n", result);
	printf("posicion en: %ld", result - s);
	return (0);
}*/
