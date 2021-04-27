/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo     <veilo@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 18:11:02 by veilo             #+#    #+#             */
/*   Updated: 2021/04/28 18:49:33 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void			update_light_sources_anim3d(t_doom3d *app, t_3d_object *object)
{
	t_animation_3d	*anim;
	int				i;
	float			radius;
	float			intensity;

	if (((t_npc*)(object->params))->animation_3d == NULL)
	{
		anim = ((t_npc*)object->params)->animation_3d;
		radius = app->unit_size * 25.0;
		intensity = 0.5;
		ft_memset(anim->current_object->material->light_sources, 0,
			sizeof(anim->current_object->material->light_sources));
		anim->current_object->material->num_lights = 0;
		i = -1;
		while (++i < (int32_t)app->active_scene->num_scene_lights)
			update_one_light_source(app, anim->current_object,
				(float[2]){radius, intensity}, i);
	}
}

/*
** Update scene light sources per frame to object materials for shading
*/

void			update_light_sources(t_doom3d *app, t_3d_object *object)
{
	int32_t	i;
	float	radius;
	float	intensity;

	if (!(object->material->shading_opts & e_shading_invisible) &&
		object->type != object_type_light)
	{
		if (object->params != NULL && object->params_type == object_type_npc)
		{
			update_light_sources_anim3d(app, object);
			return ;
		}
		radius = app->unit_size * 25.0;
		intensity = 0.5;
		ft_memset(object->material->light_sources, 0,
			sizeof(object->material->light_sources));
		object->material->num_lights = 0;
		i = -1;
		while (++i < (int32_t)app->active_scene->num_scene_lights)
			update_one_light_source(app, object,
				(float[2]){radius, intensity}, i);
	}
}
