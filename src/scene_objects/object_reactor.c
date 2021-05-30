/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_reactor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 00:18:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/31 00:57:59 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	transform_explosion_plane(t_doom3d *app, t_3d_object *reactor,
				t_3d_object *explosion_effect)
{
	float	scale;

	if (!explosion_effect)
		return ;
	scale = (reactor->scale[0][0] / app->unit_size) * 1.5;
	rotate_object_by_player_dir(app, explosion_effect);
	l3d_3d_object_scale(explosion_effect, scale, scale, scale);
	l3d_3d_object_translate(explosion_effect, 0,
		app->unit_size * 1.3 * scale, 0);
}

static void	explosion_place_sub(t_doom3d *app, t_3d_object **explosions,
										t_3d_object *model, t_vec3 pos)
{
	explosions[2] = place_procedural_temp_object(app,
			(t_procedural_tmp_obj_params){.model = model,
			.texture = "assets/animations/reaction_3.bmp",
			.lifetime = 100, .delay = 200}, pos);
	explosions[3] = place_procedural_temp_object(app,
			(t_procedural_tmp_obj_params){.model = model,
			.texture = "assets/animations/reaction_4.bmp",
			.lifetime = 100, .delay = 300}, pos);
	explosions[4] = place_procedural_temp_object(app,
			(t_procedural_tmp_obj_params){.model = model,
			.texture = "assets/animations/reaction_5.bmp",
			.lifetime = 100, .delay = 400}, pos);
	explosions[5] = place_procedural_temp_object(app,
			(t_procedural_tmp_obj_params){.model = model,
			.texture = "assets/animations/reaction_6.bmp",
			.lifetime = 100, .delay = 500}, pos);
	explosions[6] = place_procedural_temp_object(app,
			(t_procedural_tmp_obj_params){.model = model, .texture = NULL,
			.lifetime = 600, .delay = 0}, pos);
}

static void	init_explosions(t_doom3d *app, t_3d_object **explosions,
										t_3d_object *model, t_vec3 pos)
{
	int32_t	i;

	explosions[0] = place_procedural_temp_object(app,
			(t_procedural_tmp_obj_params){.model = model,
			.texture = "assets/animations/reaction_1.bmp",
			.lifetime = 100, .delay = 0}, pos);
	explosions[1] = place_procedural_temp_object(app,
			(t_procedural_tmp_obj_params){.model = model,
			.texture = "assets/animations/reaction_2.bmp",
			.lifetime = 100, .delay = 100}, pos);
	explosion_place_sub(app, explosions, model, pos);
	i = -1;
	while (++i < 7)
		explosions[i]->material->shading_opts |= e_shading_standard
			| e_shading_luminous;
	l3d_3d_object_scale(explosions[6], 0.3, 0.3, 0.3);
	l3d_object_set_shading_opts(explosions[6], e_shading_invisible);
	l3d_3d_object_set_params(explosions[6], NULL, 0, light_type_explosion);
	explosions[6]->type = object_type_light;
	explosions[6]->params_type = light_type_cyan;
}

/*
** This time must equal the length of the animations .lifetime = 600,
*/

static t_bool	should_create(void)
{
	static uint32_t		creation_time;

	if (SDL_GetTicks() - creation_time > 600)
	{
		creation_time = SDL_GetTicks();
		return (true);
	}
	return (false);
}

void	reactor_explosion_effect(t_doom3d *app, t_3d_object *reactor_obj)
{
	t_3d_object			*explosions[7];
	t_3d_object			*model;
	int32_t				i;
	t_vec3				pos;

	if (!should_create())
		return ;
	if (app->settings.is_debug)
		LOG_DEBUG("Create reactor explosion");
	ml_vector3_copy(reactor_obj->position, pos);
	model = l3d_plane_create(NULL, NULL);
	init_explosions(app, explosions, model, pos);
	l3d_3d_object_destroy(model);
	i = -1;
	while (++i < 7)
		transform_explosion_plane(app, reactor_obj, explosions[i]);
}
