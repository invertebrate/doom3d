/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_matrix4_mul.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:17:23 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 17:19:16 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgmatrix.h"

void		ml_matrix4_mul(t_mat4 m1, t_mat4 m2, t_mat4 res)
{
	size_t		r;
	size_t		c;
	size_t		i;

	c = -1;
	while (++c < 4)
	{
		r = -1;
		while (++r < 4)
		{
			res[r][c] = 0;
			i = -1;
			while (++i < 4)
				res[r][c] += m1[i][c] * m2[r][i];
		}
	}
}
