InteractWithOverworldWildEncounter::
    lock
    overworldwildencounterapproach
    applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark
    facetogether
    getoverworldwildencounterspecies VAR_0x8005
    playmoncry VAR_0x8005, CRY_MODE_DOUBLES
    waitmoncry
    tryoverworldwildencounter
    waitstate
    end

EventScript_FollowerAuto::
    msgbox gText_FollowerAutoQuestion, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, Common_EventScript_NopReturn @AUTOBATTLE
EventScript_FollowerAutoBegin:: 
    lockall
    getobjectxy OBJ_EVENT_ID_FOLLOWER, CURRENT_POSITION, 0x8004, 0x8005
    followertoautobattler 0x8004, 0x8005
    setvar VAR_LAST_TALKED, OBJ_EVENT_ID_FOLLOWER_AUTOBATTLE
    releaseall
    end

EventScript_AButtonToAutobattle::
    lockall
    callnative scriptcanautobattle
    call_if_eq VAR_RESULT, TRUE, EventScript_FollowerAutoBegin @ see wild_encounter.inc
    release
    end

EventScript_AButtonToEndAutobattle::
    lockall
    setvar VAR_LAST_TALKED, OBJ_EVENT_ID_FOLLOWER_AUTOBATTLE
    applymovement OBJ_EVENT_ID_FOLLOWER_AUTOBATTLE, gMovement_EnterPokeball
    waitmovement
    callnative RemoveAutoBattlingPokemon @ this despawn automatically updates following pokemon.
    releaseall
    end



gText_FollowerAutoQuestion::
    .string "Let {STR_VAR_1} roam and battle?$"

gMovement_EnterPokeball:
	enter_pokeball
	step_end


OWEAutoBattleOverworldWildEncounter::
    lockall
    applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark
    getoverworldwildencounterspecies VAR_0x8004
    playmoncry VAR_0x8004, CRY_MODE_DOUBLES
    waitmoncry
    bufferlivemonnickname STR_VAR_1
    bufferspeciesname STR_VAR_2, VAR_0x8004
    autobattle VAR_0x8004, VAR_0x8005 @ input a species and level in vars. Loads a battle result into var 0x8006
    goto_if_eq VAR_0x8006, 6, EventScript_AutoBattleLoss
    removeobject VAR_LAST_TALKED @ Enemy down
    goto_if_eq VAR_0x8006, 1, EventScript_AutoBattleWin1
    goto_if_eq VAR_0x8006, 2, EventScript_AutoBattleWin2
    goto_if_eq VAR_0x8006, 3, EventScript_AutoBattleWin3
    goto_if_eq VAR_0x8006, 4, EventScript_AutoBattleWin4
    goto_if_eq VAR_0x8006, 5, EventScript_AutoBattleWin5
    msgbox gText_BarelyDefeatedWoreItselfOut, MSGBOX_DEFAULT @AUTOBATTLE
    goto_if_eq VAR_0x8006, 0, EventScript_OWEAutoBattlingEnd
    releaseall
    end

gText_BarelyDefeatedWoreItselfOut:
	.string "{STR_VAR_1} barely defeated a {STR_VAR_2}.\n"
	.string "It gained {STR_VAR_3} EXP.\p"
gText_Buffer1WoreItselfOut:
	.string "{STR_VAR_1} wore itself out and\n"
	.string "came back to you.$"

EventScript_AutoBattleLoss::
    msgbox gText_Buffer1WoreItselfOut, MSGBOX_DEFAULT @AUTOBATTLE
    goto EventScript_OWEAutoBattlingEnd
    releaseall
    end

EventScript_AutoBattleWin1::
    msgbox gText_Buffer1DefeatedABuffer2easy, MSGBOX_DEFAULT @AUTOBATTLE
    releaseall
    end

gText_Buffer1DefeatedABuffer2easy:
	.string "{STR_VAR_1} defeated a {STR_VAR_2}! It took\n"
	.string "almost no damage and gained {STR_VAR_3} EXP.$"

EventScript_AutoBattleWin2::
    msgbox gText_Buffer1DefeatedABuffer2, MSGBOX_DEFAULT @AUTOBATTLE
    releaseall
    end

gText_Buffer1DefeatedABuffer2:
	.string "{STR_VAR_1} defeated a {STR_VAR_2}! It took\n"
	.string "tiny damage and gained {STR_VAR_3} EXP.$"

EventScript_AutoBattleWin3::
    msgbox gText_Buffer1DefeatedABuffer2dmg, MSGBOX_DEFAULT @AUTOBATTLE
    releaseall
    end

gText_Buffer1DefeatedABuffer2dmg:
	.string "{STR_VAR_1} defeated a {STR_VAR_2}! It took\n"
	.string "a little damage and gained {STR_VAR_3} EXP.$"

EventScript_AutoBattleWin4::
    msgbox gText_Buffer1DefeatedABuffer2hurt, MSGBOX_DEFAULT @AUTOBATTLE
    releaseall
    end

gText_Buffer1DefeatedABuffer2hurt:
	.string "{STR_VAR_1} defeated a {STR_VAR_2}! It took\n"
	.string "some damage and gained {STR_VAR_3} EXP.$"

EventScript_AutoBattleWin5::
    msgbox gText_Buffer1DefeatedABuffer2bighurt, MSGBOX_DEFAULT @AUTOBATTLE
    releaseall
    end

gText_Buffer1DefeatedABuffer2bighurt:
	.string "{STR_VAR_1} defeated a {STR_VAR_2}! It took\n"
	.string "a lot of damage and gained {STR_VAR_3} EXP.$"


OWEAutoBattling::
    lockall
    faceplayer
    bufferlivemonnickname STR_VAR_1
    playfirstmoncry
    msgbox gText_FollowerAutoQuestion2, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, EventScript_OWEAutoBattling
EventScript_OWEAutoBattlingEnd::
    applymovement OBJ_EVENT_ID_FOLLOWER_AUTOBATTLE, gMovement_EnterPokeball
    waitmovement
    callnative RemoveAutoBattlingPokemon @ this despawn automatically updates following pokemon.
EventScript_OWEAutoBattling::
    releaseall
    end

gText_FollowerAutoQuestion2::
	.string "Bring {STR_VAR_1} to follow you?$"
