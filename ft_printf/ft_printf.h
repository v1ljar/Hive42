/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vuljas <vuljas@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:07:24 by vuljas            #+#    #+#             */
/*   Updated: 2024/11/21 17:14:39 by vuljas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>

# define BASE10 "0123456789abcdef"
# define BASE16CAP "0123456789ABCDEF"

int	ft_printf(const char *format, ...);
int	ft_print_char(int c);
int	ft_print_digit(long nbr, char *str, int base);
int	ft_print_str(char *str);
int	ft_print_pointer(void *ptr, char *str, int base);

#endif
