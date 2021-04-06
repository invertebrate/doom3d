/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 15:15:42 by ohakola           #+#    #+#             */
/*   Updated: 2021/04/06 19:47:31 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				error_check(int test, const char *message)
{
	if (test)
	{
		LOG_FATAL("%s", message);
		exit(1);
	}
}
