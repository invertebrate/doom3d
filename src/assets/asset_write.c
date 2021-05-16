/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asset_write.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/15 22:10:50 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/17 00:56:12 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	write_3d_model_fd(int32_t fd, t_3d_object *obj)
{
	const char		*texture_file;
	const char		*normal_map_file;
	int32_t			len;
	int32_t			ret;
	int32_t			i;

	ret = write(fd, obj, sizeof(t_3d_object));
	i = -1;
	while (++i < (int32_t)obj->num_vertices)
		ret = write(fd, obj->vertices[i], sizeof(t_vertex));
	i = -1;
	while (++i < (int32_t)obj->num_triangles)
		ret = write(fd, &obj->triangles[i], sizeof(t_triangle));
	texture_file = NULL;
	if (obj->material->texture)
		texture_file = obj->material->texture->filename;
	normal_map_file = NULL;
	if (obj->material->normal_map)
		normal_map_file =  obj->material->normal_map->filename;
	len = ft_strlen(texture_file);
	ret = write(fd, &len, sizeof(uint32_t));
	ret = write(fd, texture_file, len);
	len = ft_strlen(normal_map_file);
	ret = write(fd, &len, sizeof(uint32_t));
	ret = write(fd, normal_map_file, len);
	(void)ret;
}

static void	write_3d_model(int64_t key, void *val,
				void *params1, void *params2)
{
	t_3d_object		*obj;
	t_doom3d		*app;
	int32_t			*fd_ptr;
	int32_t			fd;

	(void)key;
	fd_ptr = params1;
	fd = *fd_ptr;
	obj = val;
	app = params2;
	write_3d_model_fd(fd, obj);
}

/*
** Filename len + Filename size + surface struct + pixels
*/

static void	write_surface(int64_t key, void *val,
				void *params1, void *params2)
{
	t_surface		*surface;
	int32_t			ret;
	int32_t			*fd_ptr;
	int32_t			fd;
	uint32_t		len;

	(void)params2;
	fd_ptr = params1;
	fd = *fd_ptr;
	surface = val;
	if (key)
	{
		len = ft_strlen((char *)key);
		ret = write(fd, &len, sizeof(uint32_t));
		ret = write(fd, (char *)key, len);
	}
	ret = write(fd, surface, sizeof(t_surface));
	ret = write(fd, surface->pixels,
		sizeof(uint32_t) * surface->w * surface->h);
	(void)ret;
}

static void	write_asset_maps(int32_t fd, t_doom3d *app)
{
	t_assets	*assets;
	uint32_t	count;
	int32_t		ret;

	assets = &app->assets;
	count = hash_map_get_count(assets->sprite_textures);
	ret = write(fd, &count, sizeof(uint32_t));
	hash_map_foreach(assets->sprite_textures, write_surface, &fd, NULL);
	count = hash_map_get_count(assets->hud_textures);
	ret = write(fd, &count, sizeof(uint32_t));
	hash_map_foreach(assets->hud_textures, write_surface, &fd, NULL);
	count = hash_map_get_count(assets->textures);
	ret = write(fd, &count, sizeof(uint32_t));
	hash_map_foreach(assets->textures, write_surface, &fd, NULL);
	count = hash_map_get_count(assets->normal_maps);
	ret = write(fd, &count, sizeof(uint32_t));
	hash_map_foreach(assets->normal_maps, write_surface, &fd, NULL);
	count = hash_map_get_count(assets->models);
	ret = write(fd, &count, sizeof(uint32_t));
	hash_map_foreach(assets->models, write_3d_model, &fd, NULL);
	count = hash_map_get_count(assets->animation_3d_frames);
	ret = write(fd, &count, sizeof(uint32_t));
	hash_map_foreach(assets->animation_3d_frames, write_3d_model, &fd, NULL);
	(void)ret;
}

/*
** 1. Skybox, its filename lengths and filenames, we know there's 6
** 2. Num sprites + Sprite textures, its filename lengths and filenames
** 3. Num Hud textures + Hud textures, its filename lengths and filenames
** 4. Num Textures + Textures, its filename lengths and filenames
** 5. Num Nmaps + Normal maps, its filename lengths and filenames
** 6. Num Models + 3d model, its filename lengths and filenames
** 7. Num Frames + Animation 3d frames, its filename lengths and filenames
** 8. Track lengts and their lengths and their content sizes, we know there's
** exactly SOUNDS_NUM_TRACKS
** 9. Three fonts and their lengths and content sizes, we know there's 3
*/

void	write_assets(int32_t fd, t_doom3d *app)
{
	uint32_t	assets_write_size;
	t_assets	*assets;
	// uint32_t	i;
	// int32_t		ret;

	(void)fd;
	(void)write_asset_maps;
	assets = &app->assets;
	assets_write_size = get_assets_write_size(app);
	LOG_WARN("Writing assets of size: %llu bytes", assets_write_size);
	// ret = write(fd, "ASSETS\0", 7);
	// i = -1;
	// while (++i < 6)
	// 	write_surface(0, assets->skybox_textures[i], &fd, NULL);
	// write_asset_maps(fd, app);
	// write_sdl_assets(fd, assets);
}
