/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dianarituay <dianarituay@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 21:10:57 by dianarituay       #+#    #+#             */
/*   Updated: 2024/11/14 21:21:18 by dianarituay      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		return (c - 32);
	}
	return (c);
}

//int	main(void)
//{
	//int	a;

	//a = 'v';
	//printf("%c", ft_toupper(a));
	//return (0);
//}