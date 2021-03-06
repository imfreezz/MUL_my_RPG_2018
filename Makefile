##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## makefile for do_op
##

.RECIPEPREFIX +=

CC		:= gcc

NAME		:= my_rpg
FILES		:= main create_window display button get init_menu draw callback destroy event parser get_next_line init_sprite transform_2d init_choose_heroes init_options init_how_to\
                   options init_text move_rect choose_heroes init_castle init_town useful init_player init_inventory inventory init_objects init_quest init_forest init_final\
                   init_combat player init_music quests init_boss init_house_1 init_house_2 init_house_3 init_enemy init_end callback_attack callback_combat enemy_attack callback_play callback_menu\
                   callback_heroes check_inventory check_item_inventory interaction_game interaction_player map_swapper mouse_events talk_pnj move_player player_events key_pressed set_txt\
                   combat_starter animate_player map_swapper_final set_pos door volume draw_sprites str_to_unicode animate_mainmenu print_descriptions event_inventory vsync check_equipment\
                   blur_background check_error_parsing init_boss_sprites malloc_struct

SRC_NAMES 	:= $(addsuffix .c, $(FILES))
SRC		:= $(addprefix src/, $(SRC_NAMES))

CINC		:= -I include/
CFLAGS		:= -W -Wextra -Wall -pedantic -g
LDFLAGS		:= -L./lib/my -lmy -L./lib/printf -lprintf -lcsfml-graphics -lcsfml-audio -lcsfml-window -lcsfml-system

OBJ             := $(SRC:src/%.c=obj/%.o)

RED             := \033[0;31m
CYAN            := \033[0;36m
GOLD            := \033[0;33m
GREEN           := \033[0;32m
WHITE           := \033[0;0m

PREFIX		:= $(CYAN) "[$(NAME)]"

all:		createdir $(NAME)

obj/%.o: src/%.c
        @$(CC) -c $(CFLAGS) $(CINC) -o $@ $^
        @echo "$(PREFIX) $(GREEN)$^ $(GOLD)=> $(GREEN)$@"

$(NAME):        $(OBJ)
        @make -sC lib/my
        @make -sC lib/printf
        @echo "$(GOLD)Compiling...$(WHITE)\r"
        @gcc $(OBJ) -o $(NAME) $(CINC) $(CFLAGS) $(LDFLAGS)
        @echo "$(GOLD)Compiled !$(WHITE)"
        @echo "$(RED)Delete $(GOLD)$(PWD)/obj/*.o$(WHITE)"

clean:
        @echo "$(RED)Delete $(GOLD)$(PWD_PATH)/obj/*.o$(WHITE)"
        @rm -rf $(OBJ)

fclean:         clean
        @make -sC lib/my fclean
        @make -sC lib/printf fclean
        @echo "$(RED)Delete $(GOLD)$(PWD)/$(NAME)$(WHITE)"
        @rm -rf $(NAME)

re:             fclean all clean

createdir:
        @mkdir -p obj
