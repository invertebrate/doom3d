/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 12:34:54 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/19 23:25:40 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

int64_t	get_matching_3d_anim_key(t_doom3d *app, const char *filename)
{
	int32_t	i;

	if (filename == NULL)
		return (0);
	i = -1;
	while (++i < (int32_t)app->assets.asset_files.num_animation_frames_3d)
		if (ft_strequ(app->assets.asset_files.animation_3d_files[i], filename))
			return ((int64_t)app->assets.asset_files.animation_3d_files[i]);
	return (0);
}

int64_t	get_matching_model_key(t_doom3d *app, const char *filename)
{
	int32_t	i;

	if (filename == NULL)
		return (0);
	i = -1;
	while (++i < (int32_t)app->assets.asset_files.num_models)
		if (ft_strequ(app->assets.asset_files.model_files[i], filename))
			return ((int64_t)app->assets.asset_files.model_files[i]);
	return (0);
}

int64_t	get_matching_surface_key(t_doom3d *app, const char *filename)
{
	int32_t	i;

	if (filename == NULL)
		return (0);
	i = -1;
	while (++i < (int32_t)app->assets.asset_files.num_sprites)
		if (ft_strequ(app->assets.asset_files.sprite_files[i], filename))
			return ((int64_t)app->assets.asset_files.sprite_files[i]);
	i = -1;
	while (++i < (int32_t)app->assets.asset_files.num_hud_textures)
		if (ft_strequ(app->assets.asset_files.hud_textures[i], filename))
			return ((int64_t)app->assets.asset_files.hud_textures[i]);
	i = -1;
	while (++i < (int32_t)app->assets.asset_files.num_textures)
		if (ft_strequ(app->assets.asset_files.texture_files[i], filename))
			return ((int64_t)app->assets.asset_files.texture_files[i]);
	i = -1;
	while (++i < (int32_t)app->assets.asset_files.num_normal_maps)
		if (ft_strequ(app->assets.asset_files.normal_map_files[i], filename))
			return ((int64_t)app->assets.asset_files.normal_map_files[i]);
	return (0);
}
