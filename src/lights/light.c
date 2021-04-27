/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 00:54:34 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/26 03:10:11 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Transform light position for rasterizer origo at (0, 0, 0)
*/

static void		transform_light_pos(t_doom3d *app, t_vec3 light_pos,
					int32_t object_i)
{
	ml_matrix4_mul_vec3(app->player.inv_translation,
		app->active_scene->scene_lights[object_i]->position, light_pos);
	ml_matrix4_mul_vec3(app->player.inv_rotation,
		light_pos, light_pos);
}

static void		update_one_light_source(t_doom3d *app, t_3d_object *object,
					float radius_intensity[2], int32_t i)
{
	float	radius_scale;
	t_vec3	light_pos;

	radius_scale =
		app->active_scene->scene_lights[i]->scale[0][0] /
			app->unit_size;
	transform_light_pos(app, light_pos, i);
	l3d_3d_object_add_light_source(object,
		light_pos, (float[2]){radius_intensity[0] * radius_scale,
			radius_intensity[1]},
		get_light_emit_color(app->active_scene->scene_lights[i]));
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
		radius = app->unit_size * 25.0;
		intensity = 0.5;
		ft_memset(object->material->light_sources, 0,
			sizeof(object->material->light_sources));
		object->material->num_lights = 0;
		i = -1;
		while (++i < (int32_t)app->active_scene->num_scene_lights)
			update_one_light_source(app, object,
				(float[2]){radius, intensity}, i);
	}//HERE PUT UPDATE LIGHTS ON CURRENT ANIMATION FRAME
}

/*
** Set scene light sources in editor. (Basically same as in game, but
** in game updates light sources separately in object_update.c to save one loop)
*/

void			update_editor_light_sources(t_doom3d *app)
{
	int32_t			i;
	t_3d_object		*obj;

	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted))
	{
		obj = app->active_scene->objects[i];
		if (!obj)
			continue ;
		update_light_sources(app, obj);
	}
}
