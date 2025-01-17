/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 16:50:08 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/03 16:13:17 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** ft_strncpy() copies at most len characters from src into dst.
** If src is less than len characters long, the remainder of dst
** is filled with `\0' characters.  Otherwise, dst is not terminated. The
** source and destination strings should not overlap, as the behavior is
** undefined.
*/

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	while (i <= len)
		dst[i++] = '\0';
	return (dst);
}
