/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   models.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 13:11:42 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/19 14:19:02 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static t_3d_object	*read_3d_obj(t_file_contents *file, int32_t *offset,
						char filename[128])
{
	t_3d_object	*obj;
	uint32_t	len;

	len = 0;
	ft_memcpy(&len, file->buf + *offset, sizeof(uint32_t));
	*offset += sizeof(uint32_t);
	ft_memcpy(filename, file->buf + *offset, len);
	*offset += len;
	error_check(!(obj = l3d_3d_object_shallow_copy((t_3d_object *)(file->buf
					+ *offset))), "E: read object from map byte offset");
	*offset += sizeof(t_3d_object);
	*offset = read_object_triangles_and_vertices(file->buf, obj, *offset);
	l3d_3d_object_triangle_copy_and_set(obj, obj);
	return (obj);
}

static uint32_t	read_and_add_model_asset(t_doom3d *app, t_hash_table *asset_map,
					t_file_contents *file, int32_t offset)
{
	t_3d_object	*obj;
	t_3d_object	*existing_obj;
	char		filename[128];
	const char	*matching_filename;

	ft_memset(filename, 0, sizeof(filename));
	obj = read_3d_obj(file, &offset, filename);
	matching_filename = (const char *)get_matching_asset_key(app, filename);
	if (ft_strlen(filename) == 0 || matching_filename == NULL)
		l3d_3d_object_destroy(obj);
	else
	{
		existing_obj = hash_map_get(asset_map, (int64_t)matching_filename);
		if (existing_obj != NULL)
			l3d_3d_object_destroy(existing_obj);
		hash_map_add(asset_map, (int64_t)matching_filename, existing_obj);
	}
	return (offset);
}

uint32_t	read_model_assets(t_doom3d *app,
				t_file_contents *file, int32_t offset)
{
	int32_t	i;
	int32_t	num_written_assets;

	num_written_assets = 0;
	ft_memcpy(&num_written_assets, file->buf + offset, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	i = -1;
	while (++i < num_written_assets)
		offset = read_and_add_model_asset(app,
				app->assets.models, file, offset);
	ft_memcpy(&num_written_assets, file->buf + offset, sizeof(uint32_t));
	offset += sizeof(uint32_t);
	i = -1;
	while (++i < num_written_assets)
		offset = read_and_add_model_asset(app,
				app->assets.animation_3d_frames, file, offset);
	return (offset);
}
