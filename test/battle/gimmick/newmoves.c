#include "global.h"
#include "test/battle.h"
#include "battle_ai_util.h"


SINGLE_BATTLE_TEST("eNVELOP uses special defense stat of target", s16 damage)
{
    enum Move move;

    PARAMETRIZE { move = MOVE_DRILL_PECK; }
    PARAMETRIZE { move = MOVE_BODY_PRESS; }

    GIVEN {
        ASSUME(GetMovePower(MOVE_DRILL_PECK) == GetMovePower(MOVE_BODY_PRESS));
        ASSUME(GetMoveEffect(MOVE_CHARM) == EFFECT_ATTACK_DOWN_2);
        PLAYER(SPECIES_MEW);
        OPPONENT(SPECIES_SHELLDER);
    } WHEN {
        TURN { MOVE(opponent, MOVE_CHARM); MOVE(player, move); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, move, player);
        HP_BAR(opponent, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_MUL_EQ(results[0].damage, Q_4_12(2.0), results[1].damage);
    }
}

SINGLE_BATTLE_TEST("ENVELOP's damage depends on the user's base Defense instead of its base Attack", s16 damage)
{
    u32 spdef, spatk;
    PARAMETRIZE { spdef = 150; spatk = 179; } // Atk is higher
    PARAMETRIZE { spatk = 150; spdef = 179; } // Atk is lower
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET) { SpAttack(spatk); SpDefense(spdef); }
    } WHEN {
        TURN { MOVE(opponent, MOVE_ENVELOP); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ENVELOP, opponent);
        HP_BAR(player, captureDamage: &results[i].damage);
    } FINALLY {
        EXPECT_GT(results[1].damage, results[0].damage);
    }
}



DOUBLE_BATTLE_TEST("Just Desserts recycles allies' berries 100% of the time")
{
    GIVEN {
        ASSUME(MoveHasAdditionalEffect(MOVE_JUST_DESSERTS, MOVE_EFFECT_RECYCLE_BERRIES));
        ASSUME(GetItemHoldEffect(ITEM_APICOT_BERRY) == HOLD_EFFECT_SP_DEFENSE_UP);
        PLAYER(SPECIES_SNORLAX) { Item(ITEM_APICOT_BERRY); GigantamaxFactor(TRUE); }
        PLAYER(SPECIES_MUNCHLAX) { Item(ITEM_APICOT_BERRY); Ability(ABILITY_THICK_FAT); }
        OPPONENT(SPECIES_WOBBUFFET) { Item(ITEM_APICOT_BERRY); }
        OPPONENT(SPECIES_WOBBUFFET) { Item(ITEM_APICOT_BERRY); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_STUFF_CHEEKS); \
               MOVE(playerRight, MOVE_STUFF_CHEEKS); \
               MOVE(opponentLeft, MOVE_STUFF_CHEEKS); \
               MOVE(opponentRight, MOVE_STUFF_CHEEKS); }
        TURN { MOVE(playerLeft, MOVE_JUST_DESSERTS, target: opponentRight); }
    } SCENE {
        // turn 1

        MESSAGE("Using Apicot Berry, the Sp. Def of Snorlax rose!");
        MESSAGE("Using Apicot Berry, the Sp. Def of Munchlax rose!");
        MESSAGE("Using Apicot Berry, the Sp. Def of the opposing Wobbuffet rose!");
        MESSAGE("Using Apicot Berry, the Sp. Def of the opposing Wobbuffet rose!");
        // turn 2
        MESSAGE("Snorlax used Just Desserts!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_JUST_DESSERTS, playerLeft);
        MESSAGE("Snorlax found one Apicot Berry!");
        MESSAGE("Munchlax found one Apicot Berry!");
    }
}


SINGLE_BATTLE_TEST("Lightbloom SUNlight")
{
    GIVEN {
        ASSUME(MoveHasAdditionalEffect(MOVE_LIGHTBLOOM, MOVE_EFFECT_SUN));
        OPPONENT(SPECIES_WOBBUFFET);
        PLAYER(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_LIGHTBLOOM); MOVE(opponent, MOVE_CELEBRATE); }
    } SCENE {
        MESSAGE("Wobbuffet used Light Bloom!");
        MESSAGE("The sunlight turned harsh!");
        MESSAGE("The opposing Wobbuffet used Celebrate!");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_SUN_CONTINUES);
    }
}


