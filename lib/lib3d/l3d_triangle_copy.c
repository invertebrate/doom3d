/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_triangle_copy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:50:08 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/06 17:50:13 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

t_triangle			*l3d_triangle_copy(t_triangle *src, t_bool new_vertices)
{
	t_triangle	*dst;
	int32_t		i;

	error_check(!(dst = malloc(sizeof(t_triangle))), "Failed to malloc tri");
	ft_memcpy(dst, src, sizeof(t_triangle));
	if (new_vertices)
	{
		i = -1;
		while (++i < 3)
		{
			error_check(!(dst->vtc[i] = malloc(sizeof(t_vertex))),
				"Failed to malloc vtc for tri");
			ft_memcpy(dst->vtc[i], src->vtc[i], sizeof(t_vertex));
		}
	}
	return (dst);
}
