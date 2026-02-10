#include "global.h"
#include "test/battle.h"

ASSUMPTIONS
{
    // ASSUME(GetMoveCategory(MOVE_AERIAL_ACE) == DAMAGE_CATEGORY_PHYSICAL);
}

SINGLE_BATTLE_TEST("(Gulp Missile) If base DRIFBLIM hits target with Surf it transforms into Gulping form if max HP is over 1/2")
{
    GIVEN {
        PLAYER(SPECIES_DRIFBLIM) { Ability(ABILITY_GULP_MISSILE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_STOCKPILE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_STOCKPILE, player);
        ABILITY_POPUP(player, ABILITY_GULP_MISSILE);
    } THEN {
        EXPECT_EQ(player->species, SPECIES_DRIFBLIM_YAMASK);
    }
}

SINGLE_BATTLE_TEST("(Gulp Missile) If base DRIFBLIM hits target with Surf it transforms into Gorging form if max HP is under 1/2")
{
    GIVEN {
        PLAYER(SPECIES_DRIFBLIM) { HP(120); MaxHP(250); Ability(ABILITY_GULP_MISSILE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_STOCKPILE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_STOCKPILE, player);
        ABILITY_POPUP(player, ABILITY_GULP_MISSILE);
    } THEN {
        EXPECT_EQ(player->species, SPECIES_DRIFBLIM_LITWICK);
    }
}

SINGLE_BATTLE_TEST("(Gulp Missile) If base DRIFBLIM is under water it transforms into one of its forms")
{
    GIVEN {
        PLAYER(SPECIES_DRIFBLIM) { Ability(ABILITY_GULP_MISSILE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_PHANTOM_FORCE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PHANTOM_FORCE, player);
        NOT HP_BAR(opponent);
        ABILITY_POPUP(player, ABILITY_GULP_MISSILE);
    } THEN {
        EXPECT_EQ(player->species, SPECIES_DRIFBLIM_YAMASK);
    }
}

SINGLE_BATTLE_TEST("(Gulp Missile) Power Herb does not prevent Cramaront from transforming")
{
    GIVEN {
        PLAYER(SPECIES_DRIFBLIM) { Ability(ABILITY_GULP_MISSILE); Item(ITEM_POWER_HERB); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_PHANTOM_FORCE); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_PHANTOM_FORCE, player);
        MESSAGE("Drifblim became fully charged due to its Power Herb!");
        ABILITY_POPUP(player, ABILITY_GULP_MISSILE);
        HP_BAR(opponent);
    } THEN {
        EXPECT_EQ(player->species, SPECIES_DRIFBLIM_YAMASK);
    }
}

SINGLE_BATTLE_TEST("(Gulp Missile) Transformed DRIFBLIM deal 1/4 of damage opposing mon if hit by a damaging move, Gulping also lowers defense")
{
    s16 gulpMissileDamage;

    GIVEN {
        PLAYER(SPECIES_DRIFBLIM) { Ability(ABILITY_GULP_MISSILE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_STOCKPILE); MOVE(opponent, MOVE_WATER_GUN); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_STOCKPILE, player);
        ABILITY_POPUP(player, ABILITY_GULP_MISSILE);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WATER_GUN, opponent);
        HP_BAR(player);
        ABILITY_POPUP(player, ABILITY_GULP_MISSILE);
        HP_BAR(opponent, captureDamage: &gulpMissileDamage);
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
        MESSAGE("The opposing Wobbuffet's Defense fell!");
    } THEN {
        EXPECT_EQ(gulpMissileDamage, opponent->maxHP / 4);
        EXPECT_EQ(opponent->statStages[STAT_DEF], DEFAULT_STAT_STAGE - 1);
    }
}

SINGLE_BATTLE_TEST("(Gulp Missile) DRIFBLIM in LITWICK form BURNs the target if hit by a damaging move")
{
    GIVEN {
        PLAYER(SPECIES_DRIFBLIM) { HP(120); MaxHP(250); Ability(ABILITY_GULP_MISSILE); }
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_STOCKPILE); MOVE(opponent, MOVE_WATER_GUN); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_STOCKPILE, player);
        ABILITY_POPUP(player, ABILITY_GULP_MISSILE);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WATER_GUN, opponent);
        HP_BAR(player);
        ABILITY_POPUP(player, ABILITY_GULP_MISSILE);
        HP_BAR(opponent);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_BRN, opponent);
        STATUS_ICON(opponent, burn: TRUE);
    }
}

SINGLE_BATTLE_TEST("(Gulp Missile) DRIFBLIM in LITWICK form DOESN'T BURN FIRE TYPE WITH NO CRASH")
{
    GIVEN {
        PLAYER(SPECIES_DRIFBLIM) { HP(120); MaxHP(250); Ability(ABILITY_GULP_MISSILE); }
        OPPONENT(SPECIES_HEATMOR);
    } WHEN {
        TURN { MOVE(player, MOVE_STOCKPILE); MOVE(opponent, MOVE_WATER_GUN); }
        TURN { MOVE(player, MOVE_STOCKPILE); MOVE(opponent, MOVE_WATER_GUN); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_STOCKPILE, player);
        ABILITY_POPUP(player, ABILITY_GULP_MISSILE);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WATER_GUN, opponent);
        HP_BAR(player);
        ABILITY_POPUP(player, ABILITY_GULP_MISSILE);
        HP_BAR(opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_STOCKPILE, player);
        ABILITY_POPUP(player, ABILITY_GULP_MISSILE);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WATER_GUN, opponent);
        HP_BAR(player);
        ABILITY_POPUP(player, ABILITY_GULP_MISSILE);
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("(Gulp Missile) triggers even if the user is fainted by opposing mon")
{
    GIVEN {
        PLAYER(SPECIES_DRIFBLIM) { HP(1); MaxHP(250); Ability(ABILITY_GULP_MISSILE); }
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_WOBBUFFET);
    } WHEN {
        TURN { MOVE(player, MOVE_STOCKPILE); MOVE(opponent, MOVE_WATER_GUN); SEND_OUT(player, 1); }
        TURN { MOVE(player, MOVE_STOCKPILE); MOVE(opponent, MOVE_WATER_GUN); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_STOCKPILE, player);
        ABILITY_POPUP(player, ABILITY_GULP_MISSILE);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WATER_GUN, opponent);
        HP_BAR(player);
        ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_BRN, opponent);
        STATUS_ICON(opponent, burn: TRUE);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_STOCKPILE, player);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WATER_GUN, opponent);
        HP_BAR(player);
    }
}

