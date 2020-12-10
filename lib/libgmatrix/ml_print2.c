/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_print2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:17:23 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 17:21:09 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgmatrix.h"

void		ml_vector4_to_str(t_vec4 v, char *res)
{
	ft_sprintf(res, "Vec4[%.2f, %.2f, %.2f, %.2f]\n", v[0], v[1], v[2], v[3]);
}

void		ml_vector3_to_str(t_vec3 v, char *res)
{
	ft_sprintf(res, "Vec3[%.2f, %.2f, %.2f]\n", v[0], v[1], v[2]);
}

void		ml_vector2_to_str(t_vec3 v, char *res)
{
	ft_sprintf(res, "Vec3[%.2f, %.2f]\n", v[0], v[1]);
}
