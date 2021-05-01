/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_cone_intersection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 19:03:26 by veilo             #+#    #+#             */
/*   Updated: 2021/05/01 21:48:42 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

/*
**	Checks if a given point is inside a cone
**	vars[0] is distance along dir axis
**	vars[1] is cone radius at at vars[0] distance along dir axis
**	vars[2] is orthogonal distance from dir axis
*/

float	*point_inside_cone(t_cone *cone, t_vec3 point, float *vars)
{
	t_vec3	scaled_dir;
	t_vec3	orth_dist_vec;
	t_vec3	px;

	ml_vector3_normalize(cone->dir, cone->dir);
	ml_vector3_sub(point, cone->apex, px);
	vars[0] = ml_vector3_dot(px, cone->dir);
	if (vars[0] > cone->height)
		return (NULL);
	vars[1] = (vars[0] / cone->height) * cone->radius;
	ml_vector3_mul(cone->dir, vars[0], scaled_dir);
	ml_vector3_sub(px, scaled_dir, orth_dist_vec);
	vars[2] = ml_vector3_mag(orth_dist_vec);
	if (vars[2] < vars[1])
		return (vars);
	else
		return (NULL);
}
