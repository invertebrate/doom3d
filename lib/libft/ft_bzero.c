/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 13:56:04 by ohakola           #+#    #+#             */
/*   Updated: 2020/08/24 22:17:40 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The ft_bzero() function writes n zeroed bytes to the string s.
** If n is zero, ft_bzero() does nothing.
*/

void	ft_bzero(void *s, size_t n)
{
	char	*cpy;

	if (n == false)
		return ;
	cpy = s;
	while (n--)
		*cpy++ = 0;
}
