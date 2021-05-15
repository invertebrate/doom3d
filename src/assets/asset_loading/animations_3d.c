/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations_3d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 18:53:21 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/15 20:39:39 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
**	Creates the file path for each frame in an animation clip
*/

static void	scene_animation_3d_frames_set(t_asset_files *data,
					char *file_path, uint32_t framecount)
{
	int		i;
	char	*frame_path;

	i = -1;
	while (++i < (int)framecount && i < 100)
	{
		frame_path = (char *)ft_calloc(sizeof(char)
				* ft_strlen(file_path) + 16);
		if (i < 10)
		{
			ft_sprintf(frame_path, "%s_00%d.obj", file_path, i);
		}
		else if (i >= 10 && i < 100)
		{
			ft_sprintf(frame_path, "%s_0%d.obj", file_path, i);
		}
		data->animation_3d_files[data->num_animation_frames_3d++] = frame_path;
	}
}

/*
** The file path must not include the ".obj", it will be appended by
** animation_frames_set function. The function call order is important:
** each object has their animations in a contiguous chunk in the array.
*/

void	animation_3d_files_set(t_asset_files *data)
{
	scene_animation_3d_frames_set(data,
		"assets/models/monster_01/monster01_basemodel", 1);
	scene_animation_3d_frames_set(data,
		"assets/models/monster_01/idle/monster01_idle", 65);
	scene_animation_3d_frames_set(data,
		"assets/models/monster_01/move/monster01_move", 13);
	scene_animation_3d_frames_set(data,
		"assets/models/monster_01/attack/monster01_attack", 17);
	scene_animation_3d_frames_set(data,
		"assets/models/monster_01/death/monster01_death", 49);
	scene_animation_3d_frames_set(data,
		"assets/models/monster_02/monster02_basemodel", 1);
	scene_animation_3d_frames_set(data,
		"assets/models/monster_02/idle/monster02_idle", 59);
	scene_animation_3d_frames_set(data,
		"assets/models/monster_02/move/monster02_move", 20);
	scene_animation_3d_frames_set(data,
		"assets/models/monster_02/attack/monster02_attack", 12);
	scene_animation_3d_frames_set(data,
		"assets/models/monster_02/death/monster02_death", 32);
}

void	load_animation_3d_frames_to_memory(t_assets *assets,
					t_asset_files *data)
{
	int		i;

	i = -1;
	while (++i < (int32_t)data->num_animation_frames_3d)
		hash_map_add(assets->animation_3d_frames,
			(int64_t)assets->asset_files.animation_3d_files[i],
			l3d_read_obj(assets->asset_files.animation_3d_files[i],
			NULL, NULL));
}
