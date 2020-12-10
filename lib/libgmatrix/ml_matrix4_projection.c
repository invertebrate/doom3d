/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_matrix4_projection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:17:23 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 17:19:13 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgmatrix.h"

static void		ml_matrix4_orthographic(t_canvas c, t_mat4 res)
{
	ft_memset(res, 0, sizeof(t_mat4));
	res[0][0] = 2.0f / c.width;
	res[1][1] = 2.0f / c.height;
	res[2][2] = -2.0f / (c.far - c.near);
	res[3][2] = (c.near + c.far) / (c.near - c.far);
	res[3][0] = -1.0f;
	res[3][1] = -1.0f;
	res[3][3] = 1.0f;
}

static void		ml_matrix4_perspective(t_canvas c, t_mat4 res)
{
	float		ar;
	float		angle;

	ft_memset(res, 0, sizeof(t_mat4));
	angle = ml_rad(c.fov);
	ar = c.width / c.height;
	res[0][0] = 1 / (ar * tan(angle / 2));
	res[1][1] = 1 / tan(angle / 2);
	res[2][2] = (c.near + c.far) / (c.near - c.far);
	res[2][3] = -1;
	res[3][2] = (2 * c.near * c.far) / (c.near - c.far);
}

void			ml_matrix4_projection(t_projection_type type,
				t_canvas c, t_mat4 res)
{
	if (type == ml_orthographic)
		ml_matrix4_orthographic(c, res);
	else if (type == ml_perspective)
		ml_matrix4_perspective(c, res);
	else
		ml_matrix4_perspective(c, res);
}