SINGLE_BATTLE_TEST("Mood Crush replaces target's ability with dEFEATIST")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_TELEPATHY); }
        OPPONENT(SPECIES_CHARMANDER) { Ability(ABILITY_BLAZE); }
    }WHEN {
        TURN { MOVE(player, MOVE_MOOD_CRUSH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MOOD_CRUSH, player);
        ABILITY_POPUP(opponent, ABILITY_BLAZE);
    } THEN {
        EXPECT_EQ(opponent->ability, ABILITY_DEFEATIST);
    }
}

DOUBLE_BATTLE_TEST("mood Crush STILL damages if target is defeatist")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { Ability(ABILITY_TELEPATHY); }
        PLAYER(SPECIES_CHARMANDER) { Ability(ABILITY_BLAZE); }
        OPPONENT(SPECIES_BULBASAUR) { Ability(ABILITY_OVERGROW); }
        OPPONENT(SPECIES_SQUIRTLE) { Ability(ABILITY_TORRENT); }
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_MOOD_CRUSH, target: opponentLeft); MOVE(playerRight, MOVE_MOOD_CRUSH, target: opponentLeft); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MOOD_CRUSH, playerLeft);
        HP_BAR(opponentLeft);
        ABILITY_POPUP(opponentLeft, ABILITY_OVERGROW);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MOOD_CRUSH, playerRight);
        HP_BAR(opponentLeft);
        NONE_OF {
            ABILITY_POPUP(opponentLeft, ABILITY_DEFEATIST);
        }
    } THEN {
        EXPECT_EQ(opponentLeft->ability, ABILITY_DEFEATIST);
    }
}


DOUBLE_BATTLE_TEST("hawkeye boosts crit chance by 1 stage")
{
    u32 j;
    GIVEN {
        WITH_CONFIG(B_CRIT_CHANCE, GEN_6);
        ASSUME(MoveHasAdditionalEffect(MOVE_CRIT_UP_HIT, MOVE_EFFECT_CRIT_PLUS_SIDE));
        PLAYER(SPECIES_MACHAMP) { GigantamaxFactor(TRUE); }
        PLAYER(SPECIES_MACHOP);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_CRIT_UP_HIT, target: opponentLeft); }
        TURN { MOVE(playerLeft, MOVE_CRIT_UP_HIT, target: opponentLeft); }
        TURN { MOVE(playerLeft, MOVE_CRIT_UP_HIT, target: opponentLeft); \
               MOVE(playerRight, MOVE_FOCUS_ENERGY); }
        TURN { MOVE(playerRight, MOVE_SCRATCH, target: opponentLeft); }
    } SCENE {
        // turn 1 - 3
        for (j = 0; j < 3; ++j) {
            MESSAGE("Machamp used Hawkeye!");
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, playerLeft);
            MESSAGE("Machamp is getting pumped!");
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, playerRight);
            MESSAGE("Machop is getting pumped!");
        }
        // turn 4
        MESSAGE("Machop used Scratch!"); // Machop is at +5 crit stages
        MESSAGE("A critical hit!");
    }
}

DOUBLE_BATTLE_TEST("Screen Burn makes the user lose 1/2 of its Max HP in a double battle")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { HP(201); MaxHP(400); }
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_SCREEN_BURN); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCREEN_BURN);
        HP_BAR(playerLeft, damage: 200);
        NOT MESSAGE("Wobbuffet fainted!"); // Wobb had more than 1/2 of its HP, so it can't faint.
    }
}

DOUBLE_BATTLE_TEST("Screen Burn causes the user to faint when below 1/2 of its Max HP in a double battle")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET) { HP(200); MaxHP(400); }
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_SCREEN_BURN); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCREEN_BURN, playerLeft);
        HP_BAR(playerLeft, hp: 0);
        MESSAGE("Wobbuffet fainted!");
    }
}


