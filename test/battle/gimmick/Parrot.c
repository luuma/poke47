#include "global.h"
#include "test/battle.h"


SINGLE_BATTLE_TEST("Dancer can copy a dance move immediately after it was used and allow the user of Dancer to still use its move")
{
    GIVEN {
        ASSUME(IsDanceMove(MOVE_QUIVER_DANCE));
        PLAYER(SPECIES_WOBBUFFET)
        OPPONENT(SPECIES_ORICORIO) { Ability(ABILITY_DANCER); }
    } WHEN {
        TURN { MOVE(player, MOVE_QUIVER_DANCE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_QUIVER_DANCE, player);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        ABILITY_POPUP(opponent, ABILITY_DANCER);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_QUIVER_DANCE, opponent);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent); // Same turn
    }
}

SINGLE_BATTLE_TEST("Dancer can copy Teeter Dance")
{
    GIVEN {
        ASSUME(IsDanceMove(MOVE_TEETER_DANCE));
        PLAYER(SPECIES_WOBBUFFET)
        OPPONENT(SPECIES_ORICORIO) { Ability(ABILITY_DANCER); Item(ITEM_LUM_BERRY); }
    } WHEN {
        TURN { MOVE(player, MOVE_TEETER_DANCE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TEETER_DANCE, player);
        ABILITY_POPUP(opponent, ABILITY_DANCER);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TEETER_DANCE, opponent);
    }
}

DOUBLE_BATTLE_TEST("Dancer can copy Teeter Dance and confuse both opposing targets")
{
    GIVEN {
        ASSUME(IsDanceMove(MOVE_TEETER_DANCE));
        ASSUME(gItemsInfo[ITEM_LUM_BERRY].holdEffect == HOLD_EFFECT_CURE_STATUS);
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WYNAUT) { Item(ITEM_LUM_BERRY); }
        OPPONENT(SPECIES_ORICORIO) { Ability(ABILITY_DANCER); Item(ITEM_LUM_BERRY); }
        OPPONENT(SPECIES_SLOWPOKE) { Ability(ABILITY_OWN_TEMPO); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_TEETER_DANCE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TEETER_DANCE, playerLeft);
        ABILITY_POPUP(opponentLeft, ABILITY_DANCER);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TEETER_DANCE, opponentLeft);
        MESSAGE("Wobbuffet became confused!");
        MESSAGE("Wynaut became confused!");
    }
}


SINGLE_BATTLE_TEST("Parrot can copy a dance move immediately after it was used and allow the user of PARROT to still use its move")
{
    GIVEN {
        ASSUME(IsDanceMove(MOVE_QUIVER_DANCE));
        PLAYER(SPECIES_WOBBUFFET)
        OPPONENT(SPECIES_CHATOT) { Ability(ABILITY_PARROT); }
    } WHEN {
        TURN { MOVE(player, MOVE_HOWL); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HOWL, player);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, player);
        ABILITY_POPUP(opponent, ABILITY_PARROT);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HOWL, opponent);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, opponent); // Same turn
    }
}

SINGLE_BATTLE_TEST("PARROT doesn't trigger if the original user flinches")
{
    GIVEN {
        ASSUME(MoveHasAdditionalEffectWithChance(MOVE_FAKE_OUT, MOVE_EFFECT_FLINCH, 100));
        ASSUME(IsDanceMove(MOVE_DRAGON_DANCE));
        PLAYER(SPECIES_WOBBUFFET)
        OPPONENT(SPECIES_CHATOT) { Ability(ABILITY_PARROT); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_FAKE_OUT); MOVE(player, MOVE_ECHOED_VOICE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FAKE_OUT, opponent);
        MESSAGE("Wobbuffet flinched and couldn't move!");
        NONE_OF {
            ABILITY_POPUP(opponent, ABILITY_PARROT);
            ANIMATION(ANIM_TYPE_MOVE, MOVE_ECHOED_VOICE, opponent);
        }
    }
}

