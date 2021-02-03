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

void					update_app_ticks(t_doom3d *app)
{
	app->current_tick = (SDL_GetPerformanceCounter() * TICKS_PER_SEC) /
						SDL_GetPerformanceFrequency();
}

uint32_t				anim_3d_frame_update(t_doom3d *app, t_animation_3d *animation)
{
	uint32_t	current_frame;

	// if (animation->current_clip == anim_3d_type_null)
	// 	return (UINT32_MAX);
	if ((app->current_tick - animation->start_tick) % (int)((TICKS_PER_SEC) / (ANIM_3D_FPS)) > 0)
	{
		animation->current_frame = (animation->current_frame + 1) % 
		animation->clip_info[animation->current_clip % ANIM_3D_TYPE_MOD].clip_length;
	}
	current_frame = animation->current_frame;
	animation->current_object = animation->animation_frames[animation->current_frame];
	return (current_frame);
}

/*
**	Changes the current playing animation clip of an object
*/

void					anim_3d_clip_set(t_doom3d *app, t_3d_object *obj,
										t_animation_3d_type clip, uint32_t start_frame)
{
	t_animation_3d		*anim;

	if (clip != anim_3d_type_move)
	{
		ft_printf("animation clip not yet implemented\n");
		return;
	}
	anim = ((t_npc*)obj->params)->animation_3d;
	anim->current_clip = clip;
	anim->current_frame = start_frame;
	anim->current_object = anim->animation_frames[clip % ANIM_3D_TYPE_MOD];
	anim->start_tick = app->current_tick;
	(void)app;
	(void)obj;
	(void)anim;
	(void)start_frame;
}

// t_triangle		*get_animation_3d_triangle(t_3d_object *obj)
// {
// 	t_triangle		*result_tri;
// 	t_animation_3d	*anim;

// 	result_tri = NULL;
// 	if (obj->type == object_type_npc)
// 	{
// 		anim =  ((t_npc*)obj->params)->animation_3d;
// 		result_tri = anim->animation_frames[anim->current_frame]->triangles;
// 		anim->current_object = anim->animation_frames[anim->current_frame];
// 	}
// 	return (result_tri);
// }
