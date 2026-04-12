#include "global.h"
#include "test/battle.h"

SINGLE_BATTLE_TEST("Spicy Spray inflicts burn if attacker is damaged")
{
    enum Move move;
    PARAMETRIZE { move = MOVE_SCRATCH; }
    PARAMETRIZE { move = MOVE_SWIFT; }
    GIVEN {
        ASSUME(MoveMakesContact(MOVE_SCRATCH));
        ASSUME(!MoveMakesContact(MOVE_SWIFT));
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_SCOVILLAIN) { Ability(ABILITY_SPICY_SPRAY); }
    } WHEN {
        TURN { MOVE(player, move); }
    } SCENE {
        ABILITY_POPUP(opponent, ABILITY_SPICY_SPRAY);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_BRN, player);
        STATUS_ICON(player, burn: TRUE);
    }
}

SINGLE_BATTLE_TEST("Spicy Spray triggers a message when it fails to burn due to a burn immunity")
{
    GIVEN {
        ASSUME(GetMoveType(MOVE_FURY_SWIPES) == TYPE_NORMAL);
        ASSUME(IsMultiHitMove(MOVE_FURY_SWIPES));
        PLAYER(SPECIES_MAGMAR);
        OPPONENT(SPECIES_SCOVILLAIN) { Ability(ABILITY_SPICY_SPRAY); }
    } WHEN {
        TURN { MOVE(player, MOVE_FURY_SWIPES); }
    } SCENE {
        ABILITY_POPUP(opponent, ABILITY_SPICY_SPRAY);
        NOT ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_BRN, player);
        MESSAGE("It doesn't affect Magmar…");
        NOT STATUS_ICON(player, burn: TRUE);
    }
}