DOUBLE_BATTLE_TEST("PARROT still triggers if another PARROT flinches")
{
    GIVEN {
        ASSUME(MoveHasAdditionalEffectWithChance(MOVE_FAKE_OUT, MOVE_EFFECT_FLINCH, 100));
        PLAYER(SPECIES_CHATOT) { Ability(ABILITY_PARROT); Speed(10); }
        PLAYER(SPECIES_WYNAUT) { Speed(5); }
        OPPONENT(SPECIES_CHATOT) { Ability(ABILITY_PARROT); Speed(20); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(3); }
    } WHEN {
        TURN { MOVE(opponentLeft, MOVE_FAKE_OUT, target: playerLeft); MOVE(playerRight, MOVE_CLANGOROUS_SOUL); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FAKE_OUT, opponentLeft);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CLANGOROUS_SOUL, playerRight);
        ABILITY_POPUP(playerLeft, ABILITY_PARROT);
        MESSAGE("Chatot flinched and couldn't move!");
        NONE_OF {
            MESSAGE("Chatot used Clangorous Soul!");
            ANIMATION(ANIM_TYPE_MOVE, MOVE_CLANGOROUS_SOUL, playerLeft);
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, playerLeft);
        }
        ABILITY_POPUP(opponentLeft, ABILITY_PARROT);
        MESSAGE("The opposing Chatot used Clangorous Soul!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CLANGOROUS_SOUL, opponentLeft);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponentLeft);
    }
}


SINGLE_BATTLE_TEST("PARROT-called attacks do not trigger Life Orb if target is immune")
{
    GIVEN {
        ASSUME(GetItemHoldEffect(ITEM_LIFE_ORB) == HOLD_EFFECT_LIFE_ORB);
        PLAYER(SPECIES_WHISMUR) { Ability(ABILITY_SOUNDPROOF); }
        OPPONENT(SPECIES_CHATOT) { Ability(ABILITY_PARROT); Item(ITEM_LIFE_ORB); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_ROOST); MOVE(player, MOVE_BOOMBURST); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_BOOMBURST, player);
        ABILITY_POPUP(opponent, ABILITY_PARROT);
        NOT ANIMATION(ANIM_TYPE_MOVE, MOVE_BOOMBURST, opponent);
        ABILITY_POPUP(player, ABILITY_SOUNDPROOF);
        NOT HP_BAR(opponent);
    }
}

DOUBLE_BATTLE_TEST("PARROT doesn't trigger on a snatched move")
{
    GIVEN {
        ASSUME(IsDanceMove(MOVE_CLANGOROUS_SOUL));
        ASSUME(GetMoveEffect(MOVE_SNATCH) == EFFECT_SNATCH);
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WYNAUT);
        OPPONENT(SPECIES_CHATOT) { Ability(ABILITY_PARROT);}; 
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponentRight, MOVE_SNATCH); MOVE(playerRight, MOVE_CLANGOROUS_SOUL); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SNATCH, opponentRight);
        NOT ANIMATION(ANIM_TYPE_MOVE, MOVE_CLANGOROUS_SOUL, playerRight);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CLANGOROUS_SOUL, opponentRight);
        NONE_OF {
            ABILITY_POPUP(opponentLeft, ABILITY_PARROT);
            ANIMATION(ANIM_TYPE_MOVE, MOVE_CLANGOROUS_SOUL, opponentLeft);
        }
    }
}

DOUBLE_BATTLE_TEST("PARROT doesn't trigger when an ally snatches the move")
{
    GIVEN {
        ASSUME(IsDanceMove(MOVE_DRAGON_DANCE));
        ASSUME(GetMoveEffect(MOVE_SNATCH) == EFFECT_SNATCH);
        ASSUME(MoveCanBeSnatched(MOVE_DRAGON_DANCE));
        PLAYER(SPECIES_WOBBUFFET) { Speed(30); }
        PLAYER(SPECIES_WOBBUFFET) { Speed(20); }
        OPPONENT(SPECIES_CHATOT) { Ability(ABILITY_PARROT); Speed(10); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(5); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_SNATCH); MOVE(opponentRight, MOVE_CLANGOROUS_SOUL); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SNATCH, playerLeft);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CLANGOROUS_SOUL, playerLeft);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, playerLeft);
        NONE_OF {
            ABILITY_POPUP(opponentLeft, ABILITY_PARROT);
            ANIMATION(ANIM_TYPE_MOVE, MOVE_CLANGOROUS_SOUL, opponentLeft);
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponentLeft);
        }
    }
}

