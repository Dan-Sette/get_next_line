/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalves-s <dalves-s@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 15:37:29 by dalves-s          #+#    #+#             */
/*   Updated: 2021/06/25 23:47:18 by dalves-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void test_gnl(int fd, const char *current_file)
{
    int gnl_return;
    int line_counter;
    char *current_line;

    printf("testing file %s\n", current_file);
    line_counter = 0;
    while (true)
    {
        gnl_return = get_next_line(fd, &current_line);
        line_counter++;
        if (gnl_return == -1)
            break ;
        printf("LINE %d:  '%s'\n", line_counter, current_line);
        free(current_line);
        if (gnl_return == 0)
            break ;
    }
    printf("LAST RETURN:%d\n", gnl_return);
    printf("-------------------------------------------------------------------------\n");
    close(fd);
}

int main(void)
{
    char const *current_file;
    int current_file_descriptor;
    
    current_file = "./test_gnl/test_2";
    printf("%d\n", current_file_descriptor = open(current_file, O_RDONLY));
    test_gnl(current_file_descriptor, current_file);
    return 0;
}
