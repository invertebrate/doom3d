/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_explosion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 15:43:05 by phakakos          #+#    #+#             */
/*   Updated: 2021/05/31 21:54:58 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	transform_explosion_plane(t_doom3d *app, t_projectile *projectile,
					t_3d_object *explosion_effect)
{
	float		scale;

	if (!explosion_effect)
		return ;
	scale = projectile->radius
		/ (ml_vector3_mag(explosion_effect->aabb.size) * 2.0);
	l3d_3d_object_scale(explosion_effect, scale, scale, scale);
	l3d_3d_object_rotate_matrix(explosion_effect, app->player.dir_rotation);
}

static void	explosion_place(t_doom3d *app, t_3d_object **explosions,
										t_3d_object *model, t_vec3 pos)
{
	explosions[0] = place_procedural_temp_object(app,
			(t_procedural_tmp_obj_params){.model = model,
			.texture = "assets/animations/explosion1.bmp",
			.lifetime = 100, .delay = 0}, pos);
	explosions[1] = place_procedural_temp_object(app,
			(t_procedural_tmp_obj_params){.model = model,
			.texture = "assets/animations/explosion2.bmp",
			.lifetime = 100, .delay = 100}, pos);
	explosions[2] = place_procedural_temp_object(app,
			(t_procedural_tmp_obj_params){.model = model,
			.texture = "assets/animations/explosion3.bmp",
			.lifetime = 100, .delay = 200}, pos);
	explosions[3] = place_procedural_temp_object(app,
			(t_procedural_tmp_obj_params){.model = model,
			.texture = "assets/animations/explosion4.bmp",
			.lifetime = 100, .delay = 300}, pos);
	explosions[4] = place_procedural_temp_object(app,
			(t_procedural_tmp_obj_params){.model = model,
			.texture = NULL,
			.lifetime = 400, .delay = 0}, pos);
}

static void	init_holograms(t_doom3d *app, t_3d_object **explosions,
										t_3d_object *model, t_vec3 pos)
{
	int32_t	i;

	explosion_place(app, explosions, model, pos);
	i = -1;
	while (++i < 4)
		explosions[i]->material->shading_opts |= e_shading_standard
			| e_shading_luminous;
	l3d_3d_object_scale(explosions[4], 0.3, 0.3, 0.3);
	l3d_object_set_shading_opts(explosions[4],
		e_shading_invisible);
	l3d_3d_object_set_params(explosions[4], NULL, 0, light_type_explosion);
	explosions[4]->type = object_type_light;
}

void	projectile_explode_effect(t_doom3d *app, t_3d_object *projectile_obj)
{
	t_3d_object		*explosions[5];
	t_3d_object		*model;
	int32_t			i;
	t_vec3			add;
	t_vec3			pos;

	ml_vector3_mul(((t_projectile *)projectile_obj->params)->dir,
		-1 * 0.2 * app->unit_size, add);
	ml_vector3_add(projectile_obj->position, add, pos);
	model = l3d_plane_create(NULL, NULL);
	init_holograms(app, explosions, model, pos);
	l3d_3d_object_destroy(model);
	i = -1;
	while (++i < 4)
		transform_explosion_plane(app, projectile_obj->params,
			explosions[i]);
	push_custom_event(app,
		event_effect_play, (void*)sf_explsion2, s_ini(0, 1, st_game,
			distance_vol(0.7, sound_mag(app->player.pos,
					projectile_obj->position), 50000)));
}
