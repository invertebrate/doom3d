/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 18:41:09 by veilo             #+#    #+#             */
/*   Updated: 2020/12/30 20:32:36 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// typedef struct	s_animated_object
// 	/* data */
// }				t_animated_object;


// struct			s_3d_object
// {
// 	uint32_t		id;
// 	t_vertex		**vertices;
// 	int32_t			num_vertices;
// 	t_triangle		*triangles;
// 	int32_t			num_triangles;
// 	t_material		*material;
// 	t_mat4			rotation;
// 	t_mat4			scale;
// 	t_vec3			position;
// 	t_box3d			aabb;
//     t_bool			animated;
//     uint32_t		frame_count;
//     uint32_t		current_frame;
// 	uint32_t		start_frame;
// 	uint32_t		start_tick;
//     t_3d_object		*animation_frames;
// };

#include "doom3d.h"

void			update_app_ticks(t_doom3d *app)
{
	app->current_tick = (SDL_GetPerformanceCounter() * 1000) /
						SDL_GetPerformanceFrequency();
}

// uint32_t		update_current_frame(t_doom3d *app, t_3d_object *object)
// {
// 	uint32_t	current_frame;

// 	current_frame = object->start_frame +
// 	((app->current_tick - object->start_tick) % (int)(TICKS_PER_SEC / ANIM_FPS));
// 	object->current_frame = current_frame;
// 	return (current_frame);

// int test()
// {
//     return (0);
// }