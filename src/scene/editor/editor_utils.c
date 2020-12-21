/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 13:17:37 by ohakola           #+#    #+#             */
/*   Updated: 2020/12/21 13:19:43 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom3d.h"

/*
** Generates a random unique id where first bits are from app timestamp
** and rest are a random number.
*/

uint32_t	random_uuid(void)
{
	return (((SDL_GetTicks() % (1 << 8)) << 31) & (rand() % (1 << 23)));
}
