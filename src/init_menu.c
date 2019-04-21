/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** init_menu
*/

#include "../include/rpg.h"
#include "../include/my.h"

window_t *init_menu(window_t *win)
{
    sfVector2f size = get_pos_float(400, 100);
    sfVector2u size_window = sfRenderWindow_getSize(win->window);
    sfVector2f pos_window;
    int order_button[] = {JOUER, NOUVEAU, TUTORIEL, PARAM, QUITTER};

    pos_window.x = (size_window.x - size.x) / 2;
    pos_window.y = (size_window.y - size.y) / 4;
    set_struct(win, 5, 1, 1);
    init_text(&win->scene[MAINMENU].text[0], "Tekzerk", get_pos_float(pos_window.x - 70, 10));
    sfText_setColor(win->scene[MAINMENU].text[0].str, sfWhite);
    sfText_setCharacterSize(win->scene[MAINMENU].text[0].str, 150);
    win->scene[MAINMENU].text[0].font = sfFont_createFromFile("ressources/font/font.ttf");
    sfText_setFont(win->scene[MAINMENU].text[0].str, win->scene[MAINMENU].text[0].font);
    init_sprite(&win->scene[MAINMENU].sprite[0], "ressources/pack/background/frame2.png", get_pos_float(0, 0));
    win->scene[MAINMENU].sprite[0].rect.top = 0;
    win->scene[MAINMENU].sprite[0].rect.left = 0;
    win->scene[MAINMENU].sprite[0].rect.width = 1920;
    win->scene[MAINMENU].sprite[0].rect.height = 1080;
    for (int i = 0; i < win->scene[MAINMENU].nb_button; i++) {
        set_next_buttons(&win->scene[MAINMENU].button[i], win->rect_buttons, order_button[i]);
        init_button(&win->scene[MAINMENU].button[i], get_pos_float(pos_window.x - 600, pos_window.y), size, win->texture_button);
        pos_window.y += size.y + 20;
    }
    if (win->no_saves == 0)
        win->scene[MAINMENU].button[0].callback = &play_game;
    else
        win->scene[MAINMENU].button[0].callback = NULL;
    win->scene[MAINMENU].button[1].callback = &heroes_menu;
    win->scene[MAINMENU].button[2].callback = &how_to_play;
    win->scene[MAINMENU].button[3].callback = &options;
    win->scene[MAINMENU].button[4].callback = &quit;
    sfSprite_setTextureRect(win->scene[MAINMENU].sprite[0].sprite, win->scene[MAINMENU].sprite[0].rect);
    sfMusic_play(win->music->menu_song);
    return (win);
}