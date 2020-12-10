/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 19:10:25 by ohakola           #+#    #+#             */
/*   Updated: 2020/09/01 16:30:33 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t				get_num_len(uint64_t nb, uint64_t base)
{
	size_t	i;

	if (nb == false)
		return (1);
	i = 0;
	while (nb != 0)
	{
		nb = nb / base;
		i++;
	}
	return (i);
}

/*
** The ft_itoa() function transforms an integer base 10
** into a string representation of the number
*/

char				*ft_itoa(int32_t nb)
{
	return (ft_itoa_base_32(nb, 10));
}

char				*ft_itoa_64(int64_t nb)
{
	return (ft_itoa_base_64(nb, 10));
}
