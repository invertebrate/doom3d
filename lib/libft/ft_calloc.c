/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 17:31:06 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/03 16:37:13 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The ft_calloc() allocates size of memory initialized with zeros
*/

void	*ft_calloc(size_t size)
{
	unsigned char	*mem;

	mem = (void *)malloc(size);
	if (!mem)
		return (NULL);
	ft_bzero(mem, size);
	return ((void *)mem);
}
