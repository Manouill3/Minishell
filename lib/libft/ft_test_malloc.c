/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test_malloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdegache <mdegache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:36:30 by mdegache          #+#    #+#             */
/*   Updated: 2025/03/12 14:43:24 by mdegache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#undef malloc
#undef free

void    *__test_malloc(size_t size, const char *file, int line, const char *func)
{
    void    *ptr = malloc(size);

    printf("malloc at %s:%d - %s -> returned \033[35;1m%p\033[0m\n", file, line, func, ptr);
    return (ptr);
}

void    __test_free(void *ptr, const char *file, int line, const char *func)
{
    printf("free at %s:%d - %s -> \033[36;1m%p\033[0m\n", file, line, func, ptr);
    free(ptr);
}