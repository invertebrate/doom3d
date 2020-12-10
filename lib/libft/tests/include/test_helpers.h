/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_helpers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 17:23:16 by ohakola           #+#    #+#             */
/*   Updated: 2020/09/17 17:31:14 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HELPERS_H
# define TEST_HELPERS_H

typedef struct		s_position
{
	int			x;
	int			y;
}					t_position;

typedef struct		s_velocity
{
	float			x;
	float			y;
}					t_velocity;

typedef struct		s_color
{
	int				val;
}					t_color;

typedef struct		s_foo
{
	double			bar;
}					t_foo;

typedef enum		e_component_id
{
	comp_empty = 0,
	comp_position = 1,
	comp_velocity = 1 << 1,
	comp_color = 1 << 2,
	comp_foo = 1 << 3,
}					t_component_id;

#endif
