/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 13:17:37 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/24 16:31:24 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Get key string of a texture file (helper used in map file reading)
*/

const char	*texture_file_key(char *filename, t_doom3d *app)
{
	int32_t		i;

	i = -1;
	while (++i < (int32_t)app->active_scene->asset_files.num_textures)
	{
		if (ft_strequ(filename,
			app->active_scene->asset_files.texture_files[i]))
			return (app->active_scene->asset_files.texture_files[i]);
	}
	return (NULL);
}

/*
** Get key string of a normal map file (helper used in map file reading)
*/

const char	*normal_map_file_key(char *filename, t_doom3d *app)
{
	int32_t		i;

	i = -1;
	while (++i < (int32_t)app->active_scene->asset_files.num_normal_maps)
	{
		if (ft_strequ(filename,
			app->active_scene->asset_files.normal_map_files[i]))
			return (app->active_scene->asset_files.texture_files[i]);
	}
	return (NULL);
}

/*
** Set invisible objects to be visibly highlighted in editor
*/

void		editor_objects_invisible_highlight(t_doom3d *app)
{
	t_3d_object	*obj;
	int32_t		i;

	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted))
	{
		obj = app->active_scene->objects[i];
		if (obj)
		{
			if (obj->type == object_type_trigger ||
				obj->type == object_type_light ||
				obj->type == object_type_path)
			{
				obj->material->shading_opts = (obj->material->shading_opts &
					~(e_shading_invisible));
				if (obj->params_type == trigger_player_start)
					obj->material->shading_opts = e_shading_green | e_shading_transparent;
				if (obj->params_type == trigger_player_end)
					obj->material->shading_opts = e_shading_red | e_shading_transparent;
				if (obj->params_type == object_type_light)
					obj->material->shading_opts = e_shading_yellow | e_shading_transparent;
				if (obj->params_type == object_type_path)
					obj->material->shading_opts = e_shading_cyan | e_shading_transparent;
			}
		}
	}
}

/*
** Set invisible objects to be invisible again
*/

void		editor_objects_invisible_unhighlight(t_doom3d *app)
{
	t_3d_object	*obj;
	int32_t		i;

	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted))
	{
		obj = app->active_scene->objects[i];
		if (obj &&
			((obj->type == object_type_trigger &&
				(obj->params_type == trigger_player_start ||
				obj->params_type == trigger_player_end)) ||
				obj->type == object_type_light ||
				obj->type == object_type_path))
			obj->material->shading_opts = e_shading_invisible;
	}
}

static void		duplicate_selected_object(t_doom3d *app, t_3d_object *selected)
{
	t_3d_object	*model;
	const char	*texture_file;
	const char	*normal_map_file;
	t_bool		start_or_end;

	start_or_end =
		(selected->type == object_type_trigger &&
			selected->params_type == trigger_player_start) || 
		(selected->type == object_type_trigger &&
			selected->params_type == trigger_player_end);
	if (!start_or_end)
	{
		texture_file = get_object_texture_filename(app->active_scene, selected);
		normal_map_file =
			get_object_normal_map_filename(app->active_scene, selected);
		model = l3d_3d_object_copy(selected);
		// Since we're copying and not selecting from model hash table, descale first
		l3d_3d_object_scale(model,
			1.0 / app->unit_size, 1.0 / app->unit_size, 1.0 / app->unit_size);
		l3d_3d_object_translate(model, -selected->position[0],
			-selected->position[1], -selected->position[2]);
		place_procedural_scene_object(app, model,
			(const char*[2]){texture_file, normal_map_file},
			(t_vec3){selected->position[0], selected->position[1],
			selected->position[2] + -app->unit_size});
		l3d_3d_object_destroy(model);
		// Since place scene object instantiates, we also want to copy shading
		app->active_scene->objects[
			app->active_scene->last_object_index]->material->shading_opts =
				selected->material->shading_opts;
		select_object(app,
			app->active_scene->objects[app->active_scene->last_object_index]);
		notify_user(app, (t_notification){
			.message = "Duplicated an object!", .time = 2000,
			.type = notification_type_info});
	}
	else if (start_or_end)
		notify_user(app, (t_notification){
			.message = "Can't duplicate start or end triggers!", .time = 2000,
			.type = notification_type_info});
}

