/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_matrix4_mul_vec.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:17:23 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 17:19:19 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgmatrix.h"

void		ml_matrix4_mul_vec3(t_mat4 m, t_vec3 v, t_vec3 res)
{
	size_t		r;
	size_t		c;
	size_t		i;
	t_vec4		v4;
	t_vec4		res4;

	ft_memset(res4, 0, sizeof(t_vec4));
	ml_vector3_to_vec4(v, v4);
	c = -1;
	while (++c < 4)
	{
		r = -1;
		while (++r < 4)
			res4[c] += m[r][c] * v4[r];
	}
	i = -1;
	while (++i < 3)
		res[i] = res4[i];
}

void		ml_matrix4_mul_vec4(t_mat4 m, t_vec4 v, t_vec4 res)
{
	size_t		r;
	size_t		c;

	ft_memset(res, 0, sizeof(t_vec4));
	c = -1;
	while (++c < 4)
	{
		r = -1;
		while (++r < 4)
			res[c] += m[r][c] * v[r];
	}
}
