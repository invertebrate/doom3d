/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_custom_events.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sotamursu <sotamursu@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 01:50:28 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/05 15:52:02 by sotamursu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	register_editor_custom_events_sub1(t_doom3d *app)
{
	hash_map_add(app->custom_event_handles, event_editor_start_placement,
		(void *)handle_editor_placement_start);
	hash_map_add(app->custom_event_handles, event_editor_end_placement,
		(void *)handle_editor_placement_end);
	hash_map_add(app->custom_event_handles, event_editor_cancel_placement,
		(void *)handle_editor_placement_cancel);
	hash_map_add(app->custom_event_handles, event_editor_start_save,
		(void *)handle_editor_save_start);
	hash_map_add(app->custom_event_handles, event_editor_end_save,
		(void *)handle_editor_save_end);
	hash_map_add(app->custom_event_handles, event_editor_save_type,
		(void *)handle_editor_save_type);
	hash_map_add(app->custom_event_handles, event_editor_save_type_backspace,
		(void *)handle_editor_save_type_backspace);
	hash_map_add(app->custom_event_handles, event_editor_snap_to_grid,
		(void *)handle_editor_snap_to_grid);
	hash_map_add(app->custom_event_handles, event_editor_in_placement_move,
		(void *)handle_editor_in_placement_move);
	hash_map_add(app->custom_event_handles, event_editor_duplicate,
		(void *)handle_editor_duplication);
	hash_map_add(app->custom_event_handles, event_editor_zoom,
		(void *)handle_editor_zoom);
}

static void	register_editor_custom_events_sub2(t_doom3d *app)
{
	hash_map_add(app->custom_event_handles, event_editor_move_view_forward,
		(void *)handle_editor_move_view_forward);
	hash_map_add(app->custom_event_handles, event_editor_move_view_sideways,
		(void *)handle_editor_move_view_sideways);
	hash_map_add(app->custom_event_handles, event_editor_rotate_view,
		(void *)handle_editor_rotate_view);
	hash_map_add(app->custom_event_handles, event_editor_flip_lights,
		(void *)handle_editor_flip_lights);
}

/*
** Register all custom events that correspond to an action in app and their
** respecting handle functions
*/

void	register_editor_custom_events(t_doom3d *app)
{
	register_editor_custom_events_sub1(app);
	register_editor_custom_events_sub2(app);
	hash_map_add(app->custom_event_handles, event_editor_delete,
		(void *)handle_editor_delete);
	hash_map_add(app->custom_event_handles, event_editor_exit,
		(void *)handle_editor_exit);
	hash_map_add(app->custom_event_handles, event_editor_select,
		(void *)handle_editor_select);
	hash_map_add(app->custom_event_handles, event_editor_deselect,
		(void *)handle_editor_deselect);
	hash_map_add(app->custom_event_handles, event_editor_level_switch,
		(void *)handle_editor_level_switch);
	hash_map_add(app->custom_event_handles, event_editor_open_popup_menu,
		(void *)handle_editor_open_popup_menu);
	hash_map_add(app->custom_event_handles, event_editor_add_texture,
		(void *)handle_editor_add_texture);
	hash_map_add(app->custom_event_handles, event_editor_add_normal_map,
		(void *)handle_editor_add_normal_map);
	hash_map_add(app->custom_event_handles, event_editor_increment_patrol_slot,
		(void *)handle_editor_patrol_slot_increment);
	hash_map_add(app->custom_event_handles, event_editor_decrement_patrol_slot,
		(void *)handle_editor_patrol_slot_decrement);
	hash_map_add(app->custom_event_handles, event_editor_toggle_lock_vertical,
		(void *)handle_editor_toggle_vertical_lock);
}
