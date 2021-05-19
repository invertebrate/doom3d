/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 18:11:02 by veilo             #+#    #+#             */
/*   Updated: 2021/05/19 18:37:04 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
**	Updates light sources for current animation frame
*/

void	update_light_sources_anim3d(t_doom3d *app, t_3d_object *object)
{
	t_animation_3d	*anim;
	int				i;
	float			radius;
	float			intensity;

	i = -1;
	if (((t_npc *)(object->params))->animation_3d != NULL)
	{
		anim = ((t_npc *)object->params)->animation_3d;
		radius = app->unit_size * 25.0;
		intensity = 0.5;
		ft_memset(anim->current_object->material->light_sources, 0,
			sizeof(anim->current_object->material->light_sources));
		anim->current_object->material->num_lights = 0;
		i = -1;
		while (++i < (int32_t)app->active_scene->num_scene_lights)
			update_one_light_source(app, anim->current_object,
				(float [2]){radius, intensity}, i);
		anim->current_object->material->flashlight = &(app->player.flashlight);
	}
}

void	check_light_breakable(t_doom3d *app, t_3d_object *light_obj)
{
	t_3d_object	*new_obj;

	if (light_obj->params_type == light_type_breakable)
	{
		new_obj = place_scene_object(app,
				(const char *[3]){"assets/models/lamp_breakable.obj",
				"assets/textures/lamp_breakable.bmp", NULL},
				light_obj->position);
		l3d_3d_object_rotate(new_obj, 180, 0, 0);
		push_custom_event(app, event_object_delete, light_obj, NULL);
		push_custom_event(app,
			event_effect_play, (void *)sf_glass, s_ini(0, 1, st_game,
				distance_vol(1.0f, sound_mag(app->player.pos,
						light_obj->position), -1)));
	}
	if (light_obj->params_type == light_type_mushroom)
		push_custom_event(app, event_object_delete, light_obj, NULL);
}
