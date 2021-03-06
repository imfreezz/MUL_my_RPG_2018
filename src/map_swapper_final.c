/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** map_swapper_final
*/

#include "../include/rpg.h"
#include "../include/my.h"

void go_boss(window_t *win)
{
    sfVector2f pos_player = sfSprite_getPosition(win->player->sprite->sprite);
    static int ok = 0;

    if (win->actual_page == FINAL && win->page == FINAL) {
        if (is_inside_zone(get_pos_float(910, 90), get_pos_float(950, 140),
        pos_player) == 1 && win->player->direction == UP && ok == 0) {
            display_text_in_textbox(win->quests);
            win->states->pause = 1;
            win->states->talking = 1;
            ok = 1;
        }
        if (is_inside_zone(get_pos_float(910, 0), get_pos_float(940, 90),
        pos_player) == 1 && win->player->direction == UP) {
            win->player->last_pos = pos_player;
            win->player->last_pos.y += 30;
            sfSprite_setPosition(win->player->sprite->sprite,
            get_pos_float(900, 950));
            win->page = BOSS;
        }
    }
}

void go_final(window_t *win)
{
    sfSprite *sprite = win->scene[TOWN].sprite[4].sprite;
    sfVector2f pos_player = sfSprite_getPosition(win->player->sprite->sprite);
    sfIntRect rect = sfSprite_getTextureRect(sprite);
    sfVector2f pos_door = sfSprite_getPosition(sprite);

    if (is_inside_zone(get_pos_float(pos_door.x - 30, pos_door.y),
    get_pos_float(pos_door.x + 40, pos_door.y + 100), pos_player) == 1) {
        rect.top = 192;
        sfSprite_setTextureRect(win->scene[TOWN].sprite[4].sprite, rect);
        if (sfMusic_getStatus(win->music->stone_door) == sfStopped)
            sfMusic_play(win->music->stone_door);
        if (pos_player.y >= pos_door.y - 60 &&
        pos_player.y <= pos_door.y + 20 && win->player->direction == UP) {
            sfSprite_setPosition(win->player->sprite->sprite,
            get_pos_float(950, 900));
            win->page = FINAL;
        }
    } else if (rect.top >= 64) {
        rect.top = 128;
        sfSprite_setTextureRect(win->scene[TOWN].sprite[4].sprite, rect);
    }
}

void leave_final(window_t *win)
{
    sfVector2f pos_player = sfSprite_getPosition(win->player->sprite->sprite);

    if (win->actual_page == FINAL && win->page == FINAL) {
        if (is_inside_zone(get_pos_float(890, 950), get_pos_float(1020, 1100),
        pos_player) == 1 && win->player->direction == DOWN) {
            sfSprite_setPosition(win->player->sprite->sprite,
            get_pos_float(1025, 150));
            sfMusic_stop(win->music->boss_final);
            win->page = TOWN;
        }
    }
}