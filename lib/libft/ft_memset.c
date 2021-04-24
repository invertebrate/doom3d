/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:13:19 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/24 15:56:15 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_utils.h"

/*
** The ft_memset() function writes len bytes of value c
** (converted to an unsigned char) to the string b.
*/

void			*ft_memset(void *b, int c, size_t n)
{
	unsigned char *cpy;

	cpy = b;
	while (n--)
		*cpy++ = (unsigned char)c;
	return (b);
}