SINGLE_BATTLE_TEST("Screen Burn's Reflect applies for 5 turns")
{
    s16 damage[6];
    GIVEN {
        ASSUME(GetMoveCategory(MOVE_SCRATCH) == DAMAGE_CATEGORY_PHYSICAL);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCREEN_BURN); MOVE(opponent, MOVE_SCRATCH); }
        TURN { MOVE(opponent, MOVE_SCRATCH); }
        TURN { MOVE(opponent, MOVE_SCRATCH); }
        TURN { MOVE(opponent, MOVE_SCRATCH); }
        TURN { MOVE(opponent, MOVE_SCRATCH); }
        TURN { MOVE(opponent, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCREEN_BURN, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, opponent);
        HP_BAR(player, captureDamage: &damage[0]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, opponent);
        HP_BAR(player, captureDamage: &damage[1]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, opponent);
        HP_BAR(player, captureDamage: &damage[2]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, opponent);
        HP_BAR(player, captureDamage: &damage[3]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, opponent);
        HP_BAR(player, captureDamage: &damage[4]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, opponent);
        HP_BAR(player, captureDamage: &damage[5]);
    } THEN {
        EXPECT_MUL_EQ(damage[0], Q_4_12(1.0), damage[1]);
        EXPECT_MUL_EQ(damage[0], Q_4_12(1.0), damage[2]);
        EXPECT_MUL_EQ(damage[0], Q_4_12(1.0), damage[3]);
        EXPECT_MUL_EQ(damage[0], Q_4_12(1.0), damage[4]);
        EXPECT_LT(damage[0], damage[5]);
    }
}


SINGLE_BATTLE_TEST("Screen Burn's Light Screen applies for 5 turns")
{
    s16 damage[6];
    GIVEN {
        ASSUME(GetMoveCategory(MOVE_WATER_GUN) == DAMAGE_CATEGORY_SPECIAL);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCREEN_BURN); MOVE(opponent, MOVE_WATER_GUN); }
        TURN { MOVE(opponent, MOVE_WATER_GUN); }
        TURN { MOVE(opponent, MOVE_WATER_GUN); }
        TURN { MOVE(opponent, MOVE_WATER_GUN); }
        TURN { MOVE(opponent, MOVE_WATER_GUN); }
        TURN { MOVE(opponent, MOVE_WATER_GUN); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCREEN_BURN, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WATER_GUN, opponent);
        HP_BAR(player, captureDamage: &damage[0]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WATER_GUN, opponent);
        HP_BAR(player, captureDamage: &damage[1]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WATER_GUN, opponent);
        HP_BAR(player, captureDamage: &damage[2]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WATER_GUN, opponent);
        HP_BAR(player, captureDamage: &damage[3]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WATER_GUN, opponent);
        HP_BAR(player, captureDamage: &damage[4]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WATER_GUN, opponent);
        HP_BAR(player, captureDamage: &damage[5]);
    } THEN {
        EXPECT_MUL_EQ(damage[0], Q_4_12(1.0), damage[1]);
        EXPECT_MUL_EQ(damage[0], Q_4_12(1.0), damage[2]);
        EXPECT_MUL_EQ(damage[0], Q_4_12(1.0), damage[3]);
        EXPECT_MUL_EQ(damage[0], Q_4_12(1.0), damage[4]);
        EXPECT_LT(damage[0], damage[5]);
    }
}

SINGLE_BATTLE_TEST("Reflect fails if screen burn already active")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCREEN_BURN); }
        TURN { MOVE(player, MOVE_REFLECT); }
        TURN { MOVE(player, MOVE_LIGHT_SCREEN); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCREEN_BURN, player);
        MESSAGE("Wobbuffet used Reflect!");
        MESSAGE("But it failed!");
        MESSAGE("Wobbuffet used Light Screen!");
        MESSAGE("But it failed!");
    }
}

SINGLE_BATTLE_TEST("SCREEN BURN DOESN't fail if reflect's active")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_REFLECT); }
        TURN { MOVE(player, MOVE_SCREEN_BURN); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_REFLECT, player);
        MESSAGE("Wobbuffet used Screen Burn!");
	NOT MESSAGE("But it failed!");
    }
}


