/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: veilo <veilo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 18:41:09 by veilo             #+#    #+#             */
/*   Updated: 2020/12/30 20:32:36 by veilo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// typedef struct	s_animated_object
// 	/* data */
// }				t_animated_object;

// struct			s_3d_object
// {
// 	uint32_t		id;
// 	t_vertex		**vertices;
// 	int32_t			num_vertices;
// 	t_triangle		*triangles;
// 	int32_t			num_triangles;
// 	t_material		*material;
// 	t_mat4			rotation;
// 	t_mat4			scale;
// 	t_vec3			position;
// 	t_box3d			aabb;
// t_bool			animated;
// uint32_t		frame_count;
// uint32_t		current_frame;
// uint32_t		start_frame;
// uint32_t		start_tick;
// t_3d_object	*animation_frames; contains the objects for each anim frame
	// int32_t		*anim_frame_numbers; contains the frame indices for each animation start
// };

#include "doom3d.h"

void			update_app_ticks(t_doom3d *app)
{
	app->current_tick = (SDL_GetPerformanceCounter() * TICKS_PER_SEC) /
						SDL_GetPerformanceFrequency();
}

// t_3d_object				*l3d_read_obj(const char *filename, t_surface *texture,
// 							t_surface *normal_map)

static void		get_path_string(int i, char *frame_path, char *temp_index_string)
{
	if (i < 10)
	{
		ft_strcat(frame_path, "_00");
		temp_index_string = ft_itoa(i);
		ft_strcat(frame_path, temp_index_string);
	}
	else if (i < 100)
	{
		ft_strcat(frame_path, "_0");
		temp_index_string = ft_itoa(i);
		ft_strcat(frame_path, temp_index_string);
	}
}

t_bool			read_frames_to_object(t_doom3d *app, t_3d_object *object, char *path, int framecount)
{//!shouldnt have leaks but if they occur check here
	int		i;
	char	*frame_path;
	char	*temp_index_string;

	frame_path = (char*)malloc(sizeof(char) * ft_strlen(path) + 5);
	i = -1;
	while(++i < framecount && i < 100)
	{
		ft_strcpy(frame_path, path);
		get_path_string(i, frame_path, temp_index_string);
		object->animation_frames[i] = l3d_read_obj(frame_path, NULL, NULL);
		free(temp_index_string);
	}
	free(frame_path);
	temp_index_string = NULL;
	frame_path = NULL;
	return (0);
}

uint32_t		update_current_frame(t_doom3d *app, t_3d_object *object)
{
	uint32_t	current_frame;

	current_frame = object->start_frame +
	((app->current_tick - object->start_tick) % (int)(TICKS_PER_SEC / ANIM_FPS));
	object->current_frame = current_frame;
	return (current_frame);
}
// int test()
// {
//     return (0);
// }