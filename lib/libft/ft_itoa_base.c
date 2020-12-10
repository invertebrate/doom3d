/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:21:45 by ohakola           #+#    #+#             */
/*   Updated: 2020/09/01 16:48:43 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_itoa_base_32(int32_t nb, int32_t base)
{
	return (ft_itoa_base_64(nb, base));
}

char				*ft_itoa_base_u32(uint32_t nb, uint32_t base)
{
	return (ft_itoa_base_u64(nb, base));
}

char				*ft_itoa_base_64(int64_t nb, int64_t base)
{
	int		i;
	char	*arr;
	int		sign;
	char	*bases;

	sign = nb < 0 ? -1 : 1;
	if (base > 16 || base < 1)
		return (NULL);
	bases = "0123456789abcdef";
	if (!(arr = ft_strnew(get_num_len(nb, base) + (sign < 0 ? 1 : 0))))
		return (NULL);
	if (nb == false)
		arr[0] = '0';
	i = 0;
	while (nb != 0)
	{
		arr[i++] = bases[sign * (nb % base)];
		nb = nb / base;
	}
	if (sign == -1)
		arr[i] = '-';
	ft_strrev(arr);
	return (arr);
}

char				*ft_itoa_base_u64(uint64_t nb, uint64_t base)
{
	int		i;
	char	*arr;
	char	*bases;

	if (base > 16 || base < 1)
		return (NULL);
	bases = "0123456789abcdef";
	if (!(arr = ft_strnew(get_num_len(nb, base))))
		return (NULL);
	if (nb == false)
		arr[0] = '0';
	i = 0;
	while (nb != 0)
	{
		arr[i++] = bases[nb % base];
		nb = nb / base;
	}
	ft_strrev(arr);
	return (arr);
}
