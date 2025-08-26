/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:52:29 by dirituay          #+#    #+#             */
/*   Updated: 2025/08/25 21:24:38 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// verifica si el string es un -n valido(1) o no(0)

static int	check_n(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] == '\0')
		return (0);
	i = 1;
	while (str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

// verifica todos los -n e imprime el resto de args
static void	write_echo(int count, int i, bool new_line, char *args[])
{
	while (args[i] && check_n(args[i]))
	{
		i++;
		new_line = false;
	}
	while (i < count)
	{
		write(1, args[i], ft_strlen(args[i]));
		if (i != count - 1)
			write(1, " ", 1);
		i++;
	}
	if (new_line)
		write(1, "\n", 1);
}

// cuenta los args y llama a write_echo
int	ft_echo(char **args)
{
	int		count;
	int		i;
	bool	new_line;

	count = 0;
	while (args[count])
		count++;
	i = 1;
	new_line = true;
	write_echo(count, i, new_line, args);
	return (0);
}
