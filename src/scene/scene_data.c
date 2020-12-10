/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 23:22:26 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/10 14:21:37 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void		scene_main_game_data_set(t_scene_data *data)
{
	data->menu_options[0] = "Main Menu";
	data->menu_options[1] = "Exit Game";
	data->menu_option_count = 2;
	data->main_camera = new_camera();
	data->map_filename = ft_strdup("maps/level1");
	main_scene_data_asset_files_set(data);
}

void		scene_main_menu_data_set(t_scene_data *data)
{
	data->menu_options[0] = "Start Game";
	data->menu_options[1] = "Settings";
	data->menu_options[2] = "Quit";
	data->menu_option_count = 3;
}

void		scene_settings_menu_data_set(t_scene_data *data)
{
	data->menu_options[0] = "960x540";
	data->menu_options[1] = "1280x720";
	data->menu_options[2] = "1920x1080";
	data->menu_options[3] = "Back";
	data->menu_option_count = 4;
}