SINGLE_BATTLE_TEST("SCREEN BURN fails if screen burn already active.")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_SCREEN_BURN); }
        TURN { MOVE(player, MOVE_SCREEN_BURN); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCREEN_BURN, player);
        MESSAGE("Wobbuffet used Screen Burn!");
        MESSAGE("But it failed!");
    }
}

SINGLE_BATTLE_TEST("SCREEN BURN fails if screen burn already active")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_REFLECT); }
        TURN { MOVE(player, MOVE_LIGHT_SCREEN); }
        TURN { MOVE(player, MOVE_SCREEN_BURN); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_REFLECT, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_LIGHT_SCREEN, player);
        MESSAGE("Wobbuffet used Screen Burn!");
        MESSAGE("But it failed!");
    }
}


SINGLE_BATTLE_TEST("Emergency Exit will trigger due to recoil damage from screen burn")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_GOLISOPOD) { Ability(ABILITY_EMERGENCY_EXIT); MaxHP(263); HP(262); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(opponent, MOVE_SCREEN_BURN); SEND_OUT(opponent,1); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCREEN_BURN, opponent);
        HP_BAR(opponent);
        ABILITY_POPUP(opponent, ABILITY_EMERGENCY_EXIT);
    }
}

DOUBLE_BATTLE_TEST("Rototiller boosts Attack and Special Attack of all Grass types on the field")
{
    GIVEN {
        ASSUME(GetSpeciesType(SPECIES_TANGELA, 0) == TYPE_GRASS);
        ASSUME(GetSpeciesType(SPECIES_SNIVY, 0) == TYPE_GRASS);
        PLAYER(SPECIES_TANGELA);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_SNIVY);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(playerRight, MOVE_ROTOTILLER); MOVE(playerLeft, MOVE_CELEBRATE); MOVE(opponentLeft, MOVE_CELEBRATE); MOVE(opponentRight, MOVE_CELEBRATE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_ROTOTILLER, playerRight);
        NOT ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, playerRight);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, playerLeft);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponentLeft);
        NOT ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponentRight);
    } THEN {
        EXPECT_EQ(playerLeft->statStages[STAT_ATK], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ(playerLeft->statStages[STAT_DEF], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ(opponentLeft->statStages[STAT_SPDEF], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ(opponentLeft->statStages[STAT_ATK], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ(opponentLeft->statStages[STAT_DEF], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ(opponentLeft->statStages[STAT_SPDEF], DEFAULT_STAT_STAGE + 1);
        EXPECT_EQ(playerRight->statStages[STAT_ATK], DEFAULT_STAT_STAGE);
        EXPECT_EQ(playerRight->statStages[STAT_DEF], DEFAULT_STAT_STAGE);
        EXPECT_EQ(opponentRight->statStages[STAT_ATK], DEFAULT_STAT_STAGE);
        EXPECT_EQ(opponentRight->statStages[STAT_DEF], DEFAULT_STAT_STAGE);
    }
}


DOUBLE_BATTLE_TEST("Flower Shield sharply raises the sp defense of all Grass-type Pokémon")
{
    GIVEN {
        ASSUME(GetSpeciesType(SPECIES_TANGELA, 0) == TYPE_GRASS);
        ASSUME(GetSpeciesType(SPECIES_TANGROWTH, 0) == TYPE_GRASS);
        ASSUME(GetSpeciesType(SPECIES_SUNKERN, 0) == TYPE_GRASS);
        ASSUME(GetSpeciesType(SPECIES_SUNFLORA, 0) == TYPE_GRASS);
        PLAYER(SPECIES_TANGELA);
        PLAYER(SPECIES_TANGROWTH);
        OPPONENT(SPECIES_SUNKERN);
        OPPONENT(SPECIES_SUNFLORA);
    } WHEN {
        TURN { MOVE(playerLeft, MOVE_FLOWER_SHIELD); MOVE(playerRight, MOVE_CELEBRATE); }
    } SCENE {
        MESSAGE("Tangela used Flower Shield!");
        ANIMATION(ANIM_TYPE_MOVE, MOVE_FLOWER_SHIELD, playerLeft);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, playerLeft);
        MESSAGE("Tangela's Sp. Def sharply rose!");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponentLeft);
        MESSAGE("The opposing Sunkern's Sp. Def sharply rose!");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, playerRight);
        MESSAGE("Tangrowth's Sp. Def sharply rose!");
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponentRight);
        MESSAGE("The opposing Sunflora's Sp. Def sharply rose!");
    }
}


