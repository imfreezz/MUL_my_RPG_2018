/*
** EPITECH PROJECT, 2018
** my_isneg.
** File description:
** my_isneg
*/


#include "../../../include/my.h"

int my_isneg(int n)
{
    if (n >= 0)
        my_putchar('P');
    if (n < 0)
        my_putchar('N');
    return (0);
}
