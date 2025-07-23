/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirituay <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 15:54:25 by dirituay          #+#    #+#             */
/*   Updated: 2024/11/24 21:38:24 by dirituay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_malloc(char **str, int i)
{
	while (i--)
	{
		if (str[i])
		{
			free(str[i]);
			str[i] = (NULL);
		}
	}
	free(str);
	return (NULL);
}

static int	count_subs(char const *s, char c, int start)
{
	int	subs;

	subs = 0;
	while (s[start] != '\0' && s[start] != c)
	{
		start++;
		subs++;
	}
	return (subs);
}

static int	ft_check_deli(char s, char c)
{
	if (c == s)
		return (1);
	if (s == '\0')
		return (1);
	return (0);
}

static char	**ft_copy(char **str, char c, int words, const char *s)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	j = 0;
	while (i < words)
	{
		if (ft_check_deli(s[j], c) == 1)
			j++;
		else
		{
			x = 0;
			str[i] = (char *)malloc((count_subs(s, c, j) + 1) * sizeof(char));
			if (!str[i])
				return (ft_malloc(str, i));
			while (s[j] != '\0' && ft_check_deli(s[j], c) == 0)
				str[i][x++] = s[j++];
			str[i][x] = '\0';
			i++;
		}
	}
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**subs;
	int		words;
	int		i;

	i = 0;
	words = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if (ft_check_deli(s[i], c) == 0 && ft_check_deli(s[i + 1], c) == 1)
			words++;
		i++;
	}
	subs = (char **)malloc((words + 1) * sizeof(char *));
	if (subs == NULL)
		return (NULL);
	if (!ft_copy(subs, c, words, s))
		return (NULL);
	subs[words] = 0;
	return (subs);
}

/*int	main(void)
{
	char	*str = "     hola   bola       cola        ";
	char	deli = ' ';
	char	**result;
	int	i = 0;

	result = ft_split(str, deli);
	while (result[i] != NULL)
	{
		printf("subcadena: %d : %s\n", i + 1, result[i]);
		free(result[i]);
		i++;
	}
	free(result);
	return (0);
}*/
