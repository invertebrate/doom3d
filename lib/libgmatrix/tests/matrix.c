/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:17:23 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 17:19:47 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oh_test.h"
#include "libgmatrix.h"

const char		*test_matrix_inverse(void)
{
	t_mat4	inverse;
	char	matbuf[256];

	ml_matrix4_inverse((t_mat4){
		{1, 0, 33, 0},
		{5, 1, 0, 0},
		{0, 4, 555, 52},
		{0, 2, 0, 0}}, inverse);
	ml_matrix4_to_str(inverse, matbuf);
	OH_ASSERT("Inverse matrix is wrong",
		ft_strequ(matbuf,
		"Matrix4:\n"
		"|-0.000 |-0.000 | 0.030 |-0.323 |\n"
		"| 0.200 |-0.000 |-0.006 | 0.065 |\n"
		"|-0.000 |-0.000 |-0.000 | 0.019 |\n"
		"|-0.100 | 0.500 | 0.003 |-0.071 |\n"));
	return (0);
}