SINGLE_BATTLE_TEST("Laser Focus causes the user's move used on the next turn to result in a Critical Hit")
{
    GIVEN {
        ASSUME(GetMoveEffect(MOVE_LASER_FOCUS) == EFFECT_LASER_FOCUS);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_LASER_FOCUS); }
        TURN { MOVE(player, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_LASER_FOCUS, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        MESSAGE("A critical hit!");
    }
}

SINGLE_BATTLE_TEST("Laser Focus Sure Hit for all moves")
{
    PASSES_RANDOMLY(100, 100, RNG_ACCURACY);
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_LASER_FOCUS); }
        TURN { MOVE(player, MOVE_HYPNOSIS); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HYPNOSIS, player);
    }
}

SINGLE_BATTLE_TEST("Laser Focus Sure Hit lasts one turn")
{
    PASSES_RANDOMLY(60, 100, RNG_ACCURACY);
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_LASER_FOCUS); }
        TURN { MOVE(player, MOVE_CELEBRATE); }
        TURN { MOVE(player, MOVE_HYPNOSIS); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_HYPNOSIS, player);
    }
}


SINGLE_BATTLE_TEST("Miracle Eye removes Dark-type immunity to Psychic-type moves")
{
    GIVEN {
        ASSUME(GetMoveType(MOVE_PSYCHIC) == TYPE_PSYCHIC);
        ASSUME(GetSpeciesType(SPECIES_UMBREON, 0) == TYPE_DARK);
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_MIRACLE_EYE, MOVE_PSYCHIC); }
        OPPONENT(SPECIES_UMBREON) { Moves(MOVE_SPLASH); }
    } WHEN {
        TURN { MOVE(player, MOVE_PSYCHIC); MOVE(opponent, MOVE_SPLASH); }
        TURN { MOVE(player, MOVE_MIRACLE_EYE); MOVE(opponent, MOVE_SPLASH); }
        TURN { MOVE(player, MOVE_PSYCHIC); MOVE(opponent, MOVE_SPLASH); }
    } SCENE {
        NOT HP_BAR(opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MIRACLE_EYE, player);
        HP_BAR(opponent);
    }
}


SINGLE_BATTLE_TEST("Miracle Eye removes Steel-type immunity to Poison-type moves")
{
    GIVEN {
        ASSUME(GetMoveType(MOVE_SLUDGE_BOMB) == TYPE_POISON);
        ASSUME(GetSpeciesType(SPECIES_CUFANT, 0) == TYPE_STEEL);
        PLAYER(SPECIES_WOBBUFFET) { Moves(MOVE_MIRACLE_EYE, MOVE_SLUDGE_BOMB); }
        OPPONENT(SPECIES_CUFANT) { Moves(MOVE_SPLASH); }
    } WHEN {
        TURN { MOVE(player, MOVE_SLUDGE_BOMB); MOVE(opponent, MOVE_SPLASH); }
        TURN { MOVE(player, MOVE_MIRACLE_EYE); MOVE(opponent, MOVE_SPLASH); }
        TURN { MOVE(player, MOVE_SLUDGE_BOMB); MOVE(opponent, MOVE_SPLASH); }
    } SCENE {
        NOT HP_BAR(opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MIRACLE_EYE, player);
        HP_BAR(opponent);
    }
}


