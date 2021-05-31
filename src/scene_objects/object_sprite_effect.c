/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_sprite_effect.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 02:32:08 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/31 03:21:12 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	init_sprite_effect_timers(t_doom3d *app)
{
	t_3d_object	*obj;
	int32_t		i;
	uint64_t	timer;

	i = -1;
	while (++i < (int32_t)app->active_scene->num_objects)
	{
		timer = 1;
		obj = app->active_scene->objects[i];
		if (obj->material->texture
			&& ft_strequ(obj->material->texture->filename,
				"assets/textures/reactor_diffuse.bmp")
			&& obj->params_type == prefab_reactor)
			hash_map_add(app->active_scene->object_timers,
				(int64_t)obj->id, (void *)(intptr_t)timer);
		else if (obj->material->texture
			&& ft_strequ(obj->material->texture->filename,
				"assets/textures/hologram_diffuse.bmp")
			&& obj->params_type == prefab_hologram)
			hash_map_add(app->active_scene->object_timers,
				(int64_t)obj->id, (void *)(intptr_t)timer);
	}
}

t_bool	sprite_should_start(t_doom3d *app, t_3d_object *obj,
			uint64_t limit)
{
	void		*res;
	uint64_t	last_time;
	uint64_t	curr_time;

	res = hash_map_get(app->active_scene->object_timers, (int64_t)obj->id);
	if (res == 0)
		return (false);
	last_time = (uint64_t)res;
	curr_time = SDL_GetTicks();
	if (curr_time - last_time > limit)
	{
		last_time = curr_time;
		hash_map_add(app->active_scene->object_timers, (int64_t)obj->id,
			(void *)(intptr_t)last_time);
		return (true);
	}
	return (false);
}
