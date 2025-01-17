/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 17:09:00 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/03 16:50:33 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The ft_strstr() function locates the first occurrence of the
** null-terminated string needle in the null-terminated string haystack.
*/

char	*ft_strstr(const char *haystack, const char *needle)
{
	int	i;
	int	needle_len;
	int	haystack_len;

	needle_len = ft_strlen(needle);
	haystack_len = ft_strlen(haystack);
	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (i < haystack_len)
	{
		if (*haystack == *needle)
		{
			if (ft_strncmp(haystack, needle, needle_len) == false)
				return ((char *)haystack);
		}
		i++;
		haystack++;
	}
	return (NULL);
}
