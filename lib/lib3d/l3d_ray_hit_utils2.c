/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l3d_ray_hit_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 16:49:21 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/30 17:30:14 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib3d.h"

void			l3d_get_smallest_dist_hit(t_hits *hits, t_hit **closest)
{
	t_hits	*head;
	t_hit	*hit;

	head = hits;
	*closest = NULL;
	while (head)
	{
		hit = (t_hit*)head->content;
		if (*closest == NULL)
			*closest = hit;
		if (hit != NULL && hit->t <= (*closest)->t)
			*closest = hit;
		head = head->next;
	}
}