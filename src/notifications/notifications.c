/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notifications.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 16:14:00 by ohakola           #+#    #+#             */
/*   Updated: 2021/05/12 09:27:53 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Note that the distance limit is same as actionable trigger's interact radius
*/

static void	update_in_game_action_notification(t_doom3d *app)
{
	t_hits		*hits;
	t_hit		*closest_triangle_hit;
	t_3d_object	*obj;
	float		distance_limit;

	if (app->active_scene->scene_id != scene_id_main_game
		|| app->active_scene->is_paused)
	{
		ft_memset(app->action_text, 0, sizeof(app->action_text));
		return ;
	}
	distance_limit = app->unit_size * 3;
	hits = NULL;
	if (l3d_kd_tree_ray_hits(app->active_scene->triangle_tree, app->player.pos,
			app->player.forward, &hits))
	{
		l3d_get_closest_triangle_hit(hits, &closest_triangle_hit, -1);
		obj = closest_triangle_hit->triangle->parent;
		if (closest_triangle_hit != NULL && obj->type == object_type_trigger
			&& closest_triangle_hit->t < distance_limit)
			get_trigger_action_text(obj->params_type, app->action_text);
		else
			ft_memset(app->action_text, 0, sizeof(app->action_text));
		l3d_delete_hits(&hits);
	}
}

void	update_notifications(t_doom3d *app)
{
	t_notification	*last_notification;
	t_list			**last_node;

	update_in_game_action_notification(app);
	last_node = &app->notifications;
	if (!*last_node)
		return ;
	while ((*last_node)->next)
		last_node = &(*last_node)->next;
	last_notification = (*last_node)->content;
	last_notification->time -= app->info.delta_time;
	if (last_notification->time <= 0)
	{
		free(last_notification);
		free(*last_node);
		*last_node = NULL;
	}
}

/*
** For story notifications, the total time is forced to be min 150ms per letter
*/

void	notify_user(t_doom3d *app,
					t_notification notification)
{
	uint32_t	time_per_letter;
	uint32_t	len;

	if (notification.type == notification_type_story)
	{
		len = ft_strlen(notification.message);
		time_per_letter = 150.0;
		notification.time = time_per_letter * len;
	}
	notification.time_start = notification.time;
	if (app->notifications == NULL)
		app->notifications = ft_lstnew(&notification, sizeof(t_notification));
	else
		ft_lstadd(&app->notifications,
			ft_lstnew(&notification, sizeof(t_notification)));
}

void	delete_notifications(t_doom3d *app)
{
	t_list		*node;
	t_list		*tmp;

	node = app->notifications;
	while (node)
	{
		tmp = node;
		free((t_notification *)node->content);
		node = node->next;
		free(tmp);
	}
	app->notifications = NULL;
}
