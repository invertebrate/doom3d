/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_vector2_normalize.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:17:23 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 17:18:32 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgmatrix.h"

void	ml_vector2_normalize(t_vec2 v, t_vec2 res)
{
	size_t	i;
	float	mag;

	i = -1;
	mag = ml_vector2_mag(v);
	while (++i < 2)
	{
		if (mag > 0)
			res[i] = v[i] / mag;
	}
}
