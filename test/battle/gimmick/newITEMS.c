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

SINGLE_BATTLE_TEST("EvioliUM INgot boosts Defense and Sp. Def for unevolved rock or ice Pokemon", s16 damage)
{
    u16 move;
    u32 item;

    PARAMETRIZE { move = MOVE_PURSUIT;   item = ITEM_EVIUM_INGOT; }
    PARAMETRIZE { move = MOVE_PURSUIT;   item = ITEM_NONE; }
    PARAMETRIZE { move = MOVE_POWDER_SNOW; item = ITEM_EVIUM_INGOT; }
    PARAMETRIZE { move = MOVE_POWDER_SNOW; item = ITEM_NONE; }

    GIVEN {
        ASSUME(GetMoveCategory(MOVE_PURSUIT) == DAMAGE_CATEGORY_PHYSICAL);
        ASSUME(GetMoveCategory(MOVE_POWDER_SNOW) == DAMAGE_CATEGORY_SPECIAL);
        PLAYER(SPECIES_AMAURA) { Item(item); }
        OPPONENT(SPECIES_GRAVELER) { Moves(MOVE_PURSUIT, MOVE_POWDER_SNOW); }
    } WHEN {
        TURN { MOVE(opponent, move); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, move, opponent);
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(2.0), results[1].damage);
        EXPECT_MUL_EQ(results[2].damage, Q_4_12(2.0), results[3].damage);
    }
}

SINGLE_BATTLE_TEST("EvioliUM INgot boosts Defense and Sp. Def for unevolved ice Pokemon", s16 damage)
{
    u16 move;
    u32 item;

    PARAMETRIZE { move = MOVE_PURSUIT;   item = ITEM_EVIUM_INGOT; }
    PARAMETRIZE { move = MOVE_PURSUIT;   item = ITEM_NONE; }
    PARAMETRIZE { move = MOVE_WATER_GUN; item = ITEM_EVIUM_INGOT; }
    PARAMETRIZE { move = MOVE_WATER_GUN; item = ITEM_NONE; }

    GIVEN {
        ASSUME(GetMoveCategory(MOVE_PURSUIT) == DAMAGE_CATEGORY_PHYSICAL);
        ASSUME(GetMoveCategory(MOVE_POWDER_SNOW) == DAMAGE_CATEGORY_SPECIAL);
        PLAYER(SPECIES_VANILLITE) { Item(item); }
        OPPONENT(SPECIES_GRAVELER) { Moves(MOVE_PURSUIT, MOVE_WATER_GUN); }
    } WHEN {
        TURN { MOVE(opponent, move); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, move, opponent);
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(2.0), results[1].damage);
        EXPECT_MUL_EQ(results[2].damage, Q_4_12(2.0), results[3].damage);
    }
}

SINGLE_BATTLE_TEST("EvioliUM INgot does not boost Defense or Sp. Def for evolved Pokemon", s16 damage)
{
    u16 move;
    u32 item;

    PARAMETRIZE { move = MOVE_SCRATCH;   item = ITEM_EVIUM_INGOT; }
    PARAMETRIZE { move = MOVE_SCRATCH;   item = ITEM_NONE; }
    PARAMETRIZE { move = MOVE_WATER_GUN; item = ITEM_EVIUM_INGOT; }
    PARAMETRIZE { move = MOVE_WATER_GUN; item = ITEM_NONE; }

    GIVEN {
        ASSUME(GetMoveCategory(MOVE_SCRATCH) == DAMAGE_CATEGORY_PHYSICAL);
        ASSUME(GetMoveCategory(MOVE_WATER_GUN) == DAMAGE_CATEGORY_SPECIAL);
        PLAYER(SPECIES_GOLEM) { Item(item); }
        OPPONENT(SPECIES_MAGIKARP) { Moves(MOVE_SCRATCH, MOVE_WATER_GUN); }
    } WHEN {
        TURN { MOVE(opponent, move); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, move, opponent);
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.0), results[1].damage);
        EXPECT_MUL_EQ(results[2].damage, Q_4_12(1.0), results[3].damage);
    }
}

SINGLE_BATTLE_TEST("EvioliUM INgot does not boost Defense or Sp. Def for NON ROCK Pokemon", s16 damage)
{
    u16 move;
    u32 item;

    PARAMETRIZE { move = MOVE_SCRATCH;   item = ITEM_EVIUM_INGOT; }
    PARAMETRIZE { move = MOVE_SCRATCH;   item = ITEM_NONE; }
    PARAMETRIZE { move = MOVE_WATER_GUN; item = ITEM_EVIUM_INGOT; }
    PARAMETRIZE { move = MOVE_WATER_GUN; item = ITEM_NONE; }

    GIVEN {
        ASSUME(GetMoveCategory(MOVE_SCRATCH) == DAMAGE_CATEGORY_PHYSICAL);
        ASSUME(GetMoveCategory(MOVE_WATER_GUN) == DAMAGE_CATEGORY_SPECIAL);
        PLAYER(SPECIES_PIKACHU) { Item(item); }
        OPPONENT(SPECIES_MAGIKARP) { Moves(MOVE_SCRATCH, MOVE_WATER_GUN); }
    } WHEN {
        TURN { MOVE(opponent, move); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, move, opponent);
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(1.0), results[1].damage);
        EXPECT_MUL_EQ(results[2].damage, Q_4_12(1.0), results[3].damage);
    }
}


DOUBLE_BATTLE_TEST("Eviopolymer 1.5x for nfe, 1.1X for full evolved")
{
    GIVEN {
        PLAYER(SPECIES_GEODUDE) { Speed(100); Item(ITEM_EVIOPOLYMER); }
        PLAYER(SPECIES_GOLEM) { Speed(110); Item(ITEM_EVIOPOLYMER); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(149); }
        OPPONENT(SPECIES_WOBBUFFET) { Speed(151); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_CELEBRATE); MOVE(opponentLeft, MOVE_CELEBRATE); MOVE(opponentRight, MOVE_CELEBRATE);  }
    } SCENE {
        MESSAGE("The opposing Wobbuffet used Celebrate!");
        MESSAGE("Geodude used Celebrate!");
        MESSAGE("The opposing Wobbuffet used Celebrate!");
        MESSAGE("Golem used Celebrate!");
    }
}

