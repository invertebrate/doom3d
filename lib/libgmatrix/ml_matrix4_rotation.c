/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_matrix4_rotation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:17:23 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 17:19:07 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgmatrix.h"

void		ml_matrix4_rotation_x(float rad, t_mat4 res)
{
	ft_memset(res, 0, sizeof(t_mat4));
	res[0][0] = 1;
	res[3][3] = 1;
	res[1][1] = cos(rad);
	res[2][1] = -sin(rad);
	res[1][2] = sin(rad);
	res[2][2] = cos(rad);
}

void		ml_matrix4_rotation_y(float rad, t_mat4 res)
{
	ft_memset(res, 0, sizeof(t_mat4));
	res[1][1] = 1;
	res[3][3] = 1;
	res[0][0] = cos(rad);
	res[0][2] = -sin(rad);
	res[2][0] = sin(rad);
	res[2][2] = cos(rad);
}

void		ml_matrix4_rotation_z(float rad, t_mat4 res)
{
	ft_memset(res, 0, sizeof(t_mat4));
	res[2][2] = 1;
	res[3][3] = 1;
	res[0][0] = cos(rad);
	res[1][0] = -sin(rad);
	res[0][1] = sin(rad);
	res[1][1] = cos(rad);
}

void		ml_matrix4_rotation(float rad_x, float rad_y, float rad_z,
			t_mat4 res)
{
	t_mat4	rotx;
	t_mat4	roty;
	t_mat4	rotz;
	t_mat4	tmp;

	ft_memset(res, 0, sizeof(t_mat4));
	ml_matrix4_rotation_x(rad_x, rotx);
	ml_matrix4_rotation_y(rad_y, roty);
	ml_matrix4_rotation_z(rad_z, rotz);
	ml_matrix4_mul(roty, rotx, tmp);
	ml_matrix4_mul(rotz, tmp, res);
}
