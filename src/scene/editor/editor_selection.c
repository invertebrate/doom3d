/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_selection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 15:46:15 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/13 14:12:54 by ohakola          ###   ########.fr       */
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

void			editor_deselect(t_doom3d *app)
{
	if (app->editor.selected_object)
	{
		app->editor.selected_object->material->shading_opts =
			(app->editor.selected_object->material->shading_opts &
				~e_shading_select);
	}
	app->editor.selected_object = NULL;
	app->editor.selected_object_str[0] = '\0';
}

void			editor_deselect_all(t_doom3d *app)
{
	int32_t	i;

	editor_deselect(app);
	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted))
	{
		if (app->active_scene->objects[i] == NULL)
			continue ;
		app->active_scene->objects[i]->material->shading_opts =
			(app->active_scene->objects[i]->material->shading_opts &
				~(e_shading_select));
	}
}

static void		select_object(t_doom3d *app, t_3d_object *object)
{	
	char	object_type[128];

	app->editor.selected_object = object;
	app->editor.selected_object->material->shading_opts |=
		e_shading_select;
	object_type_to_str(object, object_type);
	ft_sprintf(app->editor.selected_object_str, "%s: %u", object_type,
		object->id);
	doom3d_notification_add(app, (t_notification){
			.message = "Selected!",
			.type = notification_type_info, .time = 2000});
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
		l3d_get_closest_hit(hits, &closest_triangle_hit);
		if (closest_triangle_hit != NULL)
		{
			editor_deselect(app);
			select_object(app, closest_triangle_hit->triangle->parent);
		}
		l3d_delete_hits(&hits);
	}
	else
	{
		if (app->editor.selected_object)
			doom3d_notification_add(app, (t_notification){
			.message = "Deselected!",
			.type = notification_type_info, .time = 2000});
		editor_deselect(app);
	}
}
