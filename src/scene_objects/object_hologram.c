/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_hologram.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 00:40:37 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/31 01:02:17 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	transform_hologram_plane(t_doom3d *app, t_3d_object *hologram_obj,
				t_3d_object *hologram_effect)
{
	float	scale;

	if (!hologram_effect)
		return ;
	scale = (hologram_obj->scale[0][0] / app->unit_size) * 1.2;
	rotate_object_by_player_dir(app, hologram_effect);
	l3d_3d_object_scale(hologram_effect, scale, scale, scale);
	l3d_3d_object_translate(hologram_effect, 0,
		app->unit_size * 4.0 * scale, 0);
}

static void	hologram_place(t_doom3d *app, t_3d_object **holograms,
										t_3d_object *model, t_vec3 pos)
{
	holograms[0] = place_procedural_temp_object(app,
			(t_procedural_tmp_obj_params){.model = model,
			.texture = "assets/animations/holoscreen1.bmp",
			.lifetime = 250, .delay = 0}, pos);
	holograms[1] = place_procedural_temp_object(app,
			(t_procedural_tmp_obj_params){.model = model,
			.texture = "assets/animations/holoscreen2.bmp",
			.lifetime = 250, .delay = 250}, pos);
	holograms[2] = place_procedural_temp_object(app,
			(t_procedural_tmp_obj_params){.model = model,
			.texture = "assets/animations/holoscreen3.bmp",
			.lifetime = 250, .delay = 500}, pos);
	holograms[3] = place_procedural_temp_object(app,
			(t_procedural_tmp_obj_params){.model = model,
			.texture = "assets/animations/holoscreen4.bmp",
			.lifetime = 250, .delay = 740}, pos);
	holograms[4] = place_procedural_temp_object(app,
			(t_procedural_tmp_obj_params){.model = model,
			.texture = NULL,
			.lifetime = 1000, .delay = 0}, pos);
}

static void	init_explosions(t_doom3d *app, t_3d_object **holograms,
										t_3d_object *model, t_vec3 pos)
{
	int32_t	i;

	hologram_place(app, holograms, model, pos);
	i = -1;
	while (++i < 4)
		holograms[i]->material->shading_opts |= e_shading_standard
			| e_shading_luminous;
	l3d_3d_object_scale(holograms[4], 0.3, 0.3, 0.3);
	l3d_object_set_shading_opts(holograms[4],
		e_shading_invisible);
	l3d_3d_object_set_params(holograms[4], NULL, 0, light_type_explosion);
	holograms[4]->type = object_type_light;
}

/*
** This time must equal the length of the animations .lifetime = 1000,
*/

static t_bool	should_create(void)
{
	static uint32_t		creation_time;

	if (SDL_GetTicks() - creation_time > 1000)
	{
		creation_time = SDL_GetTicks();
		return (true);
	}
	return (false);
}

void	hologram_effect(t_doom3d *app, t_3d_object *hologram_obj)
{
	t_3d_object			*holograms[5];
	t_3d_object			*model;
	int32_t				i;
	t_vec3				pos;

	if (!should_create())
		return ;
	if (app->settings.is_debug)
		LOG_DEBUG("Create hologram effect");
	ml_vector3_copy(hologram_obj->position, pos);
	model = l3d_plane_create(NULL, NULL);
	init_explosions(app, holograms, model, pos);
	l3d_3d_object_destroy(model);
	i = -1;
	while (++i < 4)
		transform_hologram_plane(app, hologram_obj, holograms[i]);
}
