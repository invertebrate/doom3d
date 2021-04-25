/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_triangle_utils2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 23:53:18 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/25 15:44:34 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Adds those triangles that are inside viewbox (not culled) and close enough
** to the renderable triangles (after clipping of course)
*/

static void				add_to_render_triangles_if_should(t_doom3d *app,
							t_tri_vec **render_triangles, t_triangle *triangle,
							t_triangle *renderable_triangle)
{
	t_vertex				vtc[3];

	if (triangle_too_far(app, triangle) ||
		!triangle_inside_viewbox(app, triangle))
		return ;
	prepare_render_triangle(app, renderable_triangle, triangle, vtc);
	if (is_rendered(app, renderable_triangle))
		clip_and_add_to_render_triangles(app,
			render_triangles, renderable_triangle);
}

/*
** Adds temporary object (limited lifetime)
** render triangles to renderable triangle vector
*/

void					add_temp_object_render_triangles(t_doom3d *app,
							t_tri_vec **render_triangles)
{
	t_temp_object			*tmp;
	t_temp_objects			*node;
	t_triangle				*triangle;
	t_triangle				r_triangle;
	int32_t					i;

	node = app->active_scene->temp_objects;
	while (node)
	{
		tmp = node->content;
		if (!object_too_far(app, tmp->obj) &&
			object_inside_viewbox(app, tmp->obj))
		{
			i = -1;
			while (++i < tmp->obj->num_triangles)
			{
				triangle = tmp->obj->triangles + i;
				add_to_render_triangles_if_should(app, render_triangles,
					triangle, &r_triangle);
			}
		}
		node = node->next;
	}
}

/*
** Gets the current render target triangle. If the object is animated, the
** triangle will be accessed from the animation 3d object frame rather than
** the original object.
*/

static t_triangle		*get_render_target_triangle(t_doom3d *app,
							t_3d_object *obj, int32_t triangle_index)
{
	t_3d_object	*current_anim_obj;
	t_triangle	*triangle;

	if (app->active_scene->scene_id != scene_id_editor3d &&
		obj->type == object_type_npc &&
		((t_npc*)obj->params)->animation_3d != NULL)
	{
		current_anim_obj = ((t_npc*)obj->params)->animation_3d->current_object;
		error_check(current_anim_obj->num_triangles != obj->num_triangles,
			"Frame object triangle count different from "
			"base object triangle count!");
		triangle = ((t_npc*)obj->params)->
					animation_3d->current_object->triangles + triangle_index;
	}
	else
		triangle = obj->triangles + triangle_index;
	return (triangle);
}

/*
** Adds object triangles to renderable triangles for objects that are in view
** of the camera
*/

void					add_objects_render_triangles(t_doom3d *app,
							t_tri_vec **render_triangles)
{
	int32_t					i;
	int32_t					j;
	t_triangle				*triangle;
	t_triangle				r_triangle;

	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted))
	{
		if ((app->active_scene->objects[i] == NULL) ||
			object_too_far(app, app->active_scene->objects[i]) ||
			!object_inside_viewbox(app, app->active_scene->objects[i]))
			continue ;
		j = -1;
		while (++j < app->active_scene->objects[i]->num_triangles)
		{
			triangle = get_render_target_triangle(app,
				app->active_scene->objects[i], j);
			add_to_render_triangles_if_should(app, render_triangles,
					triangle, &r_triangle);
		}
	}
}

/*
** Adds skybox render triangles to renderable triangle vector
*/

void					add_skybox_render_triangles(t_doom3d *app,
							t_tri_vec **render_triangles)
{
	int					i;
	int					j;
	t_triangle			r_triangle;
	t_vertex			vtc[3];

	i = -1;
	while (++i < 6 && app->active_scene->skybox[i])
	{
		j = -1;
		while (++j < app->active_scene->skybox[i]->num_triangles)
		{
			prepare_skybox_render_triangle(app, &r_triangle,
				app->active_scene->skybox[i]->triangles + j, vtc);
			if (is_rendered(app, &r_triangle))
				clip_and_add_to_render_triangles(app,
					render_triangles, &r_triangle);
		}
	}
}
