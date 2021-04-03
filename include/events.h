/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:09:16 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/04 00:31:42 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

typedef enum				e_doom3d_event
{
	event_object_delete = 1,
	event_music_play = 2,
	event_effect_play = 3,
	event_editor_start_placement = 4,
	event_editor_cancel_placement = 5,
	event_editor_end_placement = 6,
	event_editor_start_save = 7,
	event_editor_end_save = 8,
	event_editor_save_type = 9,
	event_editor_save_type_backspace = 10,
	event_editor_delete = 11,
	event_editor_select = 12,
	event_editor_deselect = 13,
	event_editor_level_switch = 14,
	event_editor_open_popup_menu = 15,
	event_editor_add_texture = 16,
	event_editor_add_normal_map = 17,
	event_editor_increment_patrol_slot = 18,
	event_editor_decrement_patrol_slot = 19,
	event_editor_exit = 20,
	event_window_resize = 21,
	event_scene_change = 22,
	event_scene_reload = 23,
	event_editor_snap_to_grid = 24,
	event_quit = 25,
}							t_doom3d_event;

# endif