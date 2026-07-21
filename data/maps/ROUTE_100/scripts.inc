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
        goto_if_set FLAG_GAUNTLET_HP_ALTAR, Route100_EventScript_Altar1
        goto_if_set FLAG_GAUNTLET_ATK_ALTAR, Route100_EventScript_Altar2
        goto_if_set FLAG_GAUNTLET_SPATK_ALTAR, Route100_EventScript_Altar3
        goto_if_set FLAG_GAUNTLET_SPEED_ALTAR, Route100_EventScript_Altar4
        goto_if_set FLAG_GAUNTLET_BOSS_ALTAR, Route100_EventScript_BRAVO
        goto_if_eq VAR_0x8004, 1234, Route100_EventScript_Retire @ Seems better to handle properly every time unless they gave up early, rather than say "you retired" even if they did great.
	setvar VAR_0x8004, 0
	call_if_unset GAUNTLET_FREELOSSPOINT, gaunteltreleasened_FREELOSSPOINTAAAAAA
        msgbox Route100_Text_YouLose
Route100_EventScript_YouLostThereforeLossPoints::
	goto_if_eq VAR_0x8004, 0, gaunteltfuckingyouhavesomepoints
        callnative fuckromhacking
        call_if_gt VAR_GAUNTLET_LOSS_POINTS, 1000, Route100_setto999losspoints @ ok cool
	buffernumberstring STR_VAR_1, VAR_0x8004 
        msgbox Route100_Text_LossPoints MSGBOX_YESNO
        goto_if_eq VAR_RESULT, YES, Route100_LossPointShop
        releaseall
        end

gaunteltfuckingyouhavesomepoints::
	goto_if_eq VAR_GAUNTLET_LOSS_POINTS, 0, gauntletreleasened::
	buffernumberstring STR_VAR_1, VAR_GAUNTLET_LOSS_POINTS
        msgbox Route100_Text_LossPoints MSGBOX_YESNO
        goto_if_eq VAR_RESULT, YES, Route100_LossPointShop
gauntletreleasened::
        releaseall
        end

Route100_Text_LossPoints:
	.string "{PLAYER} has {STR_VAR_1} LOSS POINTS.\l"
	.string "Spend them now?$"

gaunteltreleasened_FREELOSSPOINTAAAAAA::
	setvar VAR_0x8004, 1
	setflag GAUNTLET_FREELOSSPOINT
	return

Route100_EventScript_Retire::
        setvar VAR_0x8004, 0
        msgbox Route100_Text_Retire
        releaseall
        end

Route100_EventScript_Altar1::
        setvar VAR_0x8004, 1
        msgbox Route100_Text_MadeItToFirstAltar
        goto Route100_EventScript_YouLostThereforeLossPoints
        end

Route100_EventScript_BRAVO::
        msgbox Route100_Text_bravo
        releaseall
        end


Route100_EventScript_Altar2::
        setvar VAR_0x8004, 2
        msgbox Route100_Text_MadeItToSecondAltar
        goto Route100_EventScript_YouLostThereforeLossPoints
        end


Route100_EventScript_Altar3::
        setvar VAR_0x8004, 3
        msgbox Route100_Text_MadeItToSecondAltar
        goto Route100_EventScript_YouLostThereforeLossPoints
        end

Route100_EventScript_Altar4::
        setvar VAR_0x8004, 4
        msgbox Route100_Text_MadeItToFourthAltar
        goto Route100_EventScript_YouLostThereforeLossPoints
        end

Route100_Text_Retire:
	.string "Hm! I thought that attempt looked\n"
	.string "rather promising. A shame, I think.\p"
	.string "Don't fret. Your chosen POKéMON is\n"
 	.string "back to its old state, once more.$"


Route100_Text_bravo:
	.string "Bravo. Geheheh. I sensed you\n"
	.string "had it in you.\p"
	.string "Your chosen POKéMON is back to\n"
 	.string "its old state, once more.\p"
	.string "Stronger than before, I daresay.$"

Route100_Text_MadeItToFourthAltar:
	.string "Remarkable. Quite the showing,\n"
	.string "child. You handled yourself well.\p"
	.string "Don't fret. Your chosen POKéMON is\n"
 	.string "back to its old state, once more.\p"
	.string "Stronger than before, I daresay.$"

Route100_Text_MadeItToFirstAltar:
	.string "Ah, one step at a time, child.\n"
	.string "Some good victories there. Geheh.\p"
	.string "Don't fret. Your chosen POKéMON is\n"
 	.string "back to its old state, once more.\p"
	.string "A little stronger than before.$"



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

Route100_Text_LossPoints:
	.string "For a heroic loss in the CHALLENGE,\n"
	.string "{PLAYER} received {STR_VAR_1} LOSS POINTS.\l"
	.string "Spend them now?$"

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


Route100_FUCKIT::
	lock
        call_if_lt VAR_GAUNTLET_LOSS_POINTS, 10, Route100_setto999losspoints
	goto Route100_LossPointShop
	end

Route100_setto999losspoints::
        setvar VAR_GAUNTLET_LOSS_POINTS, 1000
        return

