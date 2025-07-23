/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:28:01 by dirituay          #+#    #+#             */
/*   Updated: 2024/11/24 22:16:28 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned int	i;
	char			cc;
	char			*pc;

	i = 0;
	cc = (char)c;
	pc = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == cc)
			pc = ((char *) &s[i]);
		i++;
	}
	if (cc == '\0')
		return ((char *) &s[i]);
	return (pc);
}

/*int	main(void)
{
	char	*s = "hola lola";
	char	c = 'l';
	char	*result = ft_strrchr(s, c);

	printf("ocurrencia en: %s\n", result);
	printf("posicion en : %ld", result - s);
	return (0);
}*/
