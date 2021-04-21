/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_matrix4_rotate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:17:23 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/18 19:56:38 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgmatrix.h"

/*
** Rotate matrix around x axis by rad angle
*/
void		ml_matrix4_rotate_x(t_mat4 m, float rad, t_mat4 res)
{
	t_mat4	rotation;

	ft_memset(res, 0, sizeof(t_mat4));
	ml_matrix4_rotation_x(rad, rotation);
	ml_matrix4_mul(m, rotation, res);
}

/*
** Rotate matrix around y axis by rad angle
*/
void		ml_matrix4_rotate_y(t_mat4 m, float rad, t_mat4 res)
{
	t_mat4	rotation;

	ft_memset(res, 0, sizeof(t_mat4));
	ml_matrix4_rotation_y(rad, rotation);
	ml_matrix4_mul(m, rotation, res);
}

/*
** Rotate matrix around z axis by rad angle
*/
void		ml_matrix4_rotate_z(t_mat4 m, float rad, t_mat4 res)
{
	t_mat4	rotation;

	ft_memset(res, 0, sizeof(t_mat4));
	ml_matrix4_rotation_z(rad, rotation);
	ml_matrix4_mul(m, rotation, res);
}
