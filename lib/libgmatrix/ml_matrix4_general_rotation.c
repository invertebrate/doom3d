/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_matrix4_general_rotation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:17:23 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 17:19:30 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgmatrix.h"

/*
** NOTE: USES THE MATH.H LIBRARY!
** Creates the rotation matrix for rotating around
** an arbitrary t_vec3 angle_deg degrees.
*/

void		ml_matrix4_general_rotation(t_vec3 axis, float rad_angle,
				t_mat4 res)
{
	ml_matrix4_copy((t_mat4){
		{cos(rad_angle) + axis[0] * axis[0] * (1 - cos(rad_angle)),
			axis[0] * axis[1] * (1 - cos(rad_angle)) - axis[2] * sin(rad_angle),
			axis[0] * axis[2] * (1 - cos(rad_angle)) + axis[1] * sin(rad_angle),
			0},
		{axis[1] * axis[0] * (1 - cos(rad_angle)) + axis[2] * sin(rad_angle),
			cos(rad_angle) + axis[1] * axis[1] * (1 - cos(rad_angle)),
			axis[1] * axis[2] * (1 - cos(rad_angle)) - axis[0] * sin(rad_angle),
			0},
		{axis[2] * axis[0] * (1 - cos(rad_angle)) - axis[1] * sin(rad_angle),
			axis[2] * axis[1] * (1 - cos(rad_angle)) + axis[0] * sin(rad_angle),
			cos(rad_angle) + axis[2] * axis[2] * (1 - cos(rad_angle)),
			0},
		{0, 0, 0, 1}}, res);
}