DOUBLE_BATTLE_TEST("PARROT-called moves doesn't update move to be called by Mirror Move")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Speed(10); }
        PLAYER(SPECIES_WOBBUFFET) { Speed(30); }
        OPPONENT(SPECIES_CHATOT) { Ability(ABILITY_PARROT); Speed(50); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(5); }
    } WHEN {
        TURN { MOVE(opponentLeft, MOVE_SCRATCH, target: playerLeft); MOVE(playerRight, MOVE_SING, target: opponentRight); }
        TURN { MOVE(playerLeft, MOVE_MIRROR_MOVE, target: opponentLeft); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, opponentLeft);
        HP_BAR(playerLeft);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SING, playerRight);
        ABILITY_POPUP(opponentLeft, ABILITY_PARROT);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SING, opponentLeft);
        MESSAGE("Wobbuffet used Mirror Move!");
        MESSAGE("Wobbuffet used Scratch!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, playerLeft);
        NOT MESSAGE("Wobbuffet used Sing!");
    }
}


SINGLE_BATTLE_TEST("PARROT can still copy a move even if it's being forced into a different move - Choice items")
{
    GIVEN {
        ASSUME(IsDanceMove(MOVE_SWORDS_DANCE));
        ASSUME(GetItemHoldEffect(ITEM_CHOICE_BAND) == HOLD_EFFECT_CHOICE_BAND);
        PLAYER(SPECIES_WOBBUFFET) { Speed(30); }
        OPPONENT(SPECIES_CHATOT) { Ability(ABILITY_PARROT); Speed(10); Item(ITEM_CHOICE_BAND); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_SCRATCH); }
        TURN { MOVE(player, MOVE_HEAL_BELL); MOVE(opponent, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, opponent);
        HP_BAR(player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HEAL_BELL, player);
        ABILITY_POPUP(opponent, ABILITY_PARROT);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HEAL_BELL, opponent);
    }
}



DOUBLE_BATTLE_TEST("PARROT copies parting shot and both users switch successfully.")
{
    GIVEN {
        WITH_CONFIG(B_HEALING_WISH_SWITCH, GEN_7);
        ASSUME(GetMoveEffect(MOVE_LUNAR_DANCE) == EFFECT_LUNAR_DANCE);
        PLAYER(SPECIES_RIOLU) { Speed(50); }
        PLAYER(SPECIES_CHATOT) { Ability(ABILITY_PARROT); Speed(20); }
        PLAYER(SPECIES_WYNAUT) { Speed(5); }
        PLAYER(SPECIES_CHANSEY) { Speed(5); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(10); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(10); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_PARTING_SHOT, target:opponentRight); SEND_OUT(playerLeft, 2); SEND_OUT(playerRight, 3); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PARTING_SHOT, playerLeft);
        MESSAGE("Wobbuffet's Attack fell!");
        ABILITY_POPUP(playerRight, ABILITY_PARROT);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PARTING_SHOT, playerRight);
        MESSAGE("Wobbuffet's Attack fell!");
        SEND_IN_MESSAGE("Wynaut");
        SEND_IN_MESSAGE("Chansey");
    }
}



SINGLE_BATTLE_TEST("PARROT roar")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Speed(30); }
        PLAYER(SPECIES_WOBBUFFET) { Speed(30); }
        OPPONENT(SPECIES_CHATOT) { Ability(ABILITY_PARROT); Speed(10); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(30); }
    } WHEN {
        TURN { MOVE(player, MOVE_ROAR);}
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ROAR, player);
        MESSAGE("The opposing Wobbuffet was dragged out!");
    }
}


DOUBLE_BATTLE_TEST("PARROT roar doubles")
{
    GIVEN {
        WITH_CONFIG(B_HEALING_WISH_SWITCH, GEN_7);
        ASSUME(GetMoveEffect(MOVE_LUNAR_DANCE) == EFFECT_LUNAR_DANCE);
        PLAYER(SPECIES_RIOLU) { Speed(50); }
        PLAYER(SPECIES_CHATOT) { Ability(ABILITY_PARROT); Speed(20); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(10); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(10); }
        OPPONENT(SPECIES_WYNAUT) { Speed(5); }
        OPPONENT(SPECIES_CHANSEY) { Speed(5); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_ROAR, target:opponentRight); SEND_OUT(opponentRight, 2); SEND_OUT(opponentRight, 3); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ROAR, playerLeft);
        MESSAGE("The opposing Chansey was dragged out!");
        ABILITY_POPUP(playerRight, ABILITY_PARROT);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ROAR, playerRight);
        MESSAGE("The opposing Wynaut was dragged out!");
    }
}
