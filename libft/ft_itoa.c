#include "libft.h"

static int	ft_size(int n)
{
	int	i;

	i = 1;
	while (n > 9)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static int	ft_div(int size)
{
	int	div;
	int	i;

	div = 1;
	i = 0;
	while (i < size - 1)
	{
		div *= 10;
		i++;
	}
	return (div);
}

static	void	ft_num(int n, int size, char *str, int sign)
{
	int		div;
	int		i;

	i = 0;
	div = ft_div(size);
	if (sign == -1)
		str[i++] = '-';
	while (i < size && div > 9)
	{
		str[i] = ((n / div) % 10) + '0';
		n = n % div;
		div /= 10;
		i++;
	}
	str[i] = n % 10 + '0';
	str[i + 1] = '\0';
}

static void	ft_min_int(char *str, int n)
{
	int		div;
	int		i;

	i = 0;
	str[i] = '-';
	i++;
	div = ft_div(9);
	while (i < 13 && div > 9)
	{
		str[i] = ((n / div) % 10) + '0';
		n = n % div;
		div /= 10;
		i++;
	}
	str[i] = n % 10 + '0';
	str[i + 1] = 8 + '0';
	str[i + 2] = '\0';
}

char	*ft_itoa(int n)
{
	char	*str;
	int		sign;

	sign = 1;
	if (n == -2147483648)
	{
		str = (char *) malloc (sizeof(char) * (12));
		if (!str)
			return (NULL);
		ft_min_int(str, 214748364);
		return (str);
	}
	if (n < 0)
	{
		n *= -1;
		str = (char *) malloc(sizeof(char) * (ft_size(n) + 2));
		sign = -1;
	}
	else
		str = (char *) malloc (sizeof(char) * (ft_size(n) + 1));
	if (str == NULL)
		return (NULL);
	ft_num(n, ft_size(n), str, sign);
	return (str);
}