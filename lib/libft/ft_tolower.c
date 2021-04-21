/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:40:30 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/18 19:50:12 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The ft_tolower() function converts an upper-case letter to the
** corresponding lower-case letter.
*/
int		ft_tolower(int c)
{
	if (ft_isupper(c))
		c += 32;
	return (c);
}
