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
    char *name = "ressources/images/sprites/";

    if (win->combat == 1) {
        name = my_strcat(name, "Ley-the-Monster-Whisperer.png");
        win->enemy->health = 50;
        win->enemy->strength = 50;
        sfMusic_stop(win->music->boss_song);
        sfMusic_play(win->music->boss_battle);
    }
    if (win->combat == 2) {
        name = my_strcat(name, "Oratio-the-Mercenary.png");
        win->enemy->strength = 80;
        win->enemy->health = 80;
        sfMusic_stop(win->music->boss_song);
        sfMusic_play(win->music->boss_battle);
    }
    if (win->combat == 3) {
        name = my_strcat(name, "Glenys-the-Demonswordsman.png");
        win->enemy->health = 150;
        win->enemy->strength = 150;
        sfMusic_stop(win->music->boss_song);
        sfMusic_play(win->music->boss_final);
    }
    init_sprite(&win->enemy->sprite[0], name, get_pos_float(400, 500));
    sfSprite_setTextureRect(win->enemy->sprite->sprite,
    get_rect(297, 56, 30, 30));
    sfSprite_setScale(win->enemy->sprite->sprite, get_pos_float(-4.f, 4.f));
    init_text(&win->enemy->text[0], my_itc(win->enemy->health),
    get_pos_float(400, 100));
}