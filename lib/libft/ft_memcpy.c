/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:15:27 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 17:15:28 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_utils.h"

/*
** The ft_memcpy() function copies n bytes from memory area src to memory
** area dst.
** If dst and src overlap, behavior is undefined.  Applications in
** which dst and src might overlap should use memmove(3) instead.
** This version has been optimized to copy more at once.
*/

void			*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*destcpy;
	const char	*srccpy;

	if (src == NULL && dst == NULL)
		return (NULL);
	destcpy = dst;
	srccpy = src;
	while (n--)
		*destcpy++ = *srccpy++;
	return (dst);
}
