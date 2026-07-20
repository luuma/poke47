ROUTE_100_MapScripts::
	map_script MAP_SCRIPT_ON_FRAME_TABLE, ROUTE_100_OnFrame
	.byte 0

ROUTE_100_OnFrame::
	map_script_2 VAR_GAUNTLET_ACTIVE, 1, Route100_EventScript_GauntletEnd
	.2byte 0

Route100_EventScript_GauntletEnd::
        lockall
        applymovement LOCALID_PLAYER, Common_Movement_WalkInPlaceFasterUp
        waitmovement 0
        callnative GauntletEnd @ this also clears several flags
        goto_if_eq VAR_RESULT, FALSE, Route100_EventScript_Failsafe
        setflag FLAG_TEMP_1
        goto_if_eq VAR_0x8004, 1234, Route100_EventScript_Retire
        goto_if_set FLAG_GAUNTLET_ATK_ALTAR, Route100_EventScript_Altar2
        goto_if_set FLAG_GAUNTLET_BOSS_ALTAR, Route100_EventScript_BRAVO
        msgbox Route100_Text_YouLose
        releaseall
        end

Route100_EventScript_Retire::
        msgbox Route100_Text_Retire
        releaseall
        end

Route100_EventScript_BRAVO::
        msgbox Route100_Text_bravo
        releaseall
        end


Route100_EventScript_Altar2::
        msgbox Route100_Text_MadeItToSecondAltar
        releaseall
        end

Route100_Text_Retire:
	.string "Well! I thought that attempt looked\n"
	.string "rather promising. A shame, I think.\p"
	.string "Don't fret. Your chosen POKéMON is\n"
 	.string "back to its old state, once more.$"


Route100_Text_bravo:
	.string "Bravo. Geheheh. I sensed you\n"
	.string "had it in you.\p"
	.string "Your chosen POKéMON is back to\n"
 	.string "its old state, once more.\p"
	.string "Stronger than before, I daresay.$"


Route100_Text_MadeItToSecondAltar:
	.string "Commendable. A good showing, child,\n"
	.string "for one so young. Geheh.\p"
	.string "Don't fret. Your chosen POKéMON is\n"
 	.string "back to its old state, once more.\p"
	.string "Stronger than before, I daresay.$"

Route100_Text_YouLose:
	.string "If you wanted to head home early\n"
	.string "you could've just asked. Geheh.\p"
	.string "Don't fret. Your chosen POKéMON is\n"
 	.string "back to its old state, once more.$"


ROUTE_100_Witch::
	lockall
	faceplayer
        goto_if_set FLAG_TEMP_1, ROUTE_100_Witch_fast
        goto_if_unset FLAG_GAUNTLET_TALKED_WITCH, ROUTE_100_EventScript_Witch_First
        msgbox Route100_Text_Iwaswaitingforyou, MSGBOX_YESNO
ROUTE_100_Power::
        setflag FLAG_TEMP_1
	msgbox Route100_Text_GauntletChallengePower, MSGBOX_YESNO
        goto_if_eq VAR_RESULT, YES, Route100_EventScript_GauntletSetup
Route100_EventScript_Illletyouprepare::
	msgbox Route100_Text_leavetoprepare
        releaseall
        end

Route100_EventScript_Failsafe::
	msgbox Route100_Text_veryodd
        releaseall
        end

ROUTE_100_Witch_fast::
        msgbox Route100_Text_GauntletChallengeExplain, MSGBOX_YESNO
        goto_if_eq VAR_RESULT, YES, Route100_EventScript_GauntletSetup
        goto_if_eq VAR_RESULT, NO, ROUTE_100_Power
        end

