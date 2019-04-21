/*
** EPITECH PROJECT, 2019
** MUL_my_rpg_2018
** File description:
** init_quest
*/

#include "../include/rpg.h"
#include "../include/my.h"

void init_quests(quest_t *quest)
{
    init_sprite(&quest->sprite[0], "ressources/old_paper.png", get_pos_float(240, 50));
    init_sprite(&quest->sprite[1], "ressources/pack/rpg-pack/UI/generic-rpg-ui-text-box.png", get_pos_float(800, 50));
    init_sprite(&quest->sprite[2], "ressources/buttons/Checkbox.png", get_pos_float(1400, 150));
    init_sprite(&quest->sprite[3], "ressources/buttons/Checkbox.png", get_pos_float(1400, 350));
    init_sprite(&quest->sprite[4], "ressources/buttons/Checkbox.png", get_pos_float(1400, 550));
    init_sprite(&quest->sprite[5], "ressources/buttons/Checkbox.png", get_pos_float(1400, 750));
    sfSprite_setScale(quest->sprite[1].sprite, get_pos_float(3, 3));
    sfSprite_setScale(quest->sprite[2].sprite, get_pos_float(0.2, 0.2));
    sfSprite_setScale(quest->sprite[3].sprite, get_pos_float(0.2, 0.2));
    sfSprite_setScale(quest->sprite[4].sprite, get_pos_float(0.2, 0.2));
    sfSprite_setScale(quest->sprite[5].sprite, get_pos_float(0.2, 0.2));
    quest->sprite[1].depth = -1;
    quest->sprite[2].depth = -1;
    init_text(&quest->text[0], "QUETE 1:    Aller parler au grand pere\n", get_pos_float(300, 150));
    init_text(&quest->text[1], "Bonjour\n", get_pos_float(0, 0));
    init_text(&quest->text[2], "QUETE 2:    Trouver l'epee du grand pere\n", get_pos_float(300, 350));
    init_text(&quest->text[3], "QUETE 3:    Trouver l'armure du grand pere\n", get_pos_float(300, 550));
    init_text(&quest->text[4], "QUETE 4:    Aller combattre le mechant\n", get_pos_float(300, 750));
}