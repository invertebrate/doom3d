/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_vector4_normalize.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:17:23 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/24 16:02:06 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgmatrix.h"

/*
** Normalize a vector4
*/

void		ml_vector4_normalize(t_vec4 v, t_vec4 res)
{
	size_t		i;
	float		mag;

	i = -1;
	mag = ml_vector4_mag(v);
	while (++i < 4)
		res[i] = v[i] / mag;
}
