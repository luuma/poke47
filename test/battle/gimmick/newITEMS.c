#include "global.h"
#include "test/battle.h"
#include "battle_ai_util.h"

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



#include "global.h"
#include "test/battle.h"
#include "battle_ai_util.h"


SINGLE_BATTLE_TEST("Knell Bell causes opponent's moves to use up 4 PP not 1")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { MovesWithPP({MOVE_POUND, 35}); Item(ITEM_KNELL_BELL); }
        OPPONENT(SPECIES_WOBBUFFET) { }
    } WHEN {
        TURN { MOVE(player, MOVE_POUND); }
    } THEN {
        EXPECT_EQ(player->pp[0], 31);
    }
}

SINGLE_BATTLE_TEST("NORMAL PP")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { MovesWithPP({MOVE_POUND, 35}); }
        OPPONENT(SPECIES_WOBBUFFET) { }
    } WHEN {
        TURN { MOVE(player, MOVE_POUND); }
    } THEN {
        EXPECT_EQ(player->pp[0], 34);
    }
}


DOUBLE_BATTLE_TEST("Knell Bell causes opponent's moves to use 4 PP - TIMES 3 vs pressure. NORMAL pressure is *3.")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { MovesWithPP({MOVE_GROWL, 35}); Item(ITEM_KNELL_BELL); }
        PLAYER(SPECIES_WOBBUFFET) { MovesWithPP({MOVE_GROWL, 34}); }
        OPPONENT(SPECIES_WOBBUFFET) { }
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_PRESSURE); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_GROWL); MOVE(playerRight, MOVE_GROWL, target:opponentLeft); MOVE(opponentLeft, MOVE_CELEBRATE); MOVE(opponentRight, MOVE_CELEBRATE); }
    } THEN {
        EXPECT_EQ(playerLeft->pp[0], 23);
        EXPECT_EQ(playerRight->pp[0], 31);
    }
}

DOUBLE_BATTLE_TEST("Knell Bell causes opponent's moves to use 4 PP - TIMES 5 vs double pressure. NORMAL pressure is *5.")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { MovesWithPP({MOVE_GROWL, 35}); Item(ITEM_KNELL_BELL); }
        PLAYER(SPECIES_WOBBUFFET) { MovesWithPP({MOVE_GROWL, 34}); }
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_PRESSURE); }
        OPPONENT(SPECIES_WOBBUFFET) { Ability(ABILITY_PRESSURE); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_GROWL); MOVE(playerRight, MOVE_GROWL, target:opponentLeft); MOVE(opponentLeft, MOVE_CELEBRATE); MOVE(opponentRight, MOVE_CELEBRATE); }
    } THEN {
        EXPECT_EQ(playerLeft->pp[0], 15);
        EXPECT_EQ(playerRight->pp[0], 29);
    }
}

SINGLE_BATTLE_TEST("kNELL Bell restores 1/4 HP of damage dealt")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Level(40); Item(ITEM_KNELL_BELL); HP(10); }
        OPPONENT(SPECIES_WOBBUFFET) { Level(40); }
    } WHEN {
        TURN { MOVE(player, MOVE_SEISMIC_TOSS); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SEISMIC_TOSS, player);
        HP_BAR(opponent);
        HP_BAR(player, damage: -10);
    }
}

SINGLE_BATTLE_TEST("Wizard Cape deals 1/6 foe hp when fake tears is used, BUT NOT iron defense. Bounceables only")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Level(40); Item(ITEM_DAMAGE_BOUNCEABLES);}
        OPPONENT(SPECIES_WYNAUT) { Level(40); HP(60); MaxHP(120);  }
    } WHEN {
        TURN { MOVE(player, MOVE_IRON_DEFENSE); }
        TURN { MOVE(player, MOVE_FAKE_TEARS); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_IRON_DEFENSE, player);
        NONE_OF {
            HP_BAR(opponent);
        }
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FAKE_TEARS, player);
        HP_BAR(opponent, damage: 20);
    }
}


SINGLE_BATTLE_TEST("Wizard Cape TEST with message")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Level(40); Item(ITEM_DAMAGE_BOUNCEABLES);}
        OPPONENT(SPECIES_WYNAUT) { Level(40); HP(60); MaxHP(120);  }
    } WHEN {
        TURN { MOVE(player, MOVE_FAKE_TEARS); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FAKE_TEARS, player);
        HP_BAR(opponent, damage: 20);
	MESSAGE("The opposing Wynaut was hurt by Wobbuffet's Wizard Cape!");
    }
}

DOUBLE_BATTLE_TEST("Wizard Cape in doubles")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Level(40); Item(ITEM_DAMAGE_BOUNCEABLES);}
        PLAYER(SPECIES_WOBBUFFET) { }
        OPPONENT(SPECIES_WOBBUFFET)  { Level(40); HP(60); MaxHP(120);  }
        OPPONENT(SPECIES_WOBBUFFET)  { Level(65); HP(41); MaxHP(240);  }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_GROWL); MOVE(playerRight, MOVE_GROWL); MOVE(opponentLeft, MOVE_POUND, target: playerLeft); MOVE(opponentRight, MOVE_CELEBRATE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_GROWL, playerLeft);
        HP_BAR(opponentLeft, damage: 20);
        HP_BAR(opponentRight, damage: 40);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_GROWL, playerRight);
        NONE_OF {
            HP_BAR(opponentLeft);
            HP_BAR(opponentRight);
        }
    }
}

SINGLE_BATTLE_TEST("Wizard Cape deals no damage if fail")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Level(40); Item(ITEM_DAMAGE_BOUNCEABLES);}
        OPPONENT(SPECIES_GOGOAT) { Level(40); HP(60); MaxHP(120);  }
    } WHEN {
        TURN { MOVE(player, MOVE_SLEEP_POWDER); }
        TURN { MOVE(player, MOVE_THUNDER_WAVE); MOVE(opponent, MOVE_PROTECT); }
        TURN { MOVE(player, MOVE_THUNDER_WAVE); }
        TURN { MOVE(player, MOVE_THUNDER_WAVE); }
    } SCENE {
        NONE_OF {
            ANIMATION(ANIM_TYPE_MOVE, MOVE_SLEEP_POWDER, player);
            HP_BAR(opponent);
        }
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PROTECT, opponent);
        NONE_OF {
            HP_BAR(opponent);
        }
        ANIMATION(ANIM_TYPE_MOVE, MOVE_THUNDER_WAVE, player);
        HP_BAR(opponent, damage: 20);
        NONE_OF {
            ANIMATION(ANIM_TYPE_MOVE, MOVE_THUNDER_WAVE, player);
            HP_BAR(opponent);
        }
    }
}




SINGLE_BATTLE_TEST("wonder what happens here!")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Level(40); Item(ITEM_DAMAGE_BOUNCEABLES);}
        OPPONENT(SPECIES_WYNAUT) { Level(40); Ability(ABILITY_MAGIC_BOUNCE); Item(ITEM_DAMAGE_BOUNCEABLES); }
    } WHEN {
        TURN { MOVE(player, MOVE_FAKE_TEARS); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FAKE_TEARS, opponent);
    }
}



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