/*
** Duplicates and selects any object that is not start or end trigger
** Uses existing object placement functionality from place scene object
** thus we need to once reset the scale by 1.0 / app->unit_size
** and inverse translate.
*/

void			editor_duplicate_selected_objects(t_doom3d *app)
{
	int32_t 	i;
	t_3d_object	*old_selected[MAX_SELECTED_OBJECTS];
	int32_t		num_selected;

	if (app->editor.num_selected_objects == 0)
	{
		notify_user(app, (t_notification){
			.message = "Select an object first for duplication!", .time = 2000,
			.type = notification_type_info});
		return ;
	}
	num_selected = app->editor.num_selected_objects;
	i = -1;
	while (++i < num_selected)
		old_selected[i] = app->editor.selected_objects[i];
	editor_deselect_all(app);
	i = -1;
	while (++i < num_selected)
		duplicate_selected_object(app, old_selected[i]);
}

/*
** Returns true if mouse is inside editor render view
*/

t_bool			mouse_inside_editor_view(t_doom3d *app)
{
	return (app->mouse.x > app->window->editor_pos[0] && app->mouse.x <
			app->window->editor_pos[0] +
			app->window->editor_framebuffer->width &&
		app->mouse.y > app->window->editor_pos[1] && app->mouse.y <
			app->window->editor_pos[1] +
			app->window->editor_framebuffer->height);
}

/*
** Transform mouse x & mouse y on window between 0.0 - 1.0 inside
** editor view.
*/

static void		get_mouse_editor_scale(t_doom3d *app, t_vec2 mouse_editor_pos)
{
	t_vec2	mouse_pos;

	ml_vector2_copy((t_vec2){app->mouse.x, app->mouse.y}, mouse_pos);
	ml_vector2_sub(mouse_pos, app->window->editor_pos, mouse_pos);
	ml_vector2_copy((t_vec2){
		(mouse_pos[0] / app->window->framebuffer->width),
		(mouse_pos[1] / app->window->framebuffer->height)}, mouse_pos);
	ml_vector2_copy((t_vec2){
		((float)app->window->framebuffer->width /
			(float)app->window->editor_framebuffer->width) *
			mouse_pos[0],
		((float)app->window->framebuffer->height /
			(float)app->window->editor_framebuffer->height) *
			mouse_pos[1]}, mouse_editor_pos);
}

/*
** 1. Go to screen origin
** 2. Use vectors to get to left top corner
** 3. Multiply sideways & down vectors by mouse editor scale
** 4. Got it!
*/

static void		get_mouse_world_position(t_doom3d *app, t_vec3 mouse_world_pos)
{
	t_vec2	mouse_editor_scale;
	t_vec3	screen_origin;
	t_vec3	add;
	t_vec3	dirs[4];
	float	dims[2];

	dims[0] = app->window->editor_framebuffer->width / 2.0;
	dims[1] = app->window->editor_framebuffer->height / 2.0;
	ml_vector3_mul(app->player.forward,
		ml_vector3_mag(app->active_scene->main_camera->screen.origin), add);
	ml_vector3_add(app->player.pos, add, screen_origin);
	ml_vector3_mul(app->player.up, dims[1], dirs[0]);
	ml_vector3_mul(app->player.sideways, dims[0], dirs[1]);
	ml_vector3_mul(app->player.up, -dims[1], dirs[2]);
	ml_vector3_mul(app->player.sideways, -dims[0], dirs[3]);
	ml_vector3_add(screen_origin, dirs[3], mouse_world_pos);
	ml_vector3_add(mouse_world_pos, dirs[0], mouse_world_pos);
	get_mouse_editor_scale(app, mouse_editor_scale);
	ml_vector3_mul(app->player.sideways,
		app->window->editor_framebuffer->width, add);
	ml_vector3_mul(add, mouse_editor_scale[0], add);
	ml_vector3_add(mouse_world_pos, add, mouse_world_pos);
	ml_vector3_mul(app->player.up,
		-app->window->editor_framebuffer->height, add);
	ml_vector3_mul(add, mouse_editor_scale[1], add);
	ml_vector3_add(mouse_world_pos, add, mouse_world_pos);
}

