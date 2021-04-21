/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notifications1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 11:24:41 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/18 23:39:03 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

static int32_t	adjust_notifications_dims(t_doom3d *app,
					int32_t text_dims[2], int32_t dims[2], int32_t padding)
{
	t_list		*node;
	int32_t		i;

	dims[0] = 0;
	dims[1] = 0;
	node = app->notifications;
	i = 0;
	while (node)
	{
		if (((t_notification*)node->content)->type == notification_type_info)
		{
			TTF_SizeText(app->window->debug_font,
				((t_notification*)node->content)->message,
				&text_dims[0], &text_dims[1]);
			dims[0] = (int32_t)l3d_fmax(dims[0], text_dims[0] + padding);
			dims[1] += text_dims[1] + padding;
			i++;
		}
		node = node->next;
	}
	return (i);
}

/*
** Renders doom3d notifications that show textual information to user.
** Notifications can be either story notifications or just info notifications.
*/
void			render_notifications(t_doom3d *app, t_vec2 pos)
{
	int32_t		dims[2];
	int32_t		padding;
	int32_t		text_dims[2];
	int32_t		num_notifications;

	if (app->notifications == NULL)
		return ;
	padding = 3;
	num_notifications =
		adjust_notifications_dims(app, text_dims, dims, padding);
	while ((int32_t)pos[1] + dims[1] + padding * 2 < 0)
		pos[1]++;
	while ((int32_t)pos[0] + dims[0] + padding * 2 >
		app->window->framebuffer->width)
		pos[0]--;
	if (num_notifications > 0)
		render_notifications_background(app, pos, dims, padding);
	render_notification_messages(app, pos, text_dims, padding);
}