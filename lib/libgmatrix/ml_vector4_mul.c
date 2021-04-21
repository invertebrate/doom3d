/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_vector4_mul.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:17:23 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/18 20:04:13 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgmatrix.h"

/*
** Multiply vector4 values with k
*/
void		ml_vector4_mul(t_vec4 v1, float k, t_vec4 res)
{
	size_t		i;

	ft_memset(res, 0, sizeof(t_vec4));
	i = -1;
	while (++i < 4)
		res[i] = v1[i] * k;
}
