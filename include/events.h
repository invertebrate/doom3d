/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:09:16 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/18 18:26:06 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

typedef enum				e_doom3d_event
{
	event_music_play = 1,
	event_effect_play = 2,
	event_editor_start_placement = 3,
	event_editor_cancel_placement = 4,
	event_editor_end_placement = 5,
	event_editor_in_placement_move = 6,
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
	event_editor_snap_to_grid = 21,
	event_editor_duplicate = 22,
	event_editor_move_view_forward = 23,
	event_editor_move_view_sideways = 24,
	event_editor_rotate_view = 25,
	event_editor_zoom = 26,
	event_editor_toggle_lock_vertical = 200,
	event_player_rotate = 27,
	event_player_shoot = 28,
	event_player_reload = 29,
	event_player_crouch = 30,
	event_player_weapon_equip = 31,
	event_player_move = 32,
	event_player_jump = 33,
	event_player_toggle_flight = 34,
	event_object_delete = 35,
	event_object_scale = 36,
	event_object_scale_with_uvs = 361,
	event_object_translate_x = 37,
	event_object_translate_y = 38,
	event_object_translate_z = 39,
	event_object_rotate_x = 40,
	event_object_rotate_y = 41,
	event_object_rotate_z = 42,
	event_toggle_fullscreen = 43,
	event_toggle_debug_mode = 44,
	event_toggle_pause_game = 45,
	event_toggle_normal_map_mode = 46,
	event_window_resize = 47,
	event_scene_change = 48,
	event_scene_reload = 49,
	event_quit = 99,
}							t_doom3d_event;

# endif