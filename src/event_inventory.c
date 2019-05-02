/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** event_inventory
*/

#include "../include/rpg.h"
#include "../include/my.h"

void global_event_condition_escape(window_t *win)
{
    if (win->actual_page == MAINMENU)
        quit(win);
    if (win->actual_page >= CASTLE && win->actual_page < COMBAT) {
        if (win->pause == 0 && win->inventory == 0 && win->quest == 0)
            pause_game(win);
        else if (win->inventory == 0 && win->quest == 0 &&
        win->talking == 0 && win->pause == 1) {
            unpause_game(win);
        }
        if (win->quest == 0 && win->pause == 1 && win->inventory == 1)
            close_inventory(win);
    }
}

void global_event(window_t *win)
{
    if (win->event.type == sfEvtClosed)
        quit(win);
    if (win->event.type == sfEvtKeyPressed) {
        if (win->actual_page >= CASTLE && win->actual_page < COMBAT)
            check_keyboard_input_ingame(win);
        if (sfKeyboard_isKeyPressed(sfKeyEscape) == sfTrue)
            global_event_condition_escape(win);
    }
    global_event_condition(win);
}