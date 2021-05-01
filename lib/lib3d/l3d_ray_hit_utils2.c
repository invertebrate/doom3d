/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_ray_hit_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 16:49:21 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/01 22:32:52 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

/*
** Get closest hit whether triangle or not (aabb might be the other)
*/

void	l3d_get_closest_hit(t_hits *hits, t_hit **closest)
{
	t_hits	*head;
	t_hit	*hit;

	head = hits;
	*closest = NULL;
	while (head)
	{
		hit = (t_hit *)head->content;
		if (*closest == NULL)
			*closest = hit;
		if (hit != NULL && hit->t <= (*closest)->t)
			*closest = hit;
		head = head->next;
	}
}

/*
** Get closest triangle hit within range `range`
*/

void	l3d_get_closest_triangle_hit_at_range(t_hits *hits,
			t_hit **closest,
			uint32_t ignore_id, float range)
{
	t_hits	*head;
	t_hit	*hit;

	head = hits;
	*closest = NULL;
	while (head)
	{
		hit = (t_hit *)head->content;
		if (*closest == NULL && hit->t > 0.0 && hit->t <= range
			&& hit->triangle->parent->id != ignore_id)
			*closest = hit;
		if (hit != NULL && hit->t > 0.0 && hit->t <= range
			&& hit->triangle->parent->id != ignore_id
			&& hit->t <= (*closest)->t)
			*closest = hit;
		head = head->next;
	}
	if (*closest && !(*closest)->triangle)
		*closest = NULL;
}
