/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ml_matrix3_create.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:17:23 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 17:20:50 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgmatrix.h"

void		ml_matrix3_column(t_vec3 column1, t_vec3 column2, t_vec3 column3,
				t_mat3 res)
{
	ml_vector3_copy(column1, res[0]);
	ml_vector3_copy(column2, res[1]);
	ml_vector3_copy(column3, res[2]);
}

void		ml_matrix3_row(t_vec3 row1, t_vec3 row2, t_vec3 row3, t_mat3 res)
{
	int		i;

	i = -1;
	while (++i < 3)
	{
		res[i][0] = row1[i];
		res[i][1] = row2[i];
		res[i][2] = row3[i];
	}
}
