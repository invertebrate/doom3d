/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 16:26:26 by ohakola           #+#    #+#             */
/*   Updated: 2020/08/31 20:03:11 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Adds a string to the beginning of another
*/

char					*add_str_to_beg(char *str, char *add,
						int len2, int len1)
{
	char					*res;

	res = ft_strnjoin(add, str, len1, len2);
	ft_strdel(&str);
	return (res);
}

/*
** Extends string size by add_size
*/

char					*extend_str(char *str, int size_in, int add_size)
{
	char	*res;
	int		i;

	if (!(res = malloc(sizeof(char) * (size_in + add_size + 1))))
		return (NULL);
	i = -1;
	while (++i < size_in)
		res[i] = str[i];
	res[i] = '\0';
	ft_strdel(&str);
	return (res);
}

/*
** Adds chars to the beginning of a char *
*/

char					*add_chars_to_str_begin(char *res, int start,
						int end, char c)
{
	int		i;

	ft_strrev(res);
	i = start - 1;
	while (++i < end)
		res[i] = c;
	res[i] = '\0';
	ft_strrev(res);
	return (res);
}

/*
** Adds chars to the beginning of a char * when char * includes null char
** (Used in handling null char print out)
*/

char					*add_chars_to_null_str_begin(char *res, int start,
						int end, char c)
{
	int		i;

	i = start - 1;
	while (++i < end)
		res[i] = c;
	res[i] = '\0';
	res[0] = c;
	res[i - 1] = '\0';
	return (res);
}

/*
** Adds characters to end of char *
*/

char					*add_chars_to_str_end(char *res, int start,
						int end, char c)
{
	int		i;

	i = start - 1;
	while (++i < end)
		res[i] = c;
	res[i] = '\0';
	return (res);
}