Route100_EventScript_GauntletSetup::
        getpartysize
        goto_if_ne VAR_RESULT, 1, Route100_EventScript_DepositTime
        callnative GauntletStart
        goto_if_eq VAR_RESULT, FALSE, Route100_EventScript_Failsafe
	msgbox Route100_Text_GauntletChallengeBegin
	applymovement VAR_LAST_TALKED, Common_Movement_WalkUp
	waitmovement 0
	delay 30
	hideobjectat VAR_LAST_TALKED, MAP_ROUTE_100
	call_if_eq VAR_FACING, DIR_NORTH, SlateportCity_Harbor_EventScript_BoardFerryNorth
	call_if_eq VAR_FACING, DIR_EAST, SlateportCity_Harbor_EventScript_BoardFerryEast
	delay 10
	hideplayer
	applymovement LOCALID_WITCH_BOAT, Route100_Movement_BoatDepart
	waitmovement 0
        warp MAP_GAUNTLET_ISLAND_SOUTH, 24, 48
        waitstate
        releaseall
	end

Route100_Movement_BoatDepart:
	walk_left
	walk_left
	walk_fast_left
	walk_fast_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	walk_faster_left
	step_end

Route100_EventScript_DepositTime::
	msgbox Route100_Text_MoreThanOnePartyMember
	special ShowPokemonStorageSystemPC
	goto Route100_EventScript_GauntletSetup
	end


ROUTE_100_EventScript_Witch_First::
        msgbox Route100_Text_IwaswaitingforyouArrive
        goto_if_lt VAR_BIRCH_LAB_STATE, 3, Route100_getapokemonlmao
        setflag FLAG_GAUNTLET_TALKED_WITCH
        setflag FLAG_GAUNTLET_0FBOULDER1
        setflag FLAG_GAUNTLET_0FBOULDER2
        setflag FLAG_GAUNTLET_0FBOULDER3
        msgbox Route100_Text_GauntletChallengeExplain, MSGBOX_YESNO
        goto ROUTE_100_Power        

Route100_getapokemonlmao::
        msgbox Route100_Text_getapokemonlmao
        releaseall
	end

Route100_Text_getapokemonlmao:
	.string "Perhaps I can tell you more once you.\n"
	.string "have your own POKéMON…$"

Route100_Text_IwaswaitingforyouArrive:
	.string "Ah. I was wondering when you'd arrive.\p"
	.string "You're NORMAN's tyke, now, aren't you?\n"
	.string "Didn't he teach you, perhaps,\l"
	.string "not to speak to strangers?\p"
	.string "After all, I'm a WITCH. And I am here\n"
	.string "to trick you.\p"
	.string "I want to suggest a dreadful challenge\n"
	.string "for you. Geheh.$"

Route100_Text_Iwaswaitingforyou:
	.string "Ah. I was wondering when you'd return.\n"
	.string "I am here, waiting to trick you again.\p"
	.string "They say two wrongs don't make a right…\n"
	.string "But two negatives…\n"
	.string "Don't NOT make a right. Geheheh./p"
Route100_Text_GauntletChallengeExplain:
	.string "Here's the deal. I'll reduce your only\n"
	.string "POKéMON to the state of a newborn, and\l"
	.string "strand you on a distant island. Geheh.\l"
	.string "Sound fair?$"

Route100_Text_GauntletChallengePower:
	.string "It's not fair at all.\n"
	.string "But here's the hook:\l"
	.string "The island is cursed with great power.\l"
	.string "Everyone loves power, child. Geheheh.\p"
	.string "Are you ready?$"


Route100_Text_GauntletChallengeBegin:
	.string "In we go. Geheheheh.$"

Route100_Text_veryodd:
	.string "Odd. I can't get you ready.\p"
	.string "You may need a free space in\n"
	.string "your PC boxes.\p"
Route100_Text_leavetoprepare:
	.string "I'll leave you to prepare. Geheh.$"

Route100_Text_MoreThanOnePartyMember:
	.string "You've got more than one POKéMON.\p"
	.string "Surely that's not hard enough.\n"
	.string "Deposit all but one of them,\l"
	.string "if you wouldn't mind.$"

