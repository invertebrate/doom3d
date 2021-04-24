/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 16:43:00 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/24 15:55:04 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The ft_isprint() function tests for any character
** is a printable character
*/

int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
