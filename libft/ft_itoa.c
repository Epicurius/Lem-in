/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneronin <nneronin@stuent.hive.fi>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 13:18:53 by nneronin          #+#    #+#             */
/*   Updated: 2020/06/09 08:32:38 by nneronin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_itoa(int nb)
{
	int		i;
	long	n;
	char	*str;

	n = nb;
	i = ft_nbrlen(n);
	if (!(str = ft_strnew(i)))
		return (NULL);
	if (n == 0)
		str[0] = 48;
	else if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		str[i] = 48 + (n % 10);
		n = n / 10;
		i--;
	}
	return (str);
}
