/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** event2
*/

#include "../include/rpg.h"
#include "../include/my.h"

void mouse_pressed_event(window_t *win)
{
    sfVector2i click_pos = sfMouse_getPositionRenderWindow(win->window);
    sfRectangleShape *rect;

    printf("[x: %d, y: %d]\n", click_pos.x, click_pos.y);
    for (int i = 0; i < win->scene[win->actual_page].nb_button; i++) {
        rect = win->scene[win->actual_page].button[i].shape;
        if (button_is_clicked(win->scene[win->actual_page].button[i], click_pos)) {
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
        if (button_is_clicked(win->scene[win->actual_page].button[i], click_pos)) {
            sfRectangleShape_setTextureRect(rect, win->scene[win->actual_page].button[i].rect_idle);
            if (win->scene[win->actual_page].button[i].callback != NULL)
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

int open_buff(char *filename, char **buffer, int size)
{
    int fd = open(filename, O_RDONLY);

    if (fd < 0)
        return (84);
    if (read(fd, buffer[0], size) <= 0)
        return (84);
    buffer[0][size - 1] = '\0';
    close(fd);
    return (0);
}

int check_dead_zone(window_t *win, int move)
{
    static char **tab_castle = NULL;
    static char **tab_town = NULL;
    static char **tab_house1 = NULL;
    static char **tab_house2 = NULL;
    static char **tab_house3 = NULL;
    static char **tab_forest = NULL;
    static char **tab_final = NULL;
    static char **tab_boss = NULL;
    char **tab = NULL;
    sfVector2u size_win = sfRenderWindow_getSize(win->window);
    sfVector2f pos = sfSprite_getPosition(win->player->sprite->sprite);
    int scalex = size_win.x / 16;
    int scaley = size_win.y / 15;
    int x = pos.x / 16;
    int y = pos.y / 15;
    char *buffer_castle = malloc(sizeof(char) * 8400);
    char *buffer_town = malloc(sizeof(char) * 8400);
    char *buffer_house1 = malloc(sizeof(char) * 8400);
    char *buffer_house2 = malloc(sizeof(char) * 8400);
    char *buffer_house3 = malloc(sizeof(char) * 8400);
    char *buffer_forest = malloc(sizeof(char) * 8400);
    char *buffer_final = malloc(sizeof(char) * 8400);
    char *buffer_boss = malloc(sizeof(char) * 8400);

    if (tab_town == NULL || tab_castle == NULL || tab_house1 == NULL || tab_house2 == NULL || tab_house3 == NULL || tab_forest == NULL || tab_final == NULL || tab_boss == NULL) {
        if (open_buff("ressources/text/pos_castle", &buffer_castle, 8400) == 84)
            return (84);
        if (open_buff("ressources/text/pos_town", &buffer_town, 8400) == 84)
            return (84);
        if (open_buff("ressources/text/pos_house1", &buffer_house1, 8400) == 84)
            return (84);
        if (open_buff("ressources/text/pos_house2", &buffer_house2, 8400) == 84)
            return (84);
        if (open_buff("ressources/text/pos_house3", &buffer_house3, 8400) == 84)
            return (84);
        if (open_buff("ressources/text/pos_forest", &buffer_forest, 8400) == 84)
            return (84);
        if (open_buff("ressources/text/pos_final", &buffer_final, 8400) == 84)
            return (84);
        if (open_buff("ressources/text/pos_boss", &buffer_boss, 8400) == 84)
            return (84);
        if (buffer_town == NULL || buffer_castle == NULL || buffer_house1 == NULL || buffer_house2 == NULL || buffer_house3 == NULL || buffer_forest == NULL || buffer_final == NULL || buffer_boss == NULL)
            return (84);
        tab_castle = transform_2d(buffer_castle, '\n');
        tab_town = transform_2d(buffer_town, '\n');
        tab_house1 = transform_2d(buffer_house1, '\n');
        tab_house2 = transform_2d(buffer_house2, '\n');
        tab_house3 = transform_2d(buffer_house3, '\n');
        tab_forest = transform_2d(buffer_forest, '\n');
        tab_final = transform_2d(buffer_final, '\n');
        tab_boss = transform_2d(buffer_boss, '\n');
        if (tab_castle == NULL || tab_town == NULL || tab_house1 == NULL || tab_house2 == NULL || tab_house3 == NULL || tab_forest == NULL || tab_final == NULL || tab_boss)
            return (84);
    }
    if (win->actual_page == CASTLE)
        tab = tab_castle;
    if (win->actual_page == TOWN)
        tab = tab_town;
    if (win->actual_page == HOUSE1)
        tab = tab_house1;
    if (win->actual_page == HOUSE2)
        tab = tab_house2;
    if (win->actual_page == HOUSE3)
        tab = tab_house3;
    if (win->actual_page == FOREST)
        tab = tab_forest;
    if (win->actual_page == FINAL)
        tab = tab_final;
    if (win->actual_page == BOSS)
        tab = tab_boss;
    if (move == UP) {
        if (y - 1 >= 0 && tab[y - 1][x] == '2') {
            return (1);
        }
    }
    if (move == LEFT) {
        if (x - 1 >= 0 && tab[y][x - 1] == '2')
            return (1);
    }
    if (move == DOWN) {
        if (y + 1 < scaley - 1 && tab[y + 1][x] == '2')
            return (1);
    }
    if (move == RIGHT) {
        if (x + 1 < scalex - 2 && tab[y][x + 1] == '2')
            return (1);
    }
    return (0);
}

void move_player_up(window_t *win)
{
    if (check_dead_zone(win, UP) == 1) {
        if (win->player->direction != UP) {
            if (win->player->direction == DOWN)
                win->player->speed.y -= 5;
            if (win->player->direction == LEFT)
                win->player->speed.x += 5;
            if (win->player->direction == RIGHT)
                win->player->speed.x -= 5;
            win->player->direction = UP;
            win->player->sprite->rect.left = 15;
        }
        win->player->move_rect++;
        sfVector2f pos = sfSprite_getPosition(win->player->sprite->sprite);
        pos.y -= 5;
        sfSprite_setPosition(win->player->sprite->sprite, pos);
        win->player->sprite->rect.top = 159;
        if (win->player->sprite->rect.left > 111)
            win->player->sprite->rect.left = 15;
        sfSprite_setTextureRect(win->player->sprite->sprite, win->player->sprite->rect);
        if ((win->player->move_rect % 5) == 0)
            win->player->sprite->rect.left += 48;
    }
}

void move_player_down(window_t *win)
{
    if (check_dead_zone(win, DOWN) == 1) {
        if (win->player->direction != DOWN) {
            if (win->player->direction == UP)
                win->player->speed.y += 5;
            if (win->player->direction == LEFT)
                win->player->speed.x += 5;
            if (win->player->direction == RIGHT)
                win->player->speed.x -= 5;
            win->player->direction = DOWN;
            win->player->sprite->rect.left = 15;
        }
        win->player->move_rect++;
        sfVector2f pos = sfSprite_getPosition(win->player->sprite->sprite);        
        pos.y += 5;
        sfSprite_setPosition(win->player->sprite->sprite, pos);
        win->player->sprite->rect.top = 15;
        if (win->player->sprite->rect.left > 111)
            win->player->sprite->rect.left = 15;
        sfSprite_setTextureRect(win->player->sprite->sprite, win->player->sprite->rect);
        if ((win->player->move_rect % 5) == 0)
            win->player->sprite->rect.left += 48;
    }
}

void move_player_left(window_t *win)
{
    if (check_dead_zone(win, LEFT) == 1) {
        if (win->player->direction != LEFT) {
            if (win->player->direction == RIGHT)
                win->player->speed.x -= 5;
            if (win->player->direction == UP)
                win->player->speed.y += 5;
            if (win->player->direction == DOWN)
                win->player->speed.y -= 5;
            win->player->direction = LEFT;
            win->player->sprite->rect.left = 15;
        }
        win->player->move_rect++;
        sfVector2f pos = sfSprite_getPosition(win->player->sprite->sprite);        
        pos.x -= 5;
        sfSprite_setPosition(win->player->sprite->sprite, pos);
        win->player->sprite->rect.top = 62;
        if (win->player->sprite->rect.left > 111)
            win->player->sprite->rect.left = 15;
        sfSprite_setTextureRect(win->player->sprite->sprite, win->player->sprite->rect);
        if ((win->player->move_rect % 5) == 0)
            win->player->sprite->rect.left += 48;
    }
}

void move_player_right(window_t *win)
{
    if (check_dead_zone(win, RIGHT) == 1) {
        if (win->player->direction != RIGHT) {
            if (win->player->direction == LEFT)
                win->player->speed.x += 5;
            if (win->player->direction == UP)
                win->player->speed.y += 5;
            if (win->player->direction == DOWN)
                win->player->speed.y -= 5;
            win->player->direction = RIGHT;
            win->player->sprite->rect.left = 15;
        }
        win->player->move_rect++;
        sfVector2f pos = sfSprite_getPosition(win->player->sprite->sprite);        
        pos.x += 5;
        sfSprite_setPosition(win->player->sprite->sprite, pos);
        win->player->sprite->rect.top = 110;
        if (win->player->sprite->rect.left > 111)
            win->player->sprite->rect.left = 15;
        sfSprite_setTextureRect(win->player->sprite->sprite, win->player->sprite->rect);
        if ((win->player->move_rect % 5) == 0)
            win->player->sprite->rect.left += 48;
    }
}

void check_combat_zone(window_t *win)
{
    sfVector2f pos_player = sfSprite_getPosition(win->player->sprite->sprite);

    if (win->actual_page == FINAL) {
        if (is_inside_zone(get_pos_float(800, 680), get_pos_float(1200, 730), pos_player) == 1 && win->combat == 0) {
            win->player->last_pos = pos_player;
            win->combat += 1;
            win->page = COMBAT;
        }
        if (is_inside_zone(get_pos_float(800, 280), get_pos_float(1200, 330), pos_player) == 1 && win->combat == 1) {
            win->player->last_pos = pos_player;
            win->combat += 1;
            win->page = COMBAT;
        }
    }
    if (win->actual_page == BOSS) {
        if (is_inside_zone(get_pos_float(800, 0), get_pos_float(1200, 150), pos_player) == 1 && win->combat == 2) {
            win->player->last_pos = pos_player;
            win->combat += 1;
            win->page = COMBAT;
        }
    }
}

void leave_boss(window_t *win)
{
    sfVector2f pos_player = sfSprite_getPosition(win->player->sprite->sprite);

    if (is_inside_zone(get_pos_float(890, 950), get_pos_float(1100, 1100), pos_player) == 1) {
        sfSprite_setPosition(win->player->sprite->sprite, win->player->last_pos);
        win->page = FINAL;
    }
}

void go_boss(window_t *win)
{
    sfVector2f pos_player = sfSprite_getPosition(win->player->sprite->sprite);

    if (pos_player.x > 910 && pos_player.x < 1000) {
        if (pos_player.y < 100) {
            win->player->last_pos = sfSprite_getPosition(win->player->sprite->sprite);
            win->player->last_pos.y += 30;
            sfSprite_setPosition(win->player->sprite->sprite, get_pos_float(900, 950));
            win->page = BOSS;
        }
    }
}

void move_player(window_t *win)
{
    if (win->actual_page == TOWN)
        open_door(win);
    if (win->actual_page == HOUSE1 || win->actual_page == HOUSE2 || win->actual_page == HOUSE3)
        close_door(win);
    if (win->actual_page == FINAL)
        go_boss(win);
    if (win->actual_page == BOSS)
        leave_boss(win);
    check_item_pickup(win);
    close_textbox(win);
    check_combat_zone(win);
    if (sfKeyboard_isKeyPressed(sfKeyZ) == sfTrue || sfKeyboard_isKeyPressed(sfKeyUp) == sfTrue)
        move_player_up(win);
    else if (sfKeyboard_isKeyPressed(sfKeyQ) == sfTrue || sfKeyboard_isKeyPressed(sfKeyLeft) == sfTrue)
        move_player_left(win);
    else if (sfKeyboard_isKeyPressed(sfKeyS) == sfTrue || sfKeyboard_isKeyPressed(sfKeyDown) == sfTrue)
        move_player_down(win);
    else if (sfKeyboard_isKeyPressed(sfKeyD) == sfTrue || sfKeyboard_isKeyPressed(sfKeyRight) == sfTrue)
        move_player_right(win);
}

void go_forest(window_t *win)
{
    sfVector2f pos_player = sfSprite_getPosition(win->player->sprite->sprite);

    if (pos_player.x > 630 && pos_player.x < 1280) {
        if (pos_player.y > 950) {
            win->player->last_pos = sfSprite_getPosition(win->player->sprite->sprite);
            win->player->last_pos.y -= 30;
            sfSprite_setPosition(win->player->sprite->sprite, get_pos_float(pos_player.x, 50));
            win->page = FOREST;
        }
    }
}

void leave_final(window_t *win)
{
    sfVector2f pos_player = sfSprite_getPosition(win->player->sprite->sprite);

    if (is_inside_zone(get_pos_float(890, 950), get_pos_float(1100, 1100), pos_player) == 1) {
        sfSprite_setPosition(win->player->sprite->sprite, win->player->last_pos);
        win->page = TOWN;
    }
}

void go_town(window_t *win)
{
    sfVector2f pos_player = sfSprite_getPosition(win->player->sprite->sprite);

    if (pos_player.x > 825 && pos_player.x < 1050) {
        if (pos_player.y < 360) {
            win->player->last_pos = sfSprite_getPosition(win->player->sprite->sprite);
            win->player->last_pos.y += 30;
            sfSprite_setPosition(win->player->sprite->sprite, get_pos_float(900, 950));
            win->page = TOWN;
        }
    }
}

void drag_button(window_t *win)
{
    sfVector2i click_pos = sfMouse_getPositionRenderWindow(win->window);
    int get_pos_volume = 800;

    win->music->vol_drag_posx = click_pos.x;
    float diff_between_volume = win->music->vol_drag_posx - get_pos_volume; 
    char *str = malloc(sizeof(char) * 5);

    sfVector2f get_pos_four = sfRectangleShape_getPosition(win->scene[OPTIONS].button[4].shape);
    sfVector2f get_size_four = sfRectangleShape_getSize(win->scene[OPTIONS].button[4].shape);


    if (win->page == OPTIONS && click_pos.x > get_pos_four.x && click_pos.x < get_pos_four.x + get_size_four.x &&
        click_pos.y > get_pos_four.y && click_pos.y < get_pos_four.y + get_size_four.y) {
        if (win->music->vol_drag_posx >= VALUE_FIRST && win->music->vol_drag_posx <= 1056) {
            win->music->volume = (diff_between_volume + (get_pos_volume - VALUE_FIRST)) * 0.264;
            sfMusic_setVolume(win->music->menu_song, win->music->volume);
            sfMusic_setVolume(win->music->button_sound, win->music->volume);
            str = my_itc(win->music->volume);
            str = my_strcat(str, "%");
            sfText_setString(win->scene[OPTIONS].text[4].str, str);
            win->music->vol_drag_posx = click_pos.x - get_size_four.x / 2;
            sfRectangleShape_setPosition(win->scene[OPTIONS].button[4].shape, get_pos_float(win->music->vol_drag_posx, 800 - 250));
        }
    }
}

void go_castle(window_t *win)
{
    sfVector2f pos_player = sfSprite_getPosition(win->player->sprite->sprite);

    if (win->actual_page == TOWN) {
        if (pos_player.x >= 820 && pos_player.x < 1050) {
            if (pos_player.y >= 955) {
                win->page = CASTLE;
                sfSprite_setPosition(win->player->sprite->sprite, get_pos_float(900, 380));
            }
        }
    }
    if (win->actual_page == FOREST) {
        if (pos_player.x >= 630 && pos_player.x < 1280) {
            if (pos_player.y <= 20) {
                win->page = CASTLE;
                sfSprite_setPosition(win->player->sprite->sprite, get_pos_float(900, 900));
            }
        }
    }
}

void open_inventory(window_t *win)
{
    win->pause = 1;
    win->inventory = 1;
    if (win->actual_page == TOWN) {
        for (int i = 1; i < win->scene[TOWN].nb_sprite; i++)
            win->scene[TOWN].sprite[i].depth = -1;
    }
}

void close_door(window_t *win)
{
    sfVector2f pos_player = sfSprite_getPosition(win->player->sprite->sprite);

    if (is_inside_zone(get_pos_float(880, 750), get_pos_float(935, 850), pos_player) == 1) {
        sfSprite_setPosition(win->player->sprite->sprite, win->player->last_pos);
        win->page = TOWN;
    }
}

void go_final(window_t *win)
{
    sfVector2f pos_player = sfSprite_getPosition(win->player->sprite->sprite);
    sfIntRect rect;
    sfVector2f pos_door;

    rect = sfSprite_getTextureRect(win->scene[TOWN].sprite[4].sprite);
    pos_door = sfSprite_getPosition(win->scene[TOWN].sprite[4].sprite);
    if (pos_player.x >= pos_door.x - 20 && pos_player.x <= pos_door.x + 40) {
        if (pos_player.y >= pos_door.y && pos_player.y <= pos_door.y + 100) {
            rect.top = 192;
            sfSprite_setTextureRect(win->scene[TOWN].sprite[4].sprite, rect);
        } else {
            if (rect.top >= 64) {
                rect.top = 128;
                sfSprite_setTextureRect(win->scene[TOWN].sprite[4].sprite, rect);
            }
        }
        if (pos_player.y >= pos_door.y - 50 && pos_player.y <= pos_door.y + 20 && win->player->direction == UP) {
            win->player->last_pos = get_pos_float(1025, 150);
            sfSprite_setPosition(win->player->sprite->sprite, get_pos_float(950, 900));
            win->page = FINAL;
        }
    } else {
        if (rect.top >= 64) {
            rect.top = 128;
            sfSprite_setTextureRect(win->scene[TOWN].sprite[4].sprite, rect);
        }
    }
}