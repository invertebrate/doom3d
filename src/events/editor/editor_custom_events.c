/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_custom_events.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 01:50:28 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/05 00:47:25 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	editor_event_to_str_sub(char *str, t_doom3d_event code)
{
	if (code == event_editor_start_placement)
		ft_sprintf(str, "EditorStartPlacement");
	else if (code == event_editor_end_placement)
		ft_sprintf(str, "EditorEndPlacement");
	else if (code == event_editor_cancel_placement)
		ft_sprintf(str, "EditorCancelPlacement");
	else if (code == event_editor_start_save)
		ft_sprintf(str, "EditorStartSave");
	else if (code == event_editor_end_save)
		ft_sprintf(str, "EditorEndSave");
	else if (code == event_editor_save_type)
		ft_sprintf(str, "EditorType");
	else if (code == event_editor_save_type_backspace)
		ft_sprintf(str, "EditorTypeBackspace");
	else if (code == event_editor_exit)
		ft_sprintf(str, "EditorExit");
	else if (code == event_editor_snap_to_grid)
		ft_sprintf(str, "EditorSnapToGrid");
}

void		editor_custom_event_to_str(char *str, t_doom3d_event code)
{
	editor_event_to_str_sub(str, code);
	if (code == event_editor_add_texture)
		ft_sprintf(str, "EditorAddTexture");
	else if (code == event_editor_add_normal_map)
		ft_sprintf(str, "EditorAddNormalMap");
	else if (code == event_editor_delete)
		ft_sprintf(str, "EditorDelete");
	else if (code == event_editor_select)
		ft_sprintf(str, "EditorSelect");
	else if (code == event_editor_deselect)
		ft_sprintf(str, "EditorDeselect");
	else if (code == event_editor_level_switch)
		ft_sprintf(str, "EditorLevelSwitch");
	else if (code == event_editor_open_popup_menu)
		ft_sprintf(str, "EditorOpenPopupMenu");
	else if (code == event_editor_increment_patrol_slot)
		ft_sprintf(str, "EditorIncrementPatrolSlot");
	else if (code == event_editor_decrement_patrol_slot)
		ft_sprintf(str, "EditorDecrementPatrolSlot");
}

static void	register_editor_custom_events_sub(t_doom3d *app)
{
	hash_map_add(app->custom_event_handles, event_editor_start_placement,
		(void*)handle_editor_placement_start);
	hash_map_add(app->custom_event_handles, event_editor_end_placement,
		(void*)handle_editor_placement_end);
	hash_map_add(app->custom_event_handles, event_editor_cancel_placement,
		(void*)handle_editor_placement_cancel);
	hash_map_add(app->custom_event_handles, event_editor_start_save,
		(void*)handle_editor_save_start);
	hash_map_add(app->custom_event_handles, event_editor_end_save,
		(void*)handle_editor_save_end);
	hash_map_add(app->custom_event_handles, event_editor_save_type,
		(void*)handle_editor_save_type);
	hash_map_add(app->custom_event_handles, event_editor_save_type_backspace,
		(void*)handle_editor_save_type_backspace);
	hash_map_add(app->custom_event_handles, event_editor_snap_to_grid,
		(void*)handle_editor_snap_to_grid);
}

/*
** Register all custom events that correspond to an action in app and their
** respecting handle functions
*/

void		register_editor_custom_events(t_doom3d *app)
{
	register_editor_custom_events_sub(app);
	hash_map_add(app->custom_event_handles, event_editor_delete,
		(void*)handle_editor_delete);
	hash_map_add(app->custom_event_handles, event_editor_exit,
		(void*)handle_editor_exit);
	hash_map_add(app->custom_event_handles, event_editor_select,
		(void*)handle_editor_select);
	hash_map_add(app->custom_event_handles, event_editor_deselect,
		(void*)handle_editor_deselect);
	hash_map_add(app->custom_event_handles, event_editor_level_switch,
		(void*)handle_editor_level_switch);
	hash_map_add(app->custom_event_handles, event_editor_open_popup_menu,
		(void*)handle_editor_open_popup_menu);
	hash_map_add(app->custom_event_handles, event_editor_add_texture,
		(void*)handle_editor_add_texture);
	hash_map_add(app->custom_event_handles, event_editor_add_normal_map,
		(void*)handle_editor_add_normal_map);
	hash_map_add(app->custom_event_handles, event_editor_increment_patrol_slot,
		(void*)handle_editor_patrol_slot_increment);
	hash_map_add(app->custom_event_handles, event_editor_decrement_patrol_slot,
		(void*)handle_editor_patrol_slot_decrement);
}
