/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_islower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:25:51 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/24 15:55:01 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_islower() function tests for any character
** is within lower alphabet ascii range
*/

int	ft_islower(int c)
{
	return (c >= 'a' && c <= 'z');
}
