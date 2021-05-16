/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asset_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 20:23:59 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/16 23:21:11 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static uint32_t	get_3d_obj_size(t_3d_object *obj)
{
	uint32_t	size_count;

	size_count = 0;
	size_count += obj->num_vertices * sizeof(t_vertex);
	size_count += obj->num_triangles * sizeof(t_triangle);
	size_count += sizeof(t_material);
	size_count += sizeof(t_3d_object);
	return (size_count);
}

/*
** Filename len + Filename size + surface struct + pixels
*/

static void	add_surface_size(int64_t key, void *val,
				void *params1, void *params2)
{
	t_surface		*surface;
	uint32_t		*size_counter;

	size_counter = params1;
	(void)params2;
	surface = val;
	if (key)
	{
		*size_counter += sizeof(uint32_t);
		*size_counter += ft_strlen((char *)key);
	}
	*size_counter += sizeof(t_surface);
	*size_counter += sizeof(uint32_t) * surface->w * surface->h;
}

static uint32_t	get_3d_obj_textures_write_size(t_doom3d *app, t_3d_object *obj)
{
	char			*texture_file;
	char			*normal_map_file;
	uint32_t		size_count;

	size_count = 0;
	size_count += sizeof(uint32_t) * 2;
	texture_file = get_object_texture_filename(app->active_scene, obj);
	normal_map_file = get_object_normal_map_filename(app->active_scene, obj);
	size_count += ft_strlen(texture_file);
	size_count += ft_strlen(normal_map_file);
	return (size_count);
}

/*
** Filename len + Filename size + obj size + texture filename len + size
** + normal map filename len + size
*/

static void	add_3d_animation_frame_size(int64_t key, void *val,
				void *params1, void *params2)
{
	t_3d_object		*obj;
	uint32_t		*size_counter;
	t_doom3d		*app;

	size_counter = params1;
	app = params2;
	obj = val;
	*size_counter += sizeof(uint32_t);
	*size_counter += ft_strlen((char *)key);
	*size_counter += get_3d_obj_textures_write_size(app, obj);
	*size_counter += get_3d_obj_size(obj);
}

/*
** 1. Skybox, its filename lengths and filenames, we know there's 6
** 2. Num sprites + Sprite textures, its filename lengths and filenames
** 3. Num Hud textures + Hud textures, its filename lengths and filenames
** 4. Num Textures + Textures, its filename lengths and filenames
** 5. Num Nmaps + Normal maps, its filename lengths and filenames
** 6. Num Frames + Animation 3d frames, its filename lengths and filenames
** 7. Track lengts and their lengths and their content sizes, we know there's
** exactly SOUNDS_NUM_TRACKS
** 8. Three fonts and their lengths and content sizes, we know there's 3
*/

uint32_t	get_assets_write_size(t_doom3d *app)
{
	t_assets	*assets;
	uint32_t	size_count;
	uint32_t	i;

	assets = &app->assets;
	size_count = ft_strlen("ASSETS");
	i = -1;
	while (++i < 6)
		add_surface_size(0, assets->skybox_textures[i], &size_count, NULL);
	size_count += sizeof(uint32_t);
	hash_map_foreach(assets->sprite_textures, add_surface_size,
		&size_count, NULL);
	size_count += sizeof(uint32_t);
	hash_map_foreach(assets->hud_textures, add_surface_size, &size_count, NULL);
	size_count += sizeof(uint32_t);
	hash_map_foreach(assets->textures, add_surface_size, &size_count, NULL);
	size_count += sizeof(uint32_t);
	hash_map_foreach(assets->normal_maps, add_surface_size, &size_count, NULL);
	size_count += sizeof(uint32_t);
	hash_map_foreach(assets->animation_3d_frames,
		add_3d_animation_frame_size, &size_count, app);
	size_count += get_sdl_assets_write_size(assets);
	return (size_count);
}
