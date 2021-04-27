/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_cone_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo     <veilo@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 19:03:26 by veilo             #+#    #+#             */
/*   Updated: 2021/04/07 19:53:54 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

/*
**	Checks if a given point is inside a cone, returns the distance from center
**	axis.
*/

float		point_inside_cone(t_cone *cone, t_vec3 point)
{
	t_vec3	scaled_dir;
	t_vec3	orth_dist_vec;
	t_vec3	px;
	float	vars[3];

	ml_vector3_normalize(cone->dir, cone->dir);
	ml_vector3_sub(point, cone->apex, px);
	if ((vars[0] = ml_vector3_dot(px, cone->dir)) > cone->height)
		return (-1.0);
	vars[1] = (vars[0] / cone->height) * cone->radius;
	ml_vector3_mul(cone->dir, vars[0], scaled_dir);
	ml_vector3_sub(px, scaled_dir,orth_dist_vec);
	vars[2] = ml_vector3_mag(orth_dist_vec);
	if (vars[2] < vars[1])
		return (vars[2]);
	else
		return (-1.0);
}