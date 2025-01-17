/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_matrix4_translation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:17:23 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/02 01:06:31 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgmatrix.h"

/*
** Create a translation matrix which can be used to move vectors and matrices
** by x, y, z
*/

void	ml_matrix4_translation(float to_x, float to_y, float to_z,
			t_mat4 res)
{
	ml_matrix4_id(res);
	res[3][0] = to_x;
	res[3][1] = to_y;
	res[3][2] = to_z;
}
