/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_vector3_normalize.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:17:23 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/02 01:07:58 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgmatrix.h"

/*
** Normalize vector3
*/

void	ml_vector3_normalize(t_vec3 v, t_vec3 res)
{
	size_t		i;
	float		mag;

	i = -1;
	mag = ml_vector3_mag(v);
	while (++i < 3)
	{
		if (mag > 0)
			res[i] = v[i] / mag;
	}
}
