/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_aabb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 22:50:15 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/30 21:06:43 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static void		draw_aabb_sub(t_doom3d *app, t_sub_framebuffer *buffers,
					t_box3d *aabb, uint32_t color)
{
	draw_debug_line(app, buffers, (float[2][3]){
		{aabb->xyz_min[0], aabb->xyz_min[1], aabb->xyz_min[2]},
		{aabb->xyz_min[0], aabb->xyz_min[1], aabb->xyz_max[2]}}, color);
	draw_debug_line(app, buffers, (float[2][3]){
		{aabb->xyz_min[0], aabb->xyz_min[1], aabb->xyz_max[2]},
		{aabb->xyz_max[0], aabb->xyz_min[1], aabb->xyz_max[2]}}, color);
	draw_debug_line(app, buffers, (float[2][3]){
		{aabb->xyz_max[0], aabb->xyz_min[1], aabb->xyz_max[2]},
		{aabb->xyz_max[0], aabb->xyz_min[1], aabb->xyz_min[2]}}, color);
	draw_debug_line(app, buffers, (float[2][3]){
		{aabb->xyz_max[0], aabb->xyz_min[1], aabb->xyz_min[2]},
		{aabb->xyz_min[0], aabb->xyz_min[1], aabb->xyz_min[2]}}, color);
	draw_debug_line(app, buffers, (float[2][3]){
		{aabb->xyz_min[0], aabb->xyz_max[1], aabb->xyz_min[2]},
		{aabb->xyz_min[0], aabb->xyz_max[1], aabb->xyz_max[2]}}, color);
	draw_debug_line(app, buffers, (float[2][3]){
		{aabb->xyz_min[0], aabb->xyz_max[1], aabb->xyz_max[2]},
		{aabb->xyz_max[0], aabb->xyz_max[1], aabb->xyz_max[2]}}, color);
}

void			draw_aabb(t_doom3d *app, t_sub_framebuffer *buffers,
					t_box3d *aabb, uint32_t color)
{
	draw_aabb_sub(app, buffers, aabb, color);
	draw_debug_line(app, buffers, (float[2][3]){
		{aabb->xyz_max[0], aabb->xyz_max[1], aabb->xyz_max[2]},
		{aabb->xyz_max[0], aabb->xyz_max[1], aabb->xyz_min[2]}}, color);
	draw_debug_line(app, buffers, (float[2][3]){
		{aabb->xyz_max[0], aabb->xyz_max[1], aabb->xyz_min[2]},
		{aabb->xyz_min[0], aabb->xyz_max[1], aabb->xyz_min[2]}}, color);
	draw_debug_line(app, buffers, (float[2][3]){
		{aabb->xyz_min[0], aabb->xyz_min[1], aabb->xyz_min[2]},
		{aabb->xyz_min[0], aabb->xyz_max[1], aabb->xyz_min[2]}}, color);
	draw_debug_line(app, buffers, (float[2][3]){
		{aabb->xyz_max[0], aabb->xyz_min[1], aabb->xyz_max[2]},
		{aabb->xyz_max[0], aabb->xyz_max[1], aabb->xyz_max[2]}}, color);
	draw_debug_line(app, buffers, (float[2][3]){
		{aabb->xyz_max[0], aabb->xyz_min[1], aabb->xyz_min[2]},
		{aabb->xyz_max[0], aabb->xyz_max[1], aabb->xyz_min[2]}}, color);
	draw_debug_line(app, buffers, (float[2][3]){
		{aabb->xyz_min[0], aabb->xyz_min[1], aabb->xyz_max[2]},
		{aabb->xyz_min[0], aabb->xyz_max[1], aabb->xyz_max[2]}}, color);
}

void			draw_selected_aabb(t_render_work *work)
{
	t_doom3d			*app;
	t_sub_framebuffer	*buffers;
	t_3d_object			*obj;
	int32_t				i;

	buffers = work->framebuffer->sub_buffers[work->sub_buffer_i];
	app = work->app;
	i = -1;
	while (++i < app->editor.num_selected_objects)
	{
		obj = app->editor.selected_objects[i];
		draw_aabb(app, buffers, &obj->aabb, 0xff0000ff);
	}
}

static void		draw_triangle_tree_recursive(t_doom3d *app,
					t_sub_framebuffer *buffers, t_kd_node *root, uint32_t color)
{
	if (root != NULL)
	{
		draw_aabb(app, buffers, &root->bounding_box, color);
		draw_triangle_tree_recursive(app, buffers, root->left, 0x00ff00ff);
		draw_triangle_tree_recursive(app, buffers, root->right, 0x0000ffff);
	}
}

void			draw_triangle_tree_bounding_boxes(t_render_work *work)
{
	draw_triangle_tree_recursive(work->app,
		work->framebuffer->sub_buffers[work->sub_buffer_i],
		work->app->active_scene->triangle_tree->root, 0xff0000ff);
}