/*
** Return object selected by mouse (via raycasting)
*/

t_3d_object		*editor_object_by_mouse(t_doom3d *app)
{
	t_vec3			mouse_world_pos;
	t_vec3			dir;
	t_hits			*hits;
	t_hit			*closest_triangle_hit;
	t_3d_object		*hit_obj;

	hits = NULL;
	hit_obj = NULL;
	get_mouse_world_position(app, mouse_world_pos);
	ml_vector3_sub(mouse_world_pos, app->player.pos, dir);
	ml_vector3_normalize(dir, dir);
	if (l3d_kd_tree_ray_hits(app->active_scene->triangle_tree, app->player.pos,
		dir, &hits))
	{
		l3d_get_closest_triangle_hit(hits, &closest_triangle_hit, -1);
		if (closest_triangle_hit != NULL)
		{
			hit_obj = closest_triangle_hit->triangle->parent;
		}
		l3d_delete_hits(&hits);
	}
	return (hit_obj);
}

/*
** Find an offset that is half of the bounding box and return that to be applied
** for placement. (t_vec3){0.02, 0.02, 0.02} is a small vector added to aabb
** size for the case of e.g. planes (0 width)
*/

static void		editor_point_on_target_offset(t_doom3d *app,
					t_vec3 target_point, t_vec3 normal, t_vec3 offset)
{
	t_ray			ray;
	t_hits			*hits;
	t_hit			*closest;
	t_box3d			aabb;

	ml_vector3_copy(target_point, aabb.center);
	ml_vector3_copy(app->editor.selected_objects[0]->aabb.size, aabb.size);
	ml_vector3_add(aabb.size, (t_vec3){0.02, 0.02, 0.02}, aabb.size);
	ml_vector3_mul(aabb.size, 0.5, aabb.size);
	ml_vector3_add(aabb.center, aabb.size, aabb.xyz_max);
	ml_vector3_sub(aabb.center, aabb.size, aabb.xyz_min);
	ml_vector3_mul(aabb.size, 1.0, aabb.size);
	ml_vector3_normalize(normal, ray.dir);
	ml_vector3_copy((t_vec3){
		1.0 / ray.dir[0], 1.0 / ray.dir[1], 1.0 / ray.dir[2]}, ray.dir_inv);
	ml_vector3_copy(target_point, ray.origin);
	hits = NULL;
	closest = NULL;
	if (l3d_bounding_box_ray_hit(&aabb, &ray, &hits, true))
	{
		l3d_get_closest_hit(hits, &closest);
		if (closest != NULL)
			ml_vector3_sub(target_point, closest->hit_point, offset);
		l3d_delete_hits(&hits);
	}
}

/*
** Returns hit point by mouse, but ignores the currently selected one,
** Useful when e.g. placing a new object.
*/

void			editor_point_on_target(t_doom3d *app,
					t_vec3 placement_point)
{
	t_vec3			mouse_world_pos;
	t_vec3			dir;
	t_hits			*hits;
	t_hit			*closest_triangle_hit;
	t_vec3			add;

	if (app->editor.num_selected_objects == 0)
		return ;
	hits = NULL;
	get_mouse_world_position(app, mouse_world_pos);
	ml_vector3_sub(mouse_world_pos, app->player.pos, dir);
	ml_vector3_normalize(dir, dir);
	if (l3d_kd_tree_ray_hits(app->active_scene->triangle_tree, app->player.pos,
		dir, &hits))
	{
		l3d_get_closest_triangle_hit(hits, &closest_triangle_hit,
			app->editor.selected_objects[0]->id);
		if (closest_triangle_hit != NULL)
		{
			editor_point_on_target_offset(app, closest_triangle_hit->hit_point,
				closest_triangle_hit->normal, add);
			ml_vector3_add(closest_triangle_hit->hit_point,
				add, placement_point);
		}
		l3d_delete_hits(&hits);
	}
}