SINGLE_BATTLE_TEST("(Gulp Missile) Transformed DRIFBLIM Gulping lowers defense but is prevented by stat reduction preventing abilities")
{
    u32 species;
    enum Ability ability;
    PARAMETRIZE { species = SPECIES_METAGROSS; ability = ABILITY_CLEAR_BODY; }
    PARAMETRIZE { species = SPECIES_CORVIKNIGHT; ability = ABILITY_MIRROR_ARMOR; }
    //PARAMETRIZE { species = SPECIES_CHATOT; ability = ABILITY_BIG_PECKS; }
    GIVEN {
        PLAYER(SPECIES_DRIFBLIM) { Ability(ABILITY_GULP_MISSILE); }
        OPPONENT(species) { Ability(ability); HP(9999); MaxHP(9999); } // In Gen 5 data, Surf would be enough to knock out Chatot
    } WHEN {
        TURN { MOVE(player, MOVE_STOCKPILE); MOVE(opponent, MOVE_WATER_GUN); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_STOCKPILE, player);
        ABILITY_POPUP(player, ABILITY_GULP_MISSILE);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WATER_GUN, opponent);
        HP_BAR(player);
        ABILITY_POPUP(player, ABILITY_GULP_MISSILE);
        ABILITY_POPUP(opponent, ability);
        NOT ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
    } THEN {
        EXPECT_EQ(opponent->statStages[STAT_DEF], DEFAULT_STAT_STAGE);
    }
}

SINGLE_BATTLE_TEST("(Gulp Missile) Transformed DRIFBLIM Gulping lowers defense and still triggers other effects after")
{
    // Make sure attacker and target are correct after triggering the ability
    enum Ability ability;
    PARAMETRIZE { ability = ABILITY_INFILTRATOR; }
    PARAMETRIZE { ability = ABILITY_CLEAR_BODY; }
    GIVEN {
        ASSUME(MoveMakesContact(MOVE_WATER_GUN));
        PLAYER(SPECIES_DRIFBLIM) { Ability(ABILITY_GULP_MISSILE); Item(ITEM_ROCKY_HELMET); }
        OPPONENT(SPECIES_DRAGAPULT) { Ability(ability); }
    } WHEN {
        TURN { MOVE(player, MOVE_STOCKPILE); MOVE(opponent, MOVE_WATER_GUN); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_STOCKPILE, player);
        ABILITY_POPUP(player, ABILITY_GULP_MISSILE);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_WATER_GUN, opponent);
        HP_BAR(player);
        ABILITY_POPUP(player, ABILITY_GULP_MISSILE);
        HP_BAR(opponent);
        if (ability == ABILITY_INFILTRATOR) {
            ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_STATS_CHANGE, opponent);
            MESSAGE("The opposing Dragapult's Defense fell!");
        } else {
            ABILITY_POPUP(opponent, ABILITY_CLEAR_BODY);
        }
        ANIMATION(ANIM_TYPE_GENERAL, B_ANIM_HELD_ITEM_EFFECT, player);
        HP_BAR(opponent);
    }
}

SINGLE_BATTLE_TEST("Gulp Missile triggered by explosion doesn't freeze the game")
{
    GIVEN {
        PLAYER(SPECIES_WOBBUFFET);
        OPPONENT(SPECIES_DRIFBLIM);
    } WHEN {
        TURN { MOVE(opponent, MOVE_STOCKPILE); MOVE(player, MOVE_EXPLOSION); }
    }
}

SINGLE_BATTLE_TEST("(Gulp Missile) Cramorant in Gorging damages an electric type without paralysing")
{
    GIVEN {
        PLAYER(SPECIES_CRAMORANT) { HP(120); MaxHP(250); Ability(ABILITY_GULP_MISSILE); }
        OPPONENT(SPECIES_EELEKTROSS);
    } WHEN {
        TURN { MOVE(player, MOVE_SURF); MOVE(opponent, MOVE_SCRATCH); }
        TURN { MOVE(player, MOVE_SCRATCH); MOVE(opponent, MOVE_SCRATCH); }
    } SCENE {
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SURF, player);
        HP_BAR(opponent);
        ABILITY_POPUP(player, ABILITY_GULP_MISSILE);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, opponent);
        HP_BAR(player);
        ABILITY_POPUP(player, ABILITY_GULP_MISSILE);
        HP_BAR(opponent);
        NONE_OF {
            ANIMATION(ANIM_TYPE_STATUS, B_ANIM_STATUS_PRZ, opponent);
            STATUS_ICON(opponent, paralysis: TRUE);
        }
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, player);
        HP_BAR(opponent);
        ANIMATION(ANIM_TYPE_MOVE, MOVE_SCRATCH, opponent);
        HP_BAR(player);
    }
}
