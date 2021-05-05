/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 18:11:02 by veilo             #+#    #+#             */
/*   Updated: 2021/05/05 13:56:14 by sotamursu        ###   ########.fr       */
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