Route100_LossPointShop::@ god awful code. Duct tape glue and magic numbers. I am tired.
	buffernumberstring STR_VAR_1, VAR_GAUNTLET_LOSS_POINTS
	msgbox Route100_Text_YouHaveXLossPoints
Route100_LossPointShopjUMP::
        callnative ScrCmd_GauntletStartingBenefitHandler
        .byte 1
        call_if_lt VAR_0x8006, 4, Route100_LossPointShop_dynmultiSportBalls @ 4 is plenty
        callnative ScrCmd_GauntletStartingBenefitHandler
        .byte 2
        call_if_lt VAR_0x8006, 3, Route100_LossPointShop_dynmultiSacredAss @ 3 is plenty
        callnative ScrCmd_GauntletStartingBenefitHandler
        .byte 4
@ 6 options each being "start with 1 devotion to x" where you can toggle between them.
        call_if_lt VAR_0x8006, 7, Route100_LossPointShop_dynmultimoreitems
    	dynmultipush GauntletIsland_cANCEL, 0xFF
	message Route100_Text_Buysmth
        waitmessage
        dynmultistack 0, 0, TRUE, 6, FALSE, VAR_0x800A, DYN_MULTICHOICE_CB_NONE
	callnative ScrCmd_GauntletStartingBenefitHandler
        .byte 10
	goto_if_eq VAR_RESULT, 255, Route100_Handlecanceljump
	call_if_eq VAR_0x8005, TRUE, Route100_HandlePurchaseMessage
	call_if_eq VAR_0x8005, FALSE, Route100_comebackwhenyourealittlemmmmmricher
Route100_Handlecanceljump::@ this code is SO SHIT!!
	buffernumberstring STR_VAR_1, VAR_GAUNTLET_LOSS_POINTS
	msgbox Route100_Text_YouHaveXLossPointsLeft MSGBOX_YESNO
        goto_if_eq VAR_RESULT, NO, Route100_LossPointShopjUMP
	release
	end

Route100_LossPointShop_dynmultiSportBalls::
	buffernumberstring STR_VAR_1, VAR_0x8004
    	dynmultipush GauntletIsland_ISLANDMULTI, 11
	return

Route100_LossPointShop_dynmultiSacredAss::
	buffernumberstring STR_VAR_2, VAR_0x8004
    	dynmultipush GauntletIsland_ASHMULTI, 12
	return

Route100_LossPointShop_dynmultimoreitems::
	buffernumberstring STR_VAR_3, VAR_0x8004
    	dynmultipush GauntletIsland_ITEMSMULTI, 14
	return

Route100_HandlePurchaseMessage::
	buffernumberstring STR_VAR_1, VAR_0x8004
	buffernumberstring STR_VAR_3, VAR_0x8006
	goto_if_eq VAR_0x8007, 11, Route100_LossPointShop_SportBallsbOUGHT
	goto_if_eq VAR_0x8007, 12, Route100_LossPointShop_ashbOUGHT
	goto_if_eq VAR_0x8007, 14, Route100_LossPointShop_ITEMSbought
	return

Route100_LossPointShop_SportBallsbOUGHT::
	msgbox Route100_Text_LossPointShop_SportBallsbOUGHT 
	return

Route100_LossPointShop_ashbOUGHT::
	msgbox Route100_Text_LossPointShop_ashbOUGHT 
	return

Route100_LossPointShop_ITEMSbought::
	msgbox Route100_Text_LossPointShop_ITEMSbought
	return

GauntletIsland_ISLANDMULTI:
   	.string "+1 ISLAND POKéBALL{CLEAR_TO 130}{STR_VAR_1} LP$"

GauntletIsland_ASHMULTI:
   	.string "+1 SACRED ASH{CLEAR_TO 130}{STR_VAR_2} LP$"

GauntletIsland_ITEMSMULTI:
   	.string "MORE ITEM SPAWNS{CLEAR_TO 130}{STR_VAR_3} LP$"

GauntletIsland_cANCEL:
   	.string "CANCEL$"

Route100_Text_YouHaveXLossPoints:
   	.string "{PLAYER} opened the LOSS POINT SHOP.\n"
   	.string "You have {STR_VAR_1} LOSS POINTS to spend!!!$"

Route100_Text_YouHaveXLossPointsLeft:
   	.string "You have {STR_VAR_1} LOSS POINTS left!\n"
   	.string "Would you like to exit?$"

Route100_comebackwhenyourealittlemmmmmricher:
   	.string "You don't have enough LOSS POINTS!$"

Route100_Text_Buysmth:
   	.string "Buy a boon?$"

Route100_Text_LossPointShop_ITEMSbought:
   	.string "For {STR_VAR_1} LP, you will now have up to\n"
  	.string "{STR_VAR_3} more items spawn than default.$"

Route100_Text_LossPointShop_ashbOUGHT:
   	.string "For {STR_VAR_1} LP, you will now start\n"
  	.string "with {STR_VAR_3} SACRED ASH.$"

Route100_Text_LossPointShop_SportBallsbOUGHT:
   	.string "For {STR_VAR_1} LP, you will now start\n"
  	.string "with {STR_VAR_3} ISLAND BALL(s).$"
