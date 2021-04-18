/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 19:51:56 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/18 19:48:36 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The ft_strclr() function sets all characters in a string to 0.
*/
void	ft_strclr(char *s)
{
	if (s)
		ft_bzero(s, ft_strlen(s));
}
