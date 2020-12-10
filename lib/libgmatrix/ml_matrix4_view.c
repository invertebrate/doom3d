/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_matrix4_view.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:17:23 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 17:19:01 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgmatrix.h"

static void		view_matrix(t_vec3 axes[3], t_vec3 eye, t_mat4 res)
{
	res[0][0] = axes[0][0];
	res[0][1] = axes[1][0];
	res[0][2] = -axes[2][0];
	res[1][0] = axes[0][1];
	res[1][1] = axes[1][1];
	res[1][2] = -axes[2][1];
	res[2][0] = axes[0][2];
	res[2][1] = axes[1][2];
	res[2][2] = -axes[2][2];
	res[3][0] = -ml_vector3_dot(axes[0], eye);
	res[3][1] = -ml_vector3_dot(axes[1], eye);
	res[3][2] = ml_vector3_dot(axes[2], eye);
	res[0][3] = 0.0f;
	res[1][3] = 0.0f;
	res[2][3] = 0.0f;
	res[3][3] = 1.0f;
}

void			ml_matrix4_lookat(t_vec3 eye, t_vec3 center, t_vec3 up,
				t_mat4 res)
{
	t_vec3			zaxis;
	t_vec3			xaxis;
	t_vec3			yaxis;
	t_vec3			axes[3];

	ft_memset(res, 0, sizeof(t_mat4));
	ml_vector3_sub(center, eye, zaxis);
	ml_vector3_normalize(zaxis, zaxis);
	ml_vector3_cross(zaxis, up, xaxis);
	ml_vector3_normalize(xaxis, xaxis);
	ml_vector3_cross(xaxis, zaxis, yaxis);
	ft_memcpy(&axes[0], &xaxis, sizeof(t_vec3));
	ft_memcpy(&axes[1], &yaxis, sizeof(t_vec3));
	ft_memcpy(&axes[2], &zaxis, sizeof(t_vec3));
	view_matrix(axes, eye, res);
}

void			ml_matrix4_fps(t_vec3 eye, float pitch, float yaw, t_mat4 res)
{
	t_vec3			zaxis;
	t_vec3			xaxis;
	t_vec3			yaxis;
	t_vec3			axes[3];

	ft_memset(res, 0, sizeof(t_mat4));
	pitch *= M_PI / 180;
	yaw *= M_PI / 180;
	zaxis[0] = -1 * sin(yaw) * cos(pitch);
	zaxis[1] = -1 * -sin(pitch);
	zaxis[2] = -1 * cos(pitch) * cos(yaw);
	xaxis[0] = cos(yaw);
	xaxis[1] = 0;
	xaxis[2] = -sin(yaw);
	yaxis[0] = sin(yaw) * sin(pitch);
	yaxis[1] = cos(pitch);
	yaxis[2] = cos(yaw) * sin(pitch);
	ft_memcpy(axes[0], xaxis, sizeof(t_vec3));
	ft_memcpy(axes[1], yaxis, sizeof(t_vec3));
	ft_memcpy(axes[2], zaxis, sizeof(t_vec3));
	view_matrix(axes, eye, res);
}
