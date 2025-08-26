/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 17:42:53 by dirituay          #+#    #+#             */
/*   Updated: 2025/08/25 21:24:53 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// muestra la ruta completa del directorio actual
int	ft_pwd(char **av)
{
	char	buf[PATH_MAX];
	int		ac;

	ac = 0;
	while (av && av[ac])
		ac++;
	if (ac > 1)
	{
		ft_putstr_fd(2, "minishell: pwd: no options allowed\n");
		return (2);
	}
	if (getcwd(buf, PATH_MAX))
	{
		printf("%s\n", buf);
		return (0);
	}
	return (1);
}
