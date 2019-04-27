/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** init_enemy
*/

#include "../include/rpg.h"
#include "../include/my.h"

void init_enemy(window_t *win)
{
    if (win->combat == 1) {
        init_sprite(&win->enemy->sprite[0], "ressources/pack/Pixel_Champions/Magical Heroes/Ley-the-Monster-Whisperer.png", get_pos_float(400, 500));
        win->enemy->health = 50;
    }
    if (win->combat == 2) {
        init_sprite(&win->enemy->sprite[0], "ressources/pack/Pixel_Champions/Magical Heroes/Oratio-the-Mercenary.png", get_pos_float(400, 500));
        win->enemy->health = 80;
    }
    if (win->combat == 3) {
        init_sprite(&win->enemy->sprite[0], "ressources/pack/Pixel_Champions/Magical Heroes/Glenys-the-Demonswordsman.png", get_pos_float(400, 500));
        win->enemy->health = 150;
    }
    sfSprite_setTextureRect(win->enemy->sprite->sprite, get_rect(297, 56, 30, 30));
    sfSprite_setScale(win->enemy->sprite->sprite, get_pos_float(-4.f, 4.f));
    init_text(&win->enemy->text[0], my_itc(win->enemy->health), get_pos_float(400, 100));
}