/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 20:51:20 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/03 16:58:36 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	split_len(char *s, char c)
{
	char			*str;
	unsigned long	i;

	if (!*s)
		return (0);
	str = s;
	i = 0;
	if (*str == c)
		i = -1;
	while (*str)
	{
		if (*str == c)
		{
			while (*str == c)
				str++;
			if (*str)
				i++;
		}
		str++;
	}
	return (i + 1);
}

static size_t	word_len(char *str, char c)
{
	size_t	i;

	i = 0;
	while (*str != c && *str)
	{
		i++;
		str++;
	}
	return (i);
}

static void	*fill_array(char const *str, char c, char **arr)
{
	size_t			str_len;
	size_t			i;

	i = 0;
	while (*str)
	{
		while (*str == c && *str)
			str++;
		if (*str != c && *str)
		{
			str_len = word_len((char *)str, c);
			arr[i] = ft_strsub(str, 0, str_len);
			if (!arr[i])
				return (NULL);
			str += str_len;
			i++;
		}
	}
	arr[i] = NULL;
	return (arr);
}

/*
** Allocates (with malloc(3)) and returns an array of “fresh”
** strings (all ending with ’\0’, including last array elem)
** obtained by spliting s using the character c as a delimiter.
** If the allocation fails the function returns NULL.
*/

char	**ft_strsplit(char const *str, char c)
{
	char			**arr;
	void			*ret;

	if (!str || *str == '\0')
		return (NULL);
	arr = (char **)ft_calloc(sizeof(char *) * (split_len((char *)str, c) + 1));
	if (!arr)
		return (NULL);
	ret = fill_array(str, c, arr);
	if (!ret)
		return (NULL);
	return (arr);
}
