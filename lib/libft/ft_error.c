/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 15:15:42 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/05 16:08:27 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				error_check(int test, const char *message)
{
	if (test)
	{
		LOG_ERROR("%s\n", message);
		exit(1);
	}
}
