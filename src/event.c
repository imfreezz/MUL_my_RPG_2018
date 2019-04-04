/*
** EPITECH PROJECT, 2019
** Untitled (Workspace)
** File description:
** event
*/

#include "../include/rpg.h"
#include "../include/my.h"

void mouse_pressed_event(window_t *win)
{
    sfVector2i click_pos = sfMouse_getPositionRenderWindow(win->window);
    sfRectangleShape *rect;

    for (int i = 0; i < win->scene[win->actual_page].nb_button; i++) {
        rect = win->scene[win->actual_page].button[i].shape;
        if (button_is_clicked(win->scene[win->actual_page].button[i],
        click_pos)) {
            sfRectangleShape_setTextureRect(rect, win->scene[win->actual_page].button[i].rect_pressed);
        }
    }
}

void mouse_released_event(window_t *win)
{
    sfVector2i click_pos = sfMouse_getPositionRenderWindow(win->window);
    sfRectangleShape *rect;

    for (int i = 0; i < win->scene[win->actual_page].nb_button; i++) {
        rect = win->scene[win->actual_page].button[i].shape;
        if (button_is_clicked(win->scene[win->actual_page].button[i],
        click_pos)) {
            sfRectangleShape_setTextureRect(rect, win->scene[win->actual_page].button[i].rect_idle);
            win->scene[win->actual_page].button[i].callback(win);
        }
    }
}

void mouse_moved_event(window_t *win)
{
    sfVector2i click_pos = sfMouse_getPositionRenderWindow(win->window);
    sfRectangleShape *rect;

    for (int i = 0; i < win->scene[win->actual_page].nb_button; i++) {
        rect = win->scene[win->actual_page].button[i].shape;
        if (button_is_hovered(win->scene[win->actual_page].button[i],
        click_pos)) {
            sfRectangleShape_setTextureRect(rect, win->scene[win->actual_page].button[i].rect_hovered);
        } else {
            sfRectangleShape_setTextureRect(rect, win->scene[win->actual_page].button[i].rect_idle);
        }
    }
}

void move_player(window_t *win)
{
    static int move = 0;

    if (sfKeyboard_isKeyPressed(sfKeyZ) == sfTrue || sfKeyboard_isKeyPressed(sfKeyUp) == sfTrue) {
        if (move != 0) {
            if (move == 1)
                win->player->speed.y -= 20;
            if (move == 2)
                win->player->speed.x += 20;
            if (move == 3)
                win->player->speed.x -= 20;
            move = 0;
            win->player->sprite->rect.left = 15;
        }
        win->player->sprite->rect.left += 48;
        win->player->sprite->rect.top = 159;
        if (win->player->sprite->rect.left > 111)
            win->player->sprite->rect.left = 15;
        sfSprite_setTextureRect(win->player->sprite->sprite, win->player->sprite->rect);
        sfSprite_setPosition(win->player->sprite->sprite, get_pos_float(win->player->speed.x, win->player->speed.y));
        win->player->speed.y -= 20;
    }
    if (sfKeyboard_isKeyPressed(sfKeyS) == sfTrue || sfKeyboard_isKeyPressed(sfKeyDown) == sfTrue) {
        if (move != 1) {
            if (move == 0)
                win->player->speed.y += 20;
            if (move == 2)
                win->player->speed.x += 20;
            if (move == 3)
                win->player->speed.x -= 20;
            move = 1;
            win->player->sprite->rect.left = 15;
        }
        win->player->sprite->rect.left += 48;
        win->player->sprite->rect.top = 15;
        if (win->player->sprite->rect.left > 111)
            win->player->sprite->rect.left = 15;
        sfSprite_setTextureRect(win->player->sprite->sprite, win->player->sprite->rect);
        sfSprite_setPosition(win->player->sprite->sprite, get_pos_float(win->player->speed.x, win->player->speed.y));
        win->player->speed.y += 20;
    }
    if (sfKeyboard_isKeyPressed(sfKeyQ) == sfTrue || sfKeyboard_isKeyPressed(sfKeyLeft) == sfTrue) {
        if (move != 2) {
            if (move == 3)
                win->player->speed.x -= 20;
            if (move == 0)
                win->player->speed.y += 20;
            if (move == 1)
                win->player->speed.y -= 20;
            move = 2;
            win->player->sprite->rect.left = 15;
        }
        win->player->sprite->rect.left += 48;
        win->player->sprite->rect.top = 62;
        if (win->player->sprite->rect.left > 111)
            win->player->sprite->rect.left = 15;
        sfSprite_setTextureRect(win->player->sprite->sprite, win->player->sprite->rect);
        sfSprite_setPosition(win->player->sprite->sprite, get_pos_float(win->player->speed.x, win->player->speed.y));
        win->player->speed.x -= 20;
    }
    if (sfKeyboard_isKeyPressed(sfKeyD) == sfTrue || sfKeyboard_isKeyPressed(sfKeyRight) == sfTrue) {
        if (move != 3) {
            if (move == 2)
                win->player->speed.x += 20;
            if (move == 0)
                win->player->speed.y += 20;
            if (move == 1)
                win->player->speed.y -= 20;
            move = 3;
            win->player->sprite->rect.left = 15;
        }
        win->player->sprite->rect.left += 48;
        win->player->sprite->rect.top = 110;
        if (win->player->sprite->rect.left > 111)
            win->player->sprite->rect.left = 15;
        sfSprite_setTextureRect(win->player->sprite->sprite, win->player->sprite->rect);
        sfSprite_setPosition(win->player->sprite->sprite, get_pos_float(win->player->speed.x, win->player->speed.y));
        win->player->speed.x += 20;
    }
}

void check_interaction(window_t *win)
{
    sfVector2f pos_player = sfSprite_getPosition(win->player->sprite->sprite);
    sfVector2f pos_element = sfSprite_getPosition(win->scene[GAME].sprite[0].sprite);

    pos_element.x += 45;
    pos_element.y += 140;
    //printf("%f %f %f %f\n", pos_player.x, pos_player.y, pos_element.x, pos_element.y);
    if (pos_player.x > pos_element.x - 20 && pos_player.x < pos_element.x) {
        if (pos_player.y > pos_element.y - 20 && pos_player.y < pos_element.y + 20)
            win->page = HOUSE;
    }
}

void drag_button(window_t *win)
{
    sfVector2i click_pos = sfMouse_getPositionRenderWindow(win->window);
    int get_pos_volume = 800;
    int volume = 100;

    win->vol_drag_posx = click_pos.x;
    float diff_between_volume = win->vol_drag_posx - get_pos_volume; 
    char *str = malloc(sizeof(char) * 5);

    sfVector2f get_pos_four = sfRectangleShape_getPosition(win->scene[OPTIONS].button[4].shape);
    sfVector2f get_size_four = sfRectangleShape_getSize(win->scene[OPTIONS].button[4].shape);


    if (win->page == OPTIONS && click_pos.x > get_pos_four.x && click_pos.x < get_pos_four.x + get_size_four.x &&
        click_pos.y > get_pos_four.y && click_pos.y < get_pos_four.y + get_size_four.y) {
        if (win->vol_drag_posx >= VALUE_FIRST && win->vol_drag_posx <= 1056) {
            win->volume = (diff_between_volume + (get_pos_volume - VALUE_FIRST)) * 0.264;
            sfMusic_setVolume(win->menu_song, win->volume);
            sfMusic_setVolume(win->button_sound, win->volume);
            str = my_itc(win->volume);
            str = my_strcat(str, "%");
            sfText_setString(win->scene[OPTIONS].text[4].str, str);
            printf("volume is  = %d\n", win->volume);
            win->vol_drag_posx = click_pos.x - get_size_four.x / 2;
            sfRectangleShape_setPosition(win->scene[OPTIONS].button[4].shape, get_pos_float(win->vol_drag_posx, 800 - 250));
        }
    }
}

void check_out(window_t *win)
{
    sfVector2f pos_player = sfSprite_getPosition(win->player->sprite->sprite);

    printf("%f %f\n", pos_player.x, pos_player.y);
    if (pos_player.x >= 600 && pos_player.x < 620) {
        if (pos_player.y >= 700 && pos_player.y < 720)
            win->page = GAME;
    }
}

void global_event(window_t *win)
{
    sfVector2i click_pos = sfMouse_getPositionRenderWindow(win->window);

    if (win->event.type == sfEvtClosed)
        sfRenderWindow_close(win->window);
    if (win->event.type == sfEvtKeyPressed) {
        if (sfKeyboard_isKeyPressed(sfKeyEscape) == sfTrue)
            if (win->actual_page == MAINMENU)
                sfRenderWindow_close(win->window);
            if (win->actual_page == GAME)
                pause_game(win);
        if (win->page == GAME || win->page == HOUSE) {
            move_player(win);
            check_interaction(win);
            check_out(win);
        }
    }
    if (sfMouse_isButtonPressed(sfMouseLeft)) {
        if (win->actual_page == OPTIONS)
            drag_button(win);
    }
    if (win->event.type == sfEvtMouseButtonPressed)
        mouse_pressed_event(win);
    if (win->event.type == sfEvtMouseButtonReleased)
        mouse_released_event(win);
    if (win->event.type == sfEvtMouseMoved)
        mouse_moved_event(win);
    if (win->event.type == sfEvtKeyPressed)
        if (win->actual_page == GAME)
            check_keyboard_input_ingame(win);
}

void check_keyboard_input_ingame(window_t *win)
{
    if (sfKeyboard_isKeyPressed(sfKeyI)) {
        open_inventory(win);
    }
    if (sfKeyboard_isKeyPressed(sfKeyO)) {
        open_quests_menu(win);
    }
    if (sfKeyboard_isKeyPressed(sfKeyC)) {
        open_characteristics(win);
    }
}

void open_inventory(window_t *win)
{
    printf("inventory\n");
}

void open_quests_menu(window_t *win)
{
    printf("quests\n");
}

void open_characteristics(window_t *win)
{
    printf("chars\n");
}

void pause_game(window_t *win)
{
    printf("pause\n");
}