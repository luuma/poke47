IngyBingyIsland_MapScripts::
	.byte 0

@SPECIAL BITS





annoyfishermanToSteps::
	applymovement LOCALID_ANNOYING_FISHERMAN, ing_move1
	waitmovement 0
	return

annoyfishermanToSide::
	applymovement LOCALID_ANNOYING_FISHERMAN, ing_move2
	waitmovement 0
	return


ing_move1:
	walk_slow_left
	walk_slow_left
	walk_slow_left
	face_down
	step_end

ing_move2:
	walk_slow_right
	walk_slow_right
	walk_slow_right
ing_move3:
	face_down
	step_end

@SIGNS
ing_sign1::
	msgbox ing_signtext1, MSGBOX_SIGN
	end

ing_signtext1:
	.string "ROUTE 137\n"
	.string "{LEFT_ARROW} MT. SNOWDROP\l"
	.string "{RIGHT_ARROW} ROUTE 110$"

ing_sign2::
	msgbox ing_signtext2, MSGBOX_SIGN
	end

ing_signtext2:
	.string "FISHING HUT$"

@PEOPLE

ing_person1::
	msgbox ing_person1text, MSGBOX_NPC
	end

ing_person1text:
	.string "This place is very special to me and\n"
	.string "my girlfriend.\p"
	.string "To honor our love, we decided to\n"
	.string "name it “INGY BINGY LAND”.$"

ing_person2::
	msgbox ing_person2text, MSGBOX_NPC
	end

ing_person2text:
	.string "Seeing my reflection in the rock pools\n"
	.string "inspires me with ideas for how to get\l"
	.string "my partner soaked with water… Muahaha!$"

ing_sewaddle::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_SEWADDLE, CRY_MODE_NORMAL
	msgbox ing_sewaddlems, MSGBOX_DEFAULT
	waitmoncry
	release
	end

ing_sewaddlems:
	.string "SEWADDLE: Wad wad wad!$"


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
