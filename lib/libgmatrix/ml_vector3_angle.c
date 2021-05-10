/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_vector3_angle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 19:35:40 by veilo             #+#    #+#             */
/*   Updated: 2021/05/10 17:53:40 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Returns the angle between 2 vectors in 3 space.
*/

#include "libgmatrix.h"

float	ml_vector3_angle_rad(t_vec3 v1, t_vec3 v2)
{
	float	dot;

	ml_vector3_normalize(v1, v1);
	ml_vector3_normalize(v2, v2);
	dot = ml_vector3_dot(v1, v2);
	return (acos(dot));
}

float	ml_vector3_angle_deg(t_vec3 v1, t_vec3 v2)
{
	float	dot;

	ml_vector3_normalize(v1, v1);
	ml_vector3_normalize(v2, v2);
	dot = ml_vector3_dot(v1, v2);
	return ((180 / M_PI) * acos(dot));
}
