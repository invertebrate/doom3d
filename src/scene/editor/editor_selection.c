/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_selection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 15:46:15 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/29 18:39:08 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

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

void			editor_deselect_all(t_doom3d *app)
{
	int32_t		i;
	t_3d_object	*obj;

	i = -1;
	while (++i < (int32_t)(app->editor.num_selected_objects))
	{
		obj = app->editor.selected_objects[i];
		obj->material->shading_opts = (obj->material->shading_opts &
			~(e_shading_select));
		app->editor.selected_objects[i] = NULL;
	}
	app->editor.num_selected_objects = 0;
	app->editor.selected_object_str[0] = '\0';
}

void			select_object(t_doom3d *app, t_3d_object *object)
{	
	char	object_type[128];
	int32_t	i;

	i = -1;
	while (++i < app->editor.num_selected_objects)
	{
		if (app->editor.selected_objects[i]->id == object->id)
			return ;
	}
	if (app->editor.num_selected_objects >= MAX_SELECTED_OBJECTS)
	{
		doom3d_notification_add(app, (t_notification){
			.message = "Selected max objects (64), can't select more!",
			.type = notification_type_info, .time = 2000});
		return ;
	}
	app->editor.selected_objects[app->editor.num_selected_objects++] = object;
	object->material->shading_opts |= e_shading_select;
	if (app->editor.num_selected_objects == 1)
	{
		object_type_to_str(object, object_type);
		ft_sprintf(app->editor.selected_object_str, "%s: %u", object_type,
			object->id);
	}
	else
		ft_sprintf(app->editor.selected_object_str, "multiple");
	doom3d_notification_add(app, (t_notification){.message = "Selected!",
		.type = notification_type_info, .time = 2000});
}

static void		path_connect_selection(t_doom3d *app, t_3d_object *new)
{
	t_3d_object	*old;

	old = NULL;
	if (app->editor.selected_objects[0])
		old = app->editor.selected_objects[0];
	editor_deselect_all(app);
	select_object(app, new);
	if (old->type == object_type_path && new->type == object_type_path)
		path_objects_set_neighbour(app, old);
	if (old->type == object_type_npc && new->type == object_type_path)
		patrol_path_link_node(new, old, app->editor.patrol_slot);
	if (old->type == object_type_trigger && new->type == object_type_npc)
		trigger_link_object_to_npc(old, new);
	if ((!old && new->type == object_type_trigger) || new == old)
		trigger_update_key_id(app, new);
}

/*
** Cast ray from player to mouse world position (on screen)
** and see which closest triangle intersects.
** Add hit object to selected object.
*/

void			editor_select(t_doom3d *app)
{
	t_vec3			mouse_world_pos;
	t_vec3			dir;
	t_hits			*hits;
	t_hit			*closest_triangle_hit;

	hits = NULL;
	get_mouse_world_position(app, mouse_world_pos);
	ml_vector3_sub(mouse_world_pos, app->player.pos, dir);
	ml_vector3_normalize(dir, dir);
	if (l3d_kd_tree_ray_hits(app->active_scene->triangle_tree, app->player.pos,
		dir, &hits))
	{
		l3d_get_closest_hit(hits, &closest_triangle_hit, -1);
		if (closest_triangle_hit != NULL)
		{
			if (app->keyboard.state[SDL_SCANCODE_LCTRL])
				path_connect_selection(app, closest_triangle_hit->triangle->parent);
			else if (app->keyboard.state[SDL_SCANCODE_LSHIFT])
				select_object(app, closest_triangle_hit->triangle->parent);
			else
			{
				editor_deselect_all(app);
				select_object(app, closest_triangle_hit->triangle->parent);
			}
		}
		l3d_delete_hits(&hits);
	}
}

static void		deselect_one(t_doom3d *app, t_3d_object *hit_obj)
{
	t_3d_object		*selected_objects[MAX_SELECTED_OBJECTS];
	int32_t			i;
	int32_t			j;

	i = -1;
	j = 0;
	while (++i < app->editor.num_selected_objects)
	{
		if (hit_obj->id != selected_objects[i]->id)
		{
			selected_objects[j] = app->editor.selected_objects[i];
			j++;
		}
	}
	app->editor.num_selected_objects = j;
	j = -1;
	while (++j < app->editor.num_selected_objects)
	{
		app->editor.selected_objects[j] = selected_objects[j];
	}
}

void			editor_deselect(t_doom3d *app)
{
	t_vec3			mouse_world_pos;
	t_vec3			dir;
	t_hits			*hits;
	t_hit			*closest_triangle_hit;

	hits = NULL;
	get_mouse_world_position(app, mouse_world_pos);
	ml_vector3_sub(mouse_world_pos, app->player.pos, dir);
	ml_vector3_normalize(dir, dir);
	if (l3d_kd_tree_ray_hits(app->active_scene->triangle_tree, app->player.pos,
		dir, &hits))
	{
		l3d_get_closest_hit(hits, &closest_triangle_hit, -1);
		if (closest_triangle_hit != NULL)
			deselect_one(app, closest_triangle_hit->triangle->parent);
		l3d_delete_hits(&hits);
	}
	else
	{
		if (app->editor.num_selected_objects > 0)
			doom3d_notification_add(app, (t_notification){
			.message = "Deselected all!",
			.type = notification_type_info, .time = 2000});
		editor_deselect_all(app);
	}
}

void			editor_place_position(t_doom3d *app , t_vec3 result)
{
	t_vec3	add;

	ml_vector3_mul(app->player.forward, app->unit_size * 30, add);
	ml_vector3_add(app->player.pos, add, result);
}
