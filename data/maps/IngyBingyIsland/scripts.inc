IngyBingyIsland_MapScripts::
	.byte 0

@SPECIAL BITS

Route110_EventScript_BirchApproachPlayer1::
	applymovement LOCALID_ROUTE110_BIRCH, Route110_Movement_BirchApproachPlayer1
	waitmovement 0
	return

Route110_Movement_BirchApproachPlayer1:
	walk_down
	walk_left
	walk_left
	walk_down
	step_end

@SIGNS
Route110_EventScript_SlateportCitySign::
	msgbox Route110_Text_SlateportCitySign, MSGBOX_SIGN
	end

Route110_Text_SlateportCitySign:
	.string "ROUTE 110\n"
	.string "{DOWN_ARROW} SLATEPORT CITY$"

@PEOPLE

Route110_EventScript_OldMan::
	msgbox Route110_Text_TwoRoads, MSGBOX_NPC
	end

Route110_Text_TwoRoads:
	.string "The two roads, one above, one below…\p"
	.string "A road each for people and POKéMON.\n"
	.string "Perhaps that is right and fair.$"

@TRAINERS

ing_trainer1::
	trainerbattle_single TRAINER_RODNEY, ing_trainer1Intro, ing_trainer1Defeat
	msgbox ing_trainer1PostBattle, MSGBOX_AUTOCLOSE
	end

ing_trainer1Intro:
	.string "What a surprise! I didn't expect to\n"
	.string "see a TRAINER out in the sea.\p"
	.string "I think we should battle!$"

ing_trainer1Defeat:
	.string "This kid's awfully tough…$"

ing_trainer1PostBattle:
	.string "Your eyes have that look of someone\n"
	.string "who's experienced harsh challenges\l"
	.string "and won. It suits you well!$"
