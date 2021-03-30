/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:09:16 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/30 14:22:12 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

typedef enum				e_doom3d_event
{
	event_object_delete = 111,
	event_music_play = 222,
	event_effect_play = 333,
	event_editor_start_placement = 444,
	event_editor_end_placement = 555,
	event_editor_start_save = 1234,
	event_editor_end_save = 4321,
	event_editor_save_type = 1212,
	event_editor_save_type_backspace = 1313,
	event_editor_delete = 1414,
	event_editor_select = 1818,
	event_editor_deselect = 1919,
	event_editor_level_switch = 2020,
	event_editor_open_popup_menu = 2121,
	event_editor_close_popup_menu = 2222,
	event_editor_exit = 1515,
	event_window_resize = 666,
	event_scene_change = 777,
	event_scene_reload = 888,
	event_quit = 999,
}							t_doom3d_event;

# endif