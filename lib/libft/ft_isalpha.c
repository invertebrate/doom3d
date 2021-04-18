/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 15:11:00 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/18 19:45:33 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The ft_isalpha() function tests for any character
** for which ft_isupper(3) or ft_islower(3) is true.
*/
int	ft_isalpha(int c)
{
	return (ft_isupper(c) || ft_islower(c));
}
