/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_placement2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 00:56:11 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/30 22:27:00 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Place a light object in editor. Light type defines what color is emmitted.
*/

t_3d_object	*editor_place_light_object(t_doom3d *app, t_light_type light_type)
{
	t_3d_object		*light;
	t_vec3			pos;

	editor_pos_camera_front(app, pos);
	if (light_type == light_type_breakable)
		light = place_scene_object(app, (const char *[3]){
				"assets/models/lamp_breakable.obj",
				"assets/textures/lamp_breakable.bmp", NULL}, pos);
	else if (light_type == light_type_mushroom)
		light = place_scene_object(app, (const char *[3]){
				"assets/models/mushroom.obj",
				"assets/textures/mushroom_texture.bmp", NULL}, pos);
	else
		light = place_scene_object(app, (const char *[3]){
				"assets/models/light_sphere.obj", NULL, NULL}, pos);
	l3d_object_set_shading_opts(light,
		e_shading_transparent | get_light_shading(light_type));
	light->type = object_type_light;
	light->params_type = light_type;
	editor_objects_invisible_highlight(app);
	return (light);
}

t_3d_object	*place_plane_prefab(t_doom3d *app)
{
	t_3d_object		*model;
	t_3d_object		*object;
	t_vec3			pos;

	editor_pos_camera_front(app, pos);
	model = l3d_plane_create(NULL, NULL);
	object = place_procedural_scene_object(app, model, (const char *[2]){
			"assets/textures/lava.bmp", "assets/textures/lava_normal.bmp"},
			pos);
	l3d_3d_object_destroy(model);
	placement_notification(app, "Placing plane!");
	return (object);
}

/*
** This is ugly, I know. I'm a little ashamed. Normal objects should belong
** somewhere else, but norms & UI space makes it a bit hard so here they are
** filenames get passed as void* in case the data could not be cast to
** any prefab type...
*/

t_3d_object	*editor_place_default_object(t_doom3d *app, void *data)
{
	t_3d_object		*object;
	t_vec3			pos;

	object = NULL;
	if ((t_prefab_type)data == prefab_plane
		|| (t_prefab_type)data == prefab_reactor
		|| (t_prefab_type)data == prefab_window_wall
		|| (t_prefab_type)data == prefab_hologram
		|| (t_prefab_type)data == prefab_lava_plane
		|| (t_prefab_type)data == prefab_path_node)
	{
		object = editor_handle_prefab_place(app, data);
	}
	else if ((char *)data)
	{
		editor_pos_camera_front(app, pos);
		object = place_scene_object(app,
				(const char *[3]){data, NULL, NULL}, pos);
		object->material->shading_opts = e_shading_standard;
	}
	return (object);
}

/*
** Place an npc object in editor
*/

t_3d_object	*editor_place_npc_object(t_doom3d *app, t_npc_type type)
{
	t_vec3			pos;
	t_3d_object		*object;

	editor_pos_camera_front(app, pos);
	object = npc_spawn(app, pos, 0, type);
	placement_notification(app, "Placing Npc!");
	return (object);
}

/*
** Get position in front of camera for placing objects not attached to other
** objects.
*/

void	editor_pos_camera_front(t_doom3d *app, t_vec3 result)
{
	t_vec3	add;

	ml_vector3_mul(app->player.forward, app->unit_size * 30, add);
	ml_vector3_add(app->player.pos, add, result);
}
