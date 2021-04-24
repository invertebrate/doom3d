/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 19:23:17 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/24 15:58:06 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Returns a new str of size `size`. Allocated with malloc().
*/

char	*ft_strnew(size_t size)
{
	char	*str;

	str = (char*)ft_calloc(sizeof(*str) * size + 1);
	if (!str)
		return (NULL);
	return (str);
}
