/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** event
*/

#include "../include/rpg.h"
#include "../include/my.h"

void pick_sword(window_t *win)
{
    int actual_pos = -1;

    sfText_setString(win->text->str, "\n");
    sfSprite_setPosition(win->objects[SWORD].sprite, get_inv_pos(win->inv));
    actual_pos = get_actual_pos_inv(win->inv, get_pos_float(0, 0));
    win->inv->items[actual_pos].busy = 1;
    win->inv->items[actual_pos].name = get_name_from_type(win->objects[SWORD].type);
    win->objects[SWORD].item = 1;
    win->objects[SWORD].depth = 2;
    display_text_in_textbox(win->quests, "Vous avez trouve une Epee !\n");
    win->quests->quete_done++;
}

void pick_armor(window_t *win)
{
    int actual_pos = -1;

    sfText_setString(win->text->str, "\n");
    sfSprite_setPosition(win->objects[ARMOR].sprite, get_inv_pos(win->inv));
    actual_pos = get_actual_pos_inv(win->inv, get_pos_float(0, 0));
    win->inv->items[actual_pos].busy = 1;
    win->inv->items[actual_pos].name = get_name_from_type(win->objects[ARMOR].type);
    win->objects[ARMOR].item = 1;
    win->objects[ARMOR].depth = 2;
    display_text_in_textbox(win->quests, "Vous avez trouve une Armure !\n");
    win->quests->quete_done++;
}