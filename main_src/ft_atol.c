/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlow <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 19:13:50 by mlow              #+#    #+#             */
/*   Updated: 2024/02/07 19:14:18 by mlow             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long	ft_atol(const char *nptr)
{
	long	num;
	long	minus;
	long	i;

	num = 0;
	minus = 1;
	i = 0;
	while ((nptr[num] >= '\t' && nptr[num] <= '\r') || nptr[num] == ' ')
		num++;
	if (nptr[num] == '-' || nptr[num] == '+')
	{
		if (nptr[num] == '-')
			minus = minus * -1;
		num++;
	}
	while (nptr[num] >= '0' && nptr[num] <= '9')
	{
		i = (i * 10) + (nptr[num] - '0');
		num++;
	}
	return (i * minus);
}
