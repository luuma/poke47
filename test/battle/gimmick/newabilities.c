#include "global.h"
#include "test/battle.h"
#include "battle_ai_util.h"


SINGLE_BATTLE_TEST("wonderland sets wonder room")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_SIGILYPH) { Ability(ABILITY_WONDERLAND); MaxHP(263); HP(262); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_WONDER_ROOM); }
    } SCENE {
        ABILITY_POPUP(opponent, ABILITY_WONDERLAND);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WONDER_ROOM, opponent);
        MESSAGE("Wonder Room wore off, and all switched base stats returned to normal!");
    }
}

SINGLE_BATTLE_TEST("trickland sets trick room")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_MARSHADOW) { Ability(ABILITY_TRICKLAND); MaxHP(263); HP(262); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_TRICK_ROOM); }
    } SCENE {
        ABILITY_POPUP(opponent, ABILITY_TRICKLAND);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TRICK_ROOM, opponent);
        MESSAGE("The twisted dimensions returned to normal!");
    }
}

SINGLE_BATTLE_TEST("ITEM GET")
{
    GIVEN {
        PLAYER(SPECIES_TRUBBISH) { Ability(ABILITY_ITEM_GET); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { }
        TURN { MOVE(player, MOVE_FLING); }
        TURN { MOVE(player, MOVE_FLING); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_ITEM_GET);
        HP_BAR(opponent); // FLING HIT

        HP_BAR(opponent); // fling hit
    }
}


SINGLE_BATTLE_TEST("DOUBLE Wallop does hit twice under 3/4 hp")
{
    GIVEN {
        PLAYER(SPECIES_CRABOMINABLE) { Ability(ABILITY_DOUBLE_WALLOP); MaxHP(200); HP(200);}
        OPPONENT(SPECIES_WOBBUFFET) { MaxHP(200); HP(149);}
    } WHEN {
        TURN { MOVE(player, MOVE_POWER_UP_PUNCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POWER_UP_PUNCH, player);
        MESSAGE("Crabominable's Attack rose!");
        MESSAGE("Crabominable's Attack rose!");
	//MESSAGE("The Pokémon was hit 2 times!"); SIGH. 
    }
}


SINGLE_BATTLE_TEST("DOUBLE Wallop doesnt hit twice over 3/4 hp")
{
    GIVEN {
        PLAYER(SPECIES_CRABOMINABLE) { Ability(ABILITY_DOUBLE_WALLOP); MaxHP(200); HP(130);}
        OPPONENT(SPECIES_WOBBUFFET)  { MaxHP(200); HP(151);}
    } WHEN {
        TURN { MOVE(player, MOVE_POWER_UP_PUNCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_POWER_UP_PUNCH, player);
        MESSAGE("Crabominable's Attack rose!");
        NONE_OF {MESSAGE("The Pokémon was hit 2 time(s)!"); }
    }
}

SINGLE_BATTLE_TEST("Whiteout sets up hail for 8 turns with Icy Rock (Gen6-8)")
{
    GIVEN {
        PLAYER(SPECIES_KYUREM) { Moves(MOVE_CELEBRATE); Ability(ABILITY_WHITEOUT); Item(ITEM_ICY_ROCK); }
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_CELEBRATE); }
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_WHITEOUT);
        MESSAGE("The hail is crashing down.");
        MESSAGE("The hail is crashing down.");
        MESSAGE("The hail is crashing down.");
        MESSAGE("The hail is crashing down.");
        MESSAGE("The hail is crashing down.");
        MESSAGE("The hail is crashing down.");
        MESSAGE("The hail is crashing down.");
        MESSAGE("The hail stopped.");
    }
}

SINGLE_BATTLE_TEST("Constrictor Binding Band does 3/4")
{
    GIVEN {
        PLAYER(SPECIES_CARNIVINE) { Moves(MOVE_WRAP, MOVE_CELEBRATE); Ability(ABILITY_CONSTRICTOR); Item(ITEM_BINDING_BAND); }
        OPPONENT(SPECIES_WOBBUFFET) { Moves(MOVE_CELEBRATE); }
    } WHEN {
        TURN { MOVE(player, MOVE_WRAP); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WRAP, player);
        HP_BAR(opponent); // Direct damage
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage
        MESSAGE("The opposing Wobbuffet fainted!");
    }
}




