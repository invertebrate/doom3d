/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_vector3_to_vec4.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:17:23 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/24 16:01:52 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgmatrix.h"

/*
** Transform a vector3 to vector4
*/

void		ml_vector3_to_vec4(t_vec3 v1, t_vec4 res)
{
	size_t	i;

	i = -1;
	while (++i < 4)
		res[i] = i == 3 ? 1 : v1[i];
}
