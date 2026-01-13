/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esergeev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 11:33:57 by esergeev          #+#    #+#             */
/*   Updated: 2025/06/11 11:34:04 by esergeev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>

int	ft_printf(const char *format, ...);
int	ft_putnbr(int nb);
int	ft_putchar(char c);
int	ft_putptr(uintptr_t ptr);
int	ft_putunsign(unsigned int nb);
int	ft_puthex(unsigned int arg, char format);

#endif