SINGLE_BATTLE_TEST("7 TURN constrictor withOUT grip claw")
{
    GIVEN {
        PLAYER(SPECIES_CARNIVINE) { Moves(MOVE_WRAP, MOVE_CELEBRATE); Ability(ABILITY_CONSTRICTOR); }
        OPPONENT(SPECIES_WOBBUFFET){  Moves(MOVE_CELEBRATE); Item(ITEM_LEFTOVERS); }
    } WHEN {
        TURN { MOVE(player, MOVE_WRAP); MOVE(opponent, MOVE_CELEBRATE);}
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WRAP, player);
        HP_BAR(opponent); // Direct damage

        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage

        HP_BAR(opponent); // Residual Damage heal from leftovers
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage the tenth turn

        NOT HP_BAR(opponent); // Residual Damage
    }
}


SINGLE_BATTLE_TEST("Ice Bod passes and heals like leftovers.")
{
    GIVEN {
        PLAYER(SPECIES_CARNIVINE) { Moves(MOVE_WRAP, MOVE_CELEBRATE); Ability(ABILITY_CONSTRICTOR); }
        OPPONENT(SPECIES_AVALUGG){  Moves(MOVE_CELEBRATE); Ability(ABILITY_ICE_BODY); }
    } WHEN {
        TURN { MOVE(player, MOVE_WRAP); MOVE(opponent, MOVE_CELEBRATE);}
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_CELEBRATE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WRAP, player);
        HP_BAR(opponent); // Direct damage

        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage

        HP_BAR(opponent); // Residual Damage heal from leftovers
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage
        HP_BAR(opponent); // Residual Damage the tenth turn

        NOT HP_BAR(opponent); // Residual Damage
    }
}

SINGLE_BATTLE_TEST("Grand Debut grants damage reduction on switchin Vs not having grand debut", s16 damage)
{
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_DEFIANT; }
    PARAMETRIZE { ability = ABILITY_GRAND_DEBUT; }

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_PASSIMIAN) { Ability(ability); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN {MOVE(opponent, MOVE_POUND); SWITCH(player, 1);}
    } SCENE {
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, UQ_4_12(0.66), results[1].damage); // badabing
    }
}



SINGLE_BATTLE_TEST("FOCus boost test fails 1 million times.")
{
    GIVEN {
        PLAYER(SPECIES_WATCHOG) { Ability(ABILITY_FOCUS_BOOST); MaxHP(263); HP(262); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { }
        TURN { }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, player);
        ABILITY_POPUP(player, ABILITY_FOCUS_BOOST);
       // MESSAGE("Watchog's Staring Contest raised its Accuracy!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_CELEBRATE, player);
        ABILITY_POPUP(player, ABILITY_FOCUS_BOOST);
       // MESSAGE("Watchog's Staring Contest raised its Accuracy!");

    } THEN {
        EXPECT_EQ(player->statStages[STAT_ACC], DEFAULT_STAT_STAGE + 2);
    }
}


SINGLE_BATTLE_TEST("fPREcast raises satk EXClusively on form change.")
{
    GIVEN {
        PLAYER(SPECIES_DEERLING) { Ability(ABILITY_FORECAST); MaxHP(263); HP(262); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN {MOVE(opponent, MOVE_SUNNY_DAY); }
        TURN {MOVE(opponent, MOVE_SUNNY_DAY); }
        TURN { MOVE(opponent, MOVE_RAIN_DANCE); }
    } SCENE {
        ABILITY_POPUP(player, ABILITY_FORECAST);
        ABILITY_POPUP(player, ABILITY_FORECAST);
        ABILITY_POPUP(player, ABILITY_FORECAST);
        ABILITY_POPUP(player, ABILITY_FORECAST);
    } THEN {
        EXPECT_EQ(player->statStages[STAT_SPATK], DEFAULT_STAT_STAGE + 2);
    }
}



///GRAND DEBUT, ANALYTIC. NOT MOve relearner sadly.