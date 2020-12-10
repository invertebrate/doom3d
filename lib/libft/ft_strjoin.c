/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 20:24:20 by ohakola           #+#    #+#             */
/*   Updated: 2020/03/15 18:45:19 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Allocates (with malloc(3)) and returns a “fresh” string ending with ’\0’,
** result of the concatenation of s1 and s2. If
** the allocation fails the function returns NULL.
*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*str;

	if (!s1 || !s2)
		return (NULL);
	str = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	if (!str)
		return (NULL);
	ft_strcpy(str, (char*)s1);
	str = ft_strcat(str, (char*)s2);
	return (str);
}

char	*ft_strnjoin(char const *s1, char const *s2,
		size_t len1, size_t len2)
{
	char			*str;

	if (!s1 || !s2)
		return (NULL);
	str = ft_strnew(len1 + len2);
	if (!str)
		return (NULL);
	ft_strcpy(str, (char*)s1);
	str = ft_strcat(str, (char*)s2);
	return (str);
}
