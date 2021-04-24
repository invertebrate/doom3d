/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_vector4_mag.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:17:23 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/24 16:02:01 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgmatrix.h"

/*
** Length of a vector4 (magnitude)
*/

float		ml_vector4_mag(t_vec4 v)
{
	size_t		i;
	float		res;

	i = -1;
	res = 0;
	while (++i < 4)
		res += v[i] * v[i];
	return (sqrt(res));
}
