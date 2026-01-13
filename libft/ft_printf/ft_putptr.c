/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esergeev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:29:43 by esergeev          #+#    #+#             */
/*   Updated: 2025/06/11 11:29:48 by esergeev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_len_ptr(uintptr_t ptr)
{
	int	len;

	len = 0;
	while (ptr != 0)
	{
		len++;
		ptr /= 16;
	}
	return (len);
}

void	ft_writeptr(uintptr_t ptr)
{
	if (ptr >= 16)
	{
		ft_writeptr(ptr / 16);
		ft_writeptr(ptr % 16);
	}
	else
	{
		if (ptr <= 9)
			ft_putchar(ptr + '0');
		else
			ft_putchar(ptr - 10 + 'a');
	}
}

int	ft_putptr(uintptr_t ptr)
{
	int	len;

	len = 0;
	if (ptr == 0)
	{
		write(1, "(nil)", 5);
		len += 5;
	}
	else
	{
		write(1, "0x", 2);
		len = 2;
		ft_writeptr(ptr);
		len += ft_len_ptr(ptr);
	}
	return (len);
}
