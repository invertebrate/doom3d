/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_hologram.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 00:40:37 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/31 22:01:24 by ohakola          ###   ########.fr       */
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
	l3d_3d_object_rotate_matrix(hologram_effect, app->player.dir_rotation);
	l3d_3d_object_scale(hologram_effect, scale, scale, scale);
	l3d_3d_object_translate(hologram_effect, 0,
		app->unit_size * 4.0 * scale, 0);
}

static int32_t	get_player_angle_option(t_doom3d *app,
					t_vec3 pos)
{
	(void)app;
	(void)pos;
	return (0);
}

static void	hologram_place(t_doom3d *app, t_3d_object **holograms,
										t_3d_object *model, t_vec3 pos)
{
	int32_t		angle_opt;
	const char	*texture_file;

	angle_opt = get_player_angle_option(app, pos);
	if (angle_opt == 0)
		texture_file = "assets/animations/holoscreen1.bmp";
	else if (angle_opt == 1)
		texture_file = "assets/animations/holoscreen2.bmp";
	else if (angle_opt == 2)
		texture_file = "assets/animations/holoscreen3.bmp";
	else
		texture_file = "assets/animations/holoscreen4.bmp";
	holograms[0] = place_procedural_temp_object(app,
			(t_procedural_tmp_obj_params){.model = model,
			.texture = texture_file,
			.lifetime = 250, .delay = 0}, pos);
	holograms[1] = place_procedural_temp_object(app,
			(t_procedural_tmp_obj_params){.model = model,
			.texture = NULL,
			.lifetime = 250, .delay = 0}, pos);
}

static void	init_holograms(t_doom3d *app, t_3d_object **holograms,
										t_3d_object *model, t_vec3 pos)
{
	int32_t	i;

	hologram_place(app, holograms, model, pos);
	i = -1;
	while (++i < 1)
		holograms[i]->material->shading_opts |= e_shading_standard
			| e_shading_luminous;
	l3d_3d_object_scale(holograms[1], 0.3, 0.3, 0.3);
	l3d_object_set_shading_opts(holograms[1],
		e_shading_invisible);
	l3d_3d_object_set_params(holograms[1], NULL, 0, light_type_explosion);
	holograms[1]->type = object_type_light;
	holograms[1]->params_type = light_type_cyan;
}

void	hologram_effect(t_doom3d *app, t_3d_object *hologram_obj)
{
	t_3d_object			*holograms[2];
	t_3d_object			*model;
	int32_t				i;
	t_vec3				pos;

	if (!(hologram_obj->type == object_type_default
			&& hologram_obj->params_type == prefab_hologram))
		return ;
	if (!sprite_should_start(app, hologram_obj, 250))
		return ;
	if (app->settings.is_debug)
		LOG_DEBUG("Create hologram effect");
	ml_vector3_copy(hologram_obj->position, pos);
	model = l3d_plane_create(NULL, NULL);
	init_holograms(app, holograms, model, pos);
	l3d_3d_object_destroy(model);
	i = -1;
	while (++i < 2)
		transform_hologram_plane(app, hologram_obj, holograms[i]);
}
