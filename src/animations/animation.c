/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 18:41:09 by veilo             #+#    #+#             */
/*   Updated: 2021/01/29 19:57:51 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void			update_app_ticks(t_doom3d *app)
{
	app->current_tick = (SDL_GetPerformanceCounter() * TICKS_PER_SEC) /
						SDL_GetPerformanceFrequency();
	// ft_printf("current_tick %d\n", app->current_tick);
}

uint32_t		update_current_frame(t_doom3d *app, t_animation_3d *animation)
{
	uint32_t	current_frame;
	static uint32_t c = 0;
	current_frame = animation->current_frame;

	// if (c)
	// {
	// 	current_frame = (current_frame + 1) % 6;
	// 	c = 0;
	// }
	// else 
	// 	c = 1;
	current_frame = animation->start_frame +
	((app->current_tick - animation->start_tick) % (int)((TICKS_PER_SEC) / (ANIM_3D_FPS)));

	animation->current_frame = current_frame;
	return (current_frame);
	(void)app;
	(void)c;
}

t_triangle		*get_animation_3d_triangle(t_3d_object *obj)
{
	t_triangle		*result_tri;
	t_animation_3d	*anim;

	result_tri = NULL;
	if (obj->type == object_type_npc)
	{
		anim =  ((t_npc*)obj->params)->animation_3d;
		result_tri =anim->animation_frames[anim->current_frame]->triangles;
	}
	return (result_tri);
}
