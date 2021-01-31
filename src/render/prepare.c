/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2021/01/20 21:47:55 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static t_bool	object_too_far(t_doom3d *app, t_3d_object *obj)
{
	float		too_far;
	t_vec3		player_to_obj;

	if (app->active_scene->scene_id == scene_id_main_game)
		too_far = app->unit_size * 50;
	else
		too_far = app->unit_size * 500;
	ml_vector3_sub(obj->position, app->player.pos,
		player_to_obj);
	if (ml_vector3_mag(player_to_obj) > too_far)
		return (true);
	return (false);
}

static void		add_temp_object_render_triangles(t_doom3d *app,
					t_tri_vec *render_triangles)
{
	t_temp_object 			*tmp;
	t_temp_objects			*node;
	t_triangle				*triangle;
	t_triangle				r_triangle;
	t_vertex				vtc[3];
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
				if (triangle_too_far(app, triangle) ||
					!triangle_inside_viewbox(app, triangle))
					continue ;
				prepare_render_triangle(app, &r_triangle, triangle, vtc);
				if (is_rendered(app, &r_triangle))
					clip_and_add_to_render_triangles(app,
						render_triangles, &r_triangle);
			}
		}
		node = node->next;
	}
}

/*
** The checks inside this function optimize the amount of triangles
** prepared for rendering.
*/

static void		add_objects_render_triangles(t_doom3d *app,
					t_tri_vec *render_triangles)
{
	int32_t					i;
	int32_t					j;
	t_triangle				*triangle;
	t_triangle				r_triangle;
	t_vertex				vtc[3];
	triangle = &r_triangle;
	i = -1;
	while (++i < (int32_t)(app->active_scene->num_objects +
		app->active_scene->num_deleted))
	{
		if ((app->active_scene->objects[i] == NULL) ||
			object_too_far(app, app->active_scene->objects[i]) ||
			!object_inside_viewbox(app, app->active_scene->objects[i]))
			continue ;
		if (app->active_scene->objects[i]->type == object_type_npc)
		{
			update_current_frame(app, ((t_npc*)app->active_scene->objects[i]->params)->animation_3d);
		}
		j = -1;
		while (++j < app->active_scene->objects[i]->num_triangles)
		{
			if (app->active_scene->objects[i]->type == object_type_npc)
			//^this could be more elegant as in to take into account multiple types
				{
				//^only for testing, animation controller should handle this
				triangle = get_animation_3d_triangle(app->active_scene->objects[i]) + j;
				}
			else
				triangle = app->active_scene->objects[i]->triangles + j;
			if (triangle_too_far(app, triangle)	 ||
				!triangle_inside_viewbox(app, triangle))
				continue ;
			prepare_render_triangle(app, &r_triangle, triangle, vtc);
			if (is_rendered(app, &r_triangle))
				clip_and_add_to_render_triangles(app,
					render_triangles, &r_triangle);
		}
	}
	add_temp_object_render_triangles(app, render_triangles);
}

static void		add_skybox_render_triangles(t_doom3d *app,
					t_tri_vec *render_triangles)
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

void			destroy_render_triangles(t_tri_vec *render_triangles)
{
	int32_t		i;

	i = -1;
	while (++i < (int32_t)render_triangles->size)
	{
		l3d_triangle_destroy(render_triangles->triangles[i], true);
	}
	l3d_triangle_vec_delete(render_triangles);
}

/*
** Prepares triangles for parallel rendering
*/

t_tri_vec		*prepare_render_triangles(t_doom3d *app)
{
	t_tri_vec			*render_triangles;

	render_triangles =
		l3d_triangle_vec_with_capacity(app->active_scene->num_triangles + 12);
	if (app->active_scene->scene_id != scene_id_editor3d)
		add_skybox_render_triangles(app, render_triangles);
	add_objects_render_triangles(app, render_triangles);
	return (render_triangles);
}
