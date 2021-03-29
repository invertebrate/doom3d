/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 15:09:16 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/29 17:41:26 by ohakola          ###   ########.fr       */
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
	event_window_resize = 666,
	event_scene_change = 777,
	event_quit = 999,
}							t_doom3d_event;

# endif