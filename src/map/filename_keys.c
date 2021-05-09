/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 01:24:14 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/04 18:42:42 by sotamursu        ###   ########.fr       */
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

char	*get_object_texture_filename(t_scene *scene, t_3d_object *obj)
{
	return (hash_map_get(scene->object_textures, obj->id));
}

char	*get_object_normal_map_filename(t_scene *scene, t_3d_object *obj)
{
	return (hash_map_get(scene->object_normal_maps, obj->id));
}
