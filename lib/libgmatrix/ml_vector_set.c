/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_vector_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:17:23 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/18 19:59:54 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgmatrix.h"

/*
** Set vector3 by given values
*/
void		ml_vector3_set(t_vec3 vec, float v0, float v1, float v2)
{
	vec[0] = v0;
	vec[1] = v1;
	vec[2] = v2;
}

/*
** Set all vector3 values to val
*/
void		ml_vector3_set_all(t_vec3 vec, float val)
{
	int		i;

	i = -1;
	while (i++ < 3)
	{
		vec[i] = val;
	}
}

/*
** Set all vector4 values to val
*/
void		ml_vector4_set_all(t_vec4 vec, float val)
{
	int		i;

	i = -1;
	while (i++ < 4)
	{
		vec[i] = val;
	}
}
