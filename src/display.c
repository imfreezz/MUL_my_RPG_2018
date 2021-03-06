/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** display
*/

#include "../include/rpg.h"
#include "../include/my.h"

ptr_func *init_func(void)
{
    static ptr_func ptr_choose[] = {
        {MAINMENU, &init_menu, &draw_scene, &global_event, &destroy_scene},
        {HEROES, &init_choose_heroes, &draw_scene, &global_event,
            &destroy_scene},
        {HOW_TO_PLAY, &init_how_to_play, &draw_scene, &global_event,
            &destroy_scene},
        {OPTIONS, &init_options, &draw_scene, &global_event, &destroy_scene},
        {CASTLE, &init_castle, &draw_scene, &global_event, &destroy_scene},
        {TOWN, &init_town, &draw_scene, &global_event, &destroy_scene},
        {HOUSE1, &init_house_1, &draw_scene, &global_event, &destroy_scene},
        {HOUSE2, &init_house_2, &draw_scene, &global_event, &destroy_scene},
        {HOUSE3, &init_house_3, &draw_scene, &global_event, &destroy_scene},
        {FOREST, &init_forest, &draw_scene, &global_event, &destroy_scene},
        {FINAL, &init_final, &draw_scene, &global_event, &destroy_scene},
        {BOSS, &init_boss, &draw_scene, &global_event, &destroy_scene},
        {COMBAT, &init_combat, &draw_scene, &global_event, &destroy_scene},
        {END, &init_end, &draw_scene, &global_event, &destroy_scene},
    };
    return (ptr_choose);
}

void manage_game(window_t *win)
{
    if (win->actual_page >= CASTLE && win->actual_page < COMBAT &&
    win->states->pause == 0 && win->states->no_saves == 0) {
        move_player(win);
        if (win->actual_page == CASTLE) {
            win->move_time = sfClock_getElapsedTime(win->move);
            win->states->seconds = win->move_time.microseconds / 400000.0;
            animation_torch(win, 20);
        }
    }
}

static int change_page(window_t *win, ptr_func *ptr_choose)
{
    if (win->page != win->actual_page) {
        win = ptr_choose[win->actual_page].end(win);
        if (win == NULL)
            return (84);
        win = ptr_choose[win->page].start(win);
        if (win == NULL)
            return (84);
        win->actual_page = win->page;
    }
    return (0);
}

static int check_events(window_t *win, ptr_func *ptr_choose)
{
    if (change_page(win, ptr_choose) == 84)
        return (84);
    while (sfRenderWindow_pollEvent(win->window, &win->event)) {
        if (ptr_choose[win->actual_page].event(win) == 84)
            return (84);
    }
    return (0);
}

int display(window_t *win)
{
    ptr_func *ptr_choose = init_func();
    win = ptr_choose[win->actual_page].start(win);

    if (win == NULL)
        return (84);
    while (sfRenderWindow_isOpen(win->window)) {
        if (check_events(win, ptr_choose) == 84)
            return (84);
        win = ptr_choose[win->actual_page].draw(win);
        animation_mainmenu(win);
        animation_choose_heroes(win);
        animation_end(win);
        manage_game(win);
        check_enemy_turn(win);
    }
    return (0);
}