/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_line_draw_utils1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 22:54:04 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/01 22:18:41 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d_internals.h"

/*
** Check if 2d point is inside a 2d aabb
*/

t_bool	l3d_point2d_inside_aabb(t_vec2 point,
			t_vec2 aabb[2])
{
	return (point[0] >= aabb[0][0] && point[0] < aabb[1][0] &&
		point[1] >= aabb[0][1] && point[1] < aabb[1][1]);
}

static void	copy_two_intersections(int32_t is_intersect[4],
				t_vec2 intersects[4], t_vec2 edge[2])
{
	int32_t		i;

	i = 0;
	while (is_intersect[i] != 1)
		i++;
	ml_vector2_copy(intersects[i++], edge[0]);
	while (is_intersect[i] != 1)
		i++;
	ml_vector2_copy(intersects[i], edge[1]);
}

static void	copy_one_intersections(t_vec2 aabb[2],
				int32_t is_intersect[4], t_vec2 intersects[4],
				t_vec2 edge[2])
{
	int32_t		i;

	i = 0;
	while (is_intersect[i] != 1)
		i++;
	if (l3d_point2d_inside_aabb(edge[0], aabb))
		ml_vector2_copy(intersects[i], edge[1]);
	else
		ml_vector2_copy(intersects[i], edge[0]);
}

/*
** If line intersects sub buffer twice, modify point1 and point2 to be
** those intersections. Draw.
** If line intersects once, check which point is inside sub buffer. Modify
** the other. Draw.
** If line intersects none, check if both points are inside, draw.
** Else don't draw.
*/

t_bool	l3d_clamp_edge_within_aabb(t_vec2 aabb[2],
			t_vec2 edge[2], int32_t is_intersect[4],
			t_vec2 intersects[4])
{
	int32_t		i;
	int32_t		count;

	i = -1;
	count = 0;
	while (++i < 4)
		if (is_intersect[i] == 1)
			count++;
	if (count == 2)
	{
		copy_two_intersections(is_intersect, intersects, edge);
		return (true);
	}
	else if (count == 1)
	{
		copy_one_intersections(aabb, is_intersect, intersects, edge);
		return (true);
	}
	return (l3d_point2d_inside_aabb(edge[0], aabb)
		&& l3d_point2d_inside_aabb(edge[1], aabb));
}

/*
** Get intersection points of a 2d edge / line inside aabb
*/

void	l3d_edge_aabb_intersections(t_vec2 aabb[2],
			t_vec2 edge[2], int32_t is_intersect[4],
			t_vec2 intersects[4])
{
	is_intersect[0] = l3d_2d_lines_intersect(
			(t_vec2[2]){{edge[0][0], edge[0][1]},
		{edge[1][0], edge[1][1]}},
			(t_vec2[2]){{aabb[0][0], aabb[0][0]}, {aabb[0][0], aabb[1][1]}},
			intersects[0]);
	is_intersect[1] = l3d_2d_lines_intersect(
			(t_vec2[2]){{edge[0][0], edge[0][1]},
		{edge[1][0], edge[1][1]}},
			(t_vec2[2]){{aabb[0][0], aabb[0][0]}, {aabb[1][0], aabb[0][1]}},
			intersects[1]);
	is_intersect[2] = l3d_2d_lines_intersect(
			(t_vec2[2]){{edge[0][0], edge[0][1]},
		{edge[1][0], edge[1][1]}},
			(t_vec2[2]){{aabb[1][0], aabb[0][0]}, {aabb[1][0], aabb[1][1]}},
			intersects[2]);
	is_intersect[3] = l3d_2d_lines_intersect(
			(t_vec2[2]){{edge[0][0], edge[0][1]},
		{edge[1][0], edge[1][1]}},
			(t_vec2[2]){{aabb[0][0], aabb[1][1]}, {aabb[1][0], aabb[1][1]}},
			intersects[3]);
}
