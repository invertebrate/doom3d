/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 15:56:08 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/08 22:01:31 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The ft_strdup() function allocates sufficient memory for a copy of the
** string s1, does the copy, and returns a pointer to it.  The pointer may
** subsequently be used as an argument to the function free(3).
*/

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	len;

	len = (size_t)ft_strlen(s1);
	dup = (char*)ft_calloc(len + 1);
	if (dup)
	{
		dup = ft_memcpy(dup, s1, len + 1);
		dup[len] = '\0';
	}
	return (dup);
}
