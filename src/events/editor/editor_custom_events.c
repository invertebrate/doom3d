/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_custom_events.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 01:50:28 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/31 01:51:57 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void	editor_placement_event_to_str(char *str, t_doom3d_event code)
{
	if (code == event_editor_start_placement)
		ft_sprintf(str, "EditorStartPlacement");
	else if (code == event_editor_end_placement)
		ft_sprintf(str, "EditorEndPlacement");
	else if (code == event_editor_cancel_placement)
		ft_sprintf(str, "EditorCancelPlacement");
}

void		editor_event_to_str(char *str, t_doom3d_event code)
{
	editor_placement_event_to_str(str, code);
	if (code == event_editor_add_texture)
		ft_sprintf(str, "EditorAddTexture");
	else if (code == event_editor_add_normal_map)
		ft_sprintf(str, "EditorAddNormalMap");
	else if (code == event_editor_start_save)
		ft_sprintf(str, "EditorStartSave");
	else if (code == event_editor_end_save)
		ft_sprintf(str, "EditorEndSave");
	else if (code == event_editor_save_type)
		ft_sprintf(str, "EditorType");
	else if (code == event_editor_save_type_backspace)
		ft_sprintf(str, "EditorTypeBackspace");
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
	else if (code == event_editor_exit)
		ft_sprintf(str, "EditorExit");
}

static void	register_editor_placement_events(t_doom3d *app)
{
	hash_map_add(app->custom_event_handles, event_editor_start_placement,
		(void*)handle_editor_placement_start);
	hash_map_add(app->custom_event_handles, event_editor_end_placement,
		(void*)handle_editor_placement_end);
	hash_map_add(app->custom_event_handles, event_editor_cancel_placement,
		(void*)handle_editor_placement_cancel);
}

void		register_editor_custom_events(t_doom3d *app)
{
	register_editor_placement_events(app);
	hash_map_add(app->custom_event_handles, event_editor_start_save,
		(void*)handle_editor_save_start);
	hash_map_add(app->custom_event_handles, event_editor_end_save,
		(void*)handle_editor_save_end);
	hash_map_add(app->custom_event_handles, event_editor_save_type,
		(void*)handle_editor_save_type);
	hash_map_add(app->custom_event_handles, event_editor_save_type_backspace,
		(void*)handle_editor_save_type_backspace);
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
}
