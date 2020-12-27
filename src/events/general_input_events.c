/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_input_events.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:40:54 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/28 00:24:07 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		set_objects_shading_opts(t_doom3d *app, t_shading_opts opts)
{
	int32_t	i;

	i = -1;
	while (++i < (int32_t)app->active_scene->num_objects)
		l3d_object_set_shading_opts(app->active_scene->objects[i], opts);
}

static void		handle_main_game_general_keyup_events(t_doom3d *app,
					SDL_Event event)
{
	if (event.key.keysym.sym == SDLK_n)
	{
		app->is_normal_map = !app->is_normal_map;
		if (app->is_normal_map)
			set_objects_shading_opts(app,
				app->active_scene->objects[0]->material->shading_opts |
				e_shading_normal_map);
		else
			set_objects_shading_opts(app,
				app->active_scene->objects[0]->material->shading_opts ^
				e_shading_normal_map);
	}
	if (event.key.keysym.sym == SDLK_p &&
		app->active_scene->scene_id == scene_id_main_game)
	{
		app->active_scene->is_paused = !app->active_scene->is_paused;
		if (app->active_scene->is_paused)
		{
			SDL_ShowCursor(SDL_ENABLE);
			SDL_SetRelativeMouseMode(SDL_FALSE);
		}
		else
		{
			SDL_ShowCursor(SDL_DISABLE);
			SDL_SetRelativeMouseMode(SDL_TRUE);
			SDL_GetRelativeMouseState(NULL, NULL);
		}
	}
}

static void		handle_general_keyup_events(t_doom3d *app, SDL_Event event)
{
	if (app->active_scene->scene_id == scene_id_main_game)
		handle_main_game_general_keyup_events(app, event);
	if (event.key.keysym.sym == SDLK_g)
		app->is_debug = !app->is_debug;
	if (event.key.keysym.sym == SDLK_f)
	{
		app->window->is_fullscreen = !app->window->is_fullscreen;
		if (app->window->is_fullscreen)
			SDL_SetWindowFullscreen(app->window->window, SDL_WINDOW_FULLSCREEN);
		else
			SDL_SetWindowFullscreen(app->window->window, 0);
	}
}

static void		handle_editor_saving(t_doom3d *app, SDL_Event event)
{
	int32_t		length;

	if (event.type == SDL_TEXTINPUT)
	{
		app->is_saved = false;
		ft_strcat(app->editor_filename, event.text.text);
	}
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
	{
		SDL_StopTextInput();
		app->is_saving = false;
		save_map(app);
		ft_printf("Saved %s\n", app->editor_filename);
		app->is_saved = true;
	}
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE)
	{
		app->is_saved = false;
		length = ft_strlen(app->editor_filename);
		if (length > 0)
			app->editor_filename[length - 1] = '\0';
	}
}

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
	t_vec2	mouse_editor_pos;
	t_vec3	screen_origin;
	t_vec3	add;
	t_vec3	dirs[4];
	float	dims[2];

	dims[0] = app->window->framebuffer->width / 2.0;
	dims[1] = app->window->framebuffer->height / 2.0;
	ml_vector3_mul(app->player.forward,
		ml_vector3_mag(app->active_scene->main_camera->screen.origin), add);
	ml_vector3_add(app->player.pos, add, screen_origin);
	ml_vector3_mul(app->player.up, dims[1], dirs[0]);
	ml_vector3_mul(app->player.sideways, dims[0], dirs[1]);
	ml_vector3_mul(app->player.up, -dims[1], dirs[2]);
	ml_vector3_mul(app->player.sideways, -dims[0], dirs[3]);
	ml_vector3_add(screen_origin, dirs[3], mouse_world_pos);
	ml_vector3_add(mouse_world_pos, dirs[0], mouse_world_pos);
	get_mouse_editor_scale(app, mouse_editor_pos);
	ml_vector3_mul(app->player.sideways, app->window->framebuffer->width, add);
	ml_vector3_mul(add, mouse_editor_pos[0], add);
	ml_vector3_add(mouse_world_pos, add, mouse_world_pos);
	ml_vector3_mul(app->player.up, -app->window->framebuffer->height, add);
	ml_vector3_mul(add, mouse_editor_pos[1], add);
	ml_vector3_add(mouse_world_pos, add, mouse_world_pos);
}

static void		editor_select(t_doom3d *app)
{
	t_vec3			mouse_world_pos;
	t_vec3			dir;
	t_hits			*hits;
	t_hit			*closest_triangle_hit;

	hits = NULL;
	get_mouse_world_position(app, mouse_world_pos);

	ml_vector3_print(mouse_world_pos);
	ml_vector3_sub(mouse_world_pos, app->player.pos, dir);
	if (l3d_kd_tree_ray_hits(app->active_scene->triangle_tree, app->player.pos,
		dir, &hits))
	{
		l3d_get_closest_hit(hits, &closest_triangle_hit);
		if (closest_triangle_hit != NULL)
		{
			ft_printf("Select at: ");
						place_object(app, (const char*[3]){
				"assets/models/box.obj",
				NULL, NULL}, closest_triangle_hit->hit_point);
			l3d_3d_object_scale(app->active_scene->objects[
				app->active_scene->num_objects - 1], 0.1, 0.1, 0.1);
			ml_vector3_print(closest_triangle_hit->hit_point);
		}
		l3d_delete_hits(&hits);
	}
}

static void		handle_editor_selection(t_doom3d *app, SDL_Event event)
{
	if (app->is_saving)
		return ;
	if (event.type == SDL_MOUSEBUTTONDOWN &&
		(app->mouse.state & SDL_BUTTON_LMASK))
	{
		if (app->mouse.x > app->window->editor_pos[0] && app->mouse.x <
			app->window->editor_pos[0] + app->window->editor_framebuffer->width
			&&
			app->mouse.y > app->window->editor_pos[1] && app->mouse.y <
			app->window->editor_pos[1] + app->window->editor_framebuffer->height)
			editor_select(app);
	}
}

/*
** Handle events that aren't related to menus or game, like exiting or esc
** or setting to full screen, or disabling debug info
*/

void			general_input_events_handle(t_doom3d *app, SDL_Event event)
{
	if (event.type == SDL_QUIT)
		app->is_running = false;
	if (!SDL_IsTextInputActive() && !app->is_saving)
	{
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			app->is_running = false;
		if (event.type == SDL_KEYUP)
			handle_general_keyup_events(app, event);
	}
	if (app->active_scene->scene_id == scene_id_editor3d)
	{
		handle_editor_saving(app, event);
		handle_editor_selection(app, event);
	}
}