SINGLE_BATTLE_TEST("Tar Shot doubles the effectiveness of Fire-type moves used on the target AND sharply lowers speed")
{
    s16 damage[2];
    u32 species;

    PARAMETRIZE { species = SPECIES_WOBBUFFET; }
    PARAMETRIZE { species = SPECIES_OMASTAR; } // Dual type with double resists

    ASSUME(GetSpeciesType(SPECIES_WOBBUFFET, 0) == TYPE_PSYCHIC);
    ASSUME(GetSpeciesType(SPECIES_WOBBUFFET, 1) == TYPE_PSYCHIC);
    ASSUME(GetSpeciesType(SPECIES_OMASTAR, 0) == TYPE_ROCK);
    ASSUME(GetSpeciesType(SPECIES_OMASTAR, 1) == TYPE_WATER);
    ASSUME(GetMoveType(MOVE_EMBER) == TYPE_FIRE);

    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(species);
    } WHEN {
        TURN { MOVE(player, MOVE_EMBER); }
        TURN { MOVE(player, MOVE_TAR_SHOT); }
        TURN { MOVE(player, MOVE_EMBER); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_EMBER, player);
        HP_BAR(opponent, captureDamage: &damage[0]);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TAR_SHOT, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_EMBER, player);
        HP_BAR(opponent, captureDamage: &damage[1]);
        if (species != SPECIES_OMASTAR)
            MESSAGE("It's super effective!");
        else
            MESSAGE("It's not very effective…");
    } THEN {
        EXPECT_MUL_EQ(damage[0], Q_4_12(2.0), damage[1]);
        EXPECT_EQ(opponent->statStages[STAT_SPEED], DEFAULT_STAT_STAGE - 2);
    }
}


SINGLE_BATTLE_TEST("Toxic THREAD inflicts bad poison AND sharply lowers speed")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_TOXIC_THREAD); }
        TURN {}
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_TOXIC_THREAD, player);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_PSN, opponent);
        STATUS_ICON(opponent, badPoison: TRUE);
    } THEN {
        EXPECT_EQ(opponent->statStages[STAT_SPEED], DEFAULT_STAT_STAGE - 2);
    }
}

SINGLE_BATTLE_TEST("Mist blocks secondary effects")
{
    enum Move move;
    PARAMETRIZE { move = MOVE_NUZZLE; }
    PARAMETRIZE { move = MOVE_INFERNO; }
    PARAMETRIZE { move = MOVE_MORTAL_SPIN; }
    PARAMETRIZE { move = MOVE_ROCK_TOMB; }
    PARAMETRIZE { move = MOVE_SPIRIT_SHACKLE; }
    PARAMETRIZE { move = MOVE_PSYCHIC_NOISE; }

    GIVEN {
        ASSUME(MoveHasAdditionalEffectWithChance(MOVE_NUZZLE, MOVE_EFFECT_PARALYSIS, 100) == TRUE);
        ASSUME(MoveHasAdditionalEffectWithChance(MOVE_INFERNO, MOVE_EFFECT_BURN, 100) == TRUE);
        ASSUME(MoveHasAdditionalEffectWithChance(MOVE_MORTAL_SPIN, MOVE_EFFECT_POISON, 100) == TRUE);
        //ASSUME(MoveHasAdditionalEffectWithChance(MOVE_FAKE_OUT, MOVE_EFFECT_FLINCH, 100) == TRUE);
        ASSUME(MoveHasAdditionalEffectWithChance(MOVE_ROCK_TOMB, MOVE_EFFECT_SPD_MINUS_1, 100) == TRUE);
        ASSUME(MoveHasAdditionalEffectWithChance(MOVE_SPIRIT_SHACKLE, MOVE_EFFECT_PREVENT_ESCAPE, 100) == TRUE);
        ASSUME(MoveHasAdditionalEffectWithChance(MOVE_PSYCHIC_NOISE, MOVE_EFFECT_PSYCHIC_NOISE, 100) == TRUE);
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_CELEBRATE); MOVE(opponent, MOVE_MIST); }
        TURN { MOVE(player, move); MOVE(opponent, MOVE_CELEBRATE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_MIST, opponent);
        ANIMATION(ANIM_TYPE_MOVE, move, player);
        HP_BAR(opponent);
        NONE_OF {
            MESSAGE("The opposing Wobbuffet is paralyzed, so it may be unable to move!");
            MESSAGE("The opposing Wobbuffet was burned!");
            MESSAGE("The opposing Wobbuffet was poisoned!");
            MESSAGE("The opposing Wobbuffet flinched and couldn't move!");
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
            MESSAGE("The opposing Wobbuffet was prevented from healing!");
        }
    } THEN { // Can't find good way to test trapping
        EXPECT(!opponent->volatiles.escapePrevention);
    }
}
