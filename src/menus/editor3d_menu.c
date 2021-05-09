/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor3d_menu.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:26:29 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/05 16:16:54 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

void	editor_popup_menu_create_sub1(t_doom3d *app,
			t_editor_menu_index new_menu,
			t_vec2 pos)
{
	if (new_menu == editor_menu_objects)
		editor_popup_menu_set(app, pos, (t_button_menu_params){
			.button_names = app->active_scene->asset_files.model_files,
			.num_buttons = app->active_scene->asset_files.num_models,
			.on_click = on_objects_menu_button_click,
			.button_font = app->window->debug_font});
	else if (new_menu == editor_menu_textures)
		editor_popup_menu_set(app, pos, (t_button_menu_params){
			.button_names = app->active_scene->asset_files.texture_files,
			.num_buttons = app->active_scene->asset_files.num_textures,
			.on_click = on_textures_menu_button_click,
			.button_font = app->window->debug_font});
}

void	editor_popup_menu_create_sub2(t_doom3d *app,
			t_editor_menu_index new_menu,
			t_vec2 pos)
{
	if (new_menu == editor_menu_normalmaps)
		editor_popup_menu_set(app, pos, (t_button_menu_params){
			.button_names = app->active_scene->asset_files.normal_map_files,
			.num_buttons = app->active_scene->asset_files.num_normal_maps,
			.on_click = on_normmaps_menu_button_click,
			.button_font = app->window->debug_font});
	else if (new_menu == editor_menu_prefabs)
		editor_popup_menu_set(app, pos, (t_button_menu_params){
			.button_names = app->active_scene->asset_files.prefab_names,
			.num_buttons = app->active_scene->asset_files.num_prefabs,
			.on_click = on_prefab_menu_button_click,
			.button_font = app->window->debug_font});
}

void	editor_popup_menu_create_sub3(t_doom3d *app,
			t_editor_menu_index new_menu,
			t_vec2 pos)
{
	if (new_menu == editor_menu_npcs)
		editor_popup_menu_set(app, pos, (t_button_menu_params){
			.button_names = app->active_scene->asset_files.npc_names,
			.num_buttons = app->active_scene->asset_files.num_npcs,
			.on_click = on_npc_menu_button_click,
			.button_font = app->window->debug_font});
	else if (new_menu == editor_menu_triggers)
		editor_popup_menu_set(app, pos, (t_button_menu_params){
			.button_names = app->active_scene->asset_files.trigger_names,
			.num_buttons = app->active_scene->asset_files.num_triggers,
			.on_click = on_trigger_menu_button_click,
			.button_font = app->window->debug_font});
}

/*
** Create popup menus for editor
** Totally ugly formatting here unfortunately norm requirements. There's always
** a way to do it clean too, but not today.
*/

void	editor_popup_menu_create(t_doom3d *app,
			t_editor_menu_index new_menu,
			t_vec2 pos)
{
	t_vec2	dims;

	editor_popup_menu_create_sub1(app, new_menu, pos);
	editor_popup_menu_create_sub2(app, new_menu, pos);
	editor_popup_menu_create_sub3(app, new_menu, pos);
	if (new_menu == editor_menu_lights)
		editor_popup_menu_set(app, pos, (t_button_menu_params){
			.button_names = app->active_scene->asset_files.light_names,
			.num_buttons = app->active_scene->asset_files.num_lights,
			.on_click = on_light_menu_button_click,
			.button_font = app->window->debug_font});
	popup_menu_default_dims(dims);
	if (new_menu == editor_menu_guide)
		editor_popup_menu_set(app, (t_vec2){
			app->window->framebuffer->width / 2 - dims[0] / 2.0,
			app->window->framebuffer->height / 2 - dims[1] / 2.0},
			(t_button_menu_params){
			.button_names = NULL, .num_buttons = 0, .on_click = NULL,
			.button_font = NULL});
}

/*
** Create editor's main menu
*/

void	editor3d_menu_create(t_doom3d *app)
{
	error_check(!(app->active_scene->menus = ft_calloc(sizeof(t_button_group *)
				* 4)), "Failed to malloc menus");
	app->active_scene->menus[0] = button_menu_create_shaded(app,
			(t_button_menu_params){
			.button_names = (const char*[9]){"Exit", "Save",
			"Objects", "Textures", "NormMaps", "Prefabs",
			"Characters", "Triggers", "Lights"},
			.num_buttons = 9, .on_click = on_editor_menu_button_click,
			.button_font = app->window->main_font});
	app->active_scene->menus[1] = button_menu_create_shaded(app,
			(t_button_menu_params){
			.button_names = (const char*[1]){"Delete"},
			.num_buttons = 1, .on_click = on_delete_menu_button_click,
			.button_font = app->window->main_font});
	app->active_scene->menus[1]->is_active = false;
	app->active_scene->menus[2] = button_menu_create_shaded(app,
			(t_button_menu_params){.button_names = (const char*[1]){
			"New"}, .num_buttons = 1,
			.on_click = on_new_level_menu_button_click,
			.button_font = app->window->main_font});
	app->active_scene->menus[3] = button_menu_create_shaded(app,
			(t_button_menu_params){.button_names = (const char*[1]){
			"Guide"}, .num_buttons = 1, .on_click = on_guide_menu_button_click,
			.button_font = app->window->main_font});
	app->active_scene->num_button_menus = 4;
}
