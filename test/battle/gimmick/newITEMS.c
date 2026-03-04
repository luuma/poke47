#include "global.h"
#include "test/battle.h"
#include "battle_ai_util.h"


SINGLE_BATTLE_TEST("SPANDEX flares set electric terrain")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_SPANDEX_FLARES); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_DRAGON_DANCE); }
        TURN { MOVE(player, MOVE_DRAGON_DANCE); MOVE(opponent, MOVE_SPORE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DRAGON_DANCE, player);
        MESSAGE("An electric current ran across the battlefield!");
        MESSAGE("The opposing Wobbuffet used Spore!");
        MESSAGE("Wobbuffet surrounds itself with electrified terrain!");
    }
}

SINGLE_BATTLE_TEST("SPANDEX flares set electric terrain 5 turn")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_SPANDEX_FLARES); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_DRAGON_DANCE); }
        TURN {}
        TURN {}
        TURN {}
        TURN {}
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_DRAGON_DANCE, player);
        MESSAGE("An electric current ran across the battlefield!");

        MESSAGE("The electricity disappeared from the battlefield.");
    }
}


SINGLE_BATTLE_TEST("SPANDEX flares doesn't when not dancing")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Item(ITEM_SPANDEX_FLARES); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_RAIN_DANCE); }
        TURN { MOVE(player, MOVE_RAIN_DANCE); MOVE(opponent, MOVE_SPORE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_RAIN_DANCE, player);
        MESSAGE("The opposing Wobbuffet used Spore!");
        STATUS_ICON(player, sleep: TRUE);

    }
}

