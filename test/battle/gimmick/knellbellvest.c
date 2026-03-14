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
