InteractWithOverworldWildEncounter::
    lock
    overworldwildencounterapproach
    applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark
    facetogether
    playmoncry VAR_0x8004, CRY_MODE_DOUBLES
    waitmoncry
    tryoverworldwildencounter
    waitstate
    end

OWEAutoBattleOverworldWildEncounter::
    lockall
    callnative ScriptFaceEachOtherFollowerOWE  
    applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark
    playmoncry VAR_0x8004, CRY_MODE_DOUBLES
    waitmoncry
    removeobject VAR_LAST_TALKED
    bufferlivemonnickname STR_VAR_1
    bufferspeciesname STR_VAR_2, VAR_0x8004
    autobattle VAR_0x8004, VAR_0x8005 @ input a species and level in vars. Loads a battle result into var 0x8006
    goto_if_eq VAR_0x8006, 1, EventScript_AutoBattleWin1
    goto_if_eq VAR_0x8006, 2, EventScript_AutoBattleWin2
    goto_if_eq VAR_0x8006, 3, EventScript_AutoBattleWin3
    goto_if_eq VAR_0x8006, 4, EventScript_AutoBattleWin4
    goto_if_eq VAR_0x8006, 5, EventScript_AutoBattleWin5
    msgbox gText_WoreItselfOut, MSGBOX_DEFAULT @AUTOBATTLE
    goto_if_eq VAR_0x8006, 0, EventScript_OWEAutoBattlingEnd
    releaseall
    end

gText_WoreItselfOut:
	.string "{STR_VAR_1} defeated a {STR_VAR_2}!\n"
	.string "It took damage and gained {STR_VAR_3} EXP.\p"
	.string "{STR_VAR_1} wore itself out and\n"
	.string "came back to you.$"


EventScript_AutoBattleWin1::
    msgbox gText_Buffer1DefeatedABuffer2easy, MSGBOX_DEFAULT @AUTOBATTLE
    releaseall
    end

gText_Buffer1DefeatedABuffer2easy:
	.string "{STR_VAR_1} defeated a {STR_VAR_2} easily!\n"
	.string "Gained {STR_VAR_3} EXP.$"

EventScript_AutoBattleWin2::
    msgbox gText_Buffer1DefeatedABuffer2, MSGBOX_DEFAULT @AUTOBATTLE
    releaseall
    end

gText_Buffer1DefeatedABuffer2:
	.string "{STR_VAR_1} defeated a {STR_VAR_2}! It took\n"
	.string "almost no damage and gained {STR_VAR_3} EXP.$"

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
    callnative RemoveAutoBattlingPokemon
    updatefollowingmon
EventScript_OWEAutoBattling::
    releaseall
    end

gText_FollowerAutoQuestion2::
	.string "Bring {STR_VAR_1} to follow you?$"
