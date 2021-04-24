/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgbtoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 13:06:36 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/24 15:56:56 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Converts traditional R G B
** value to single integer form.
*/

int		ft_rgbtoi(t_rgb rgb)
{
	return ((rgb.r & 255) << 16) | ((rgb.g & 255) << 8 | (rgb.b & 255));
}
