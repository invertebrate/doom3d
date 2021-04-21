/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_matrix4_id.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:17:23 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/18 19:54:29 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgmatrix.h"

/*
** Create identity matrix
*/
void		ml_matrix4_id(t_mat4 res)
{
	size_t		r;
	size_t		c;

	c = -1;
	while (++c < 4)
	{
		r = -1;
		while (++r < 4)
			res[r][c] = 0;
	}
	res[0][0] = 1;
	res[1][1] = 1;
	res[2][2] = 1;
	res[3][3] = 1;
}
