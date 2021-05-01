/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_triangle_clone.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 17:50:08 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/01 22:44:18 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

/*
** Clone triangle copying vertices if needed
*/

t_triangle	*l3d_triangle_clone(t_triangle *src, t_bool new_vertices)
{
	t_triangle	*dst;
	int32_t		i;

	error_check(!(dst = ft_calloc(sizeof(t_triangle))), "Failed to malloc tri");
	ft_memcpy(dst, src, sizeof(t_triangle));
	if (new_vertices)
	{
		i = -1;
		while (++i < 3)
		{
			error_check(!(dst->vtc[i] = ft_calloc(sizeof(t_vertex))),
				"Failed to malloc vtc for tri");
			ft_memcpy(dst->vtc[i], src->vtc[i], sizeof(t_vertex));
		}
	}
	return (dst);
}

/*
** Copy triangles while maintaining own vertex pointers
** Copies the vertex content to dst though.
*/

void	*l3d_triangle_copy(t_triangle *dst, t_triangle *src)
{
	int32_t		i;
	t_vertex	*vtc[3];

	i = -1;
	while (++i < 3)
		vtc[i] = dst->vtc[i];
	ft_memcpy(dst, src, sizeof(t_triangle));
	i = -1;
	while (++i < 3)
	{
		dst->vtc[i] = vtc[i];
		ft_memcpy(dst->vtc[i], src->vtc[i], sizeof(t_vertex));
	}
	return (dst);
}
