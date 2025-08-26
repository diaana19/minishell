/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <dirituay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 13:53:14 by dirituay          #+#    #+#             */
/*   Updated: 2025/08/25 22:32:41 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// de str a int, marca error si str no es valido o muy grande
static int	ft_atoi2(char *str, int *error)
{
	int					i;
	int					j;
	int					sign;
	unsigned long long	result;

	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	j = i;
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10 + (str[i++] - '0');
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] || i - j > 20 || ((sign == -1 && (result - 1) > LONG_MAX)
			|| (sign == 1 && (result > LONG_MAX))))
		*error = 1;
	return ((int)((result * sign) % 256));
}

// maneja e imprime los errores
static void	handle_exit_error(t_data *data, char *arg, bool is_num_err)
{
	if (is_num_err)
	{
		ft_putstr_fd(STDERR_FILENO, "minishell: exit: ");
		ft_putstr_fd(STDERR_FILENO, &arg[0]);
		ft_putstr_fd(STDERR_FILENO, ": numeric argument required\n");
		data->exit_code = 2;
	}
	else
	{
		ft_putstr_fd(STDERR_FILENO, "minishell: exit: too many arguments\n");
		data->exit_code = 1;
	}
}

// termina el programa con exit code
void	ft_exit(t_data *data, char **args)
{
	int	code;
	int	error;

	code = 0;
	error = 0;
	if (args[1])
	{
		code = ft_atoi2(args[1], &error);
		if (error)
		{
			handle_exit_error(data, args[1], true);
			free_total(data, data->exit_code);
			return ;
		}
	}
	if (args[1] && args[2])
	{
		handle_exit_error(data, NULL, false);
		return ;
	}
	ft_putstr_fd(STDOUT_FILENO, "exit\n");
	if (!args[1])
		free_total(data, data->exit_code);
	free_total(data, code);
}
