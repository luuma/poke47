IngyBingyIsland_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, ingy_OnTransition
	.byte 0

ingy_OnTransition:
	call_if_set FLAG_ANNOYING_FISHERMAN_ATSTEPS, ingy_fisherman_putatsteps
	end

ingy_fisherman_putatsteps::
	setobjectxyperm LOCALID_ANNOYING_FISHERMAN, 60, 33
	setobjectmovementtype LOCALID_ANNOYING_FISHERMAN, MOVEMENT_TYPE_FACE_DOWN
	return


@SPECIAL BITS

annoyfisherman::
	lockall
	faceplayer
	goto_if_set FLAG_ANNOYING_FISHERMAN_ATSTEPS, annoyfishermanToSteps
	msgbox annoyfish_huhnmovetext1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, annoyfisherman_OhChill
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_eq VAR_RESULT, DIR_WEST, annoyfishermanyoureintheway
	applymovement VAR_LAST_TALKED, ing_move3
	waitmovement 0
	faceplayer
	msgbox annoyfish_ideatext1
	closemessage
	applymovement VAR_LAST_TALKED, ing_move2
	waitmovement 0
	setflag FLAG_ANNOYING_FISHERMAN_ATSTEPS
	releaseall
	end

annoyfishermanToSteps::
	msgbox annoyfish_huhnmovetext2, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, annoyfisherman_OhChill
	specialvar VAR_RESULT, GetPlayerFacingDirection
	goto_if_eq VAR_RESULT, DIR_EAST, annoyfishermanyoureintheway
	applymovement VAR_LAST_TALKED, ing_move3
	waitmovement 0
	faceplayer
	msgbox annoyfish_ideatext2
	closemessage
	applymovement VAR_LAST_TALKED, ing_move1
	waitmovement 0
	clearflag FLAG_ANNOYING_FISHERMAN_ATSTEPS
	releaseall
	end

annoyfishermanyoureintheway::
	applymovement VAR_LAST_TALKED, ing_move3
	waitmovement 0
	faceplayer
	msgbox annoyfish_youreintheway
	closemessage
	applymovement VAR_LAST_TALKED, ing_move3
	waitmovement 0
	msgbox annoyfish_youreintheway2
	closemessage
	releaseall
	end


annoyfisherman_OhChill::
	msgbox annoyfish_chilltext, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, ing_move3
	waitmovement 0
	msgbox annoyfish_myrodtext
	closemessage
	applymovement VAR_LAST_TALKED, ing_move3
	waitmovement 0
	releaseall
	end

annoyfish_chilltext:
	.string "Oh.\p"
	.string "Yeah, that's chill then.$"

annoyfish_myrodtext:
	.string "Man, I wish I'd remembered to bring\n"
	.string "my fishing rod…$"

annoyfish_youreintheway:
	.string "Oh, but you're in the way.\p"
	.string "Oh, dude I'm so sorry.\p"
	.string "Man, that blows.$"

annoyfish_youreintheway2:
	.string "Sigh… I guess I'll stay here then.$"


annoyfish_huhnmovetext1:
	.string "…………………………………………………………………………\n"
	.string "…………Huhn? Oh.\p"
	.string "I'm just chilling in my fave spot\n"
	.string "for fishing.\p"
	.string "You're telling me I'm in the way?\p"
	.string "Oh, dude. Bummer. I'm so sorry.\p"
	.string "…………………………………………………………………………\n"
	.string "…………………………………………………………………………\p"
	.string "…………Huhn? Oh, you want me to move?$"

annoyfish_ideatext1:
	.string "Oh, I know where I can move.\p"
	.string "I'll go and chill in my second fave spot\n"
	.string "for fishing.$"

annoyfish_huhnmovetext2:
	.string "…………………………………………………………………………\n"
	.string "…………Huhn? Oh.\p"
	.string "I'm just chilling in my second\n"
	.string "favourite spot for fishing.\p"
	.string "You're telling me I'm in the way?\p"
	.string "Oh, dude. Bummer. I'm so sorry.\p"
	.string "…………………………………………………………………………\n"
	.string "…………………………………………………………………………\p"
	.string "…………Huhn? Oh, you want me to move?$"

annoyfish_ideatext2:
	.string "Oh, bingo! I've got an idea!\p"
	.string "I can move and chill in my fave spot\n"
	.string "for fishing! Righteous!$"

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
	face_down
	step_end

ing_move3:
	face_down
	delay_16
	delay_16
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
	.string "FISHING SHACK\p"
	.string "“A little old place where\n"
	.string "we can fish together.”$"

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
	trainerbattle_single TRAINER_INGY_FISHERMAN, ing_trainer1Intro, ing_trainer1Defeat
	msgbox ing_trainer1PostBattle, MSGBOX_AUTOCLOSE
	end

ing_trainer1Intro:
	.string "The Fishing Shack is nearby. Perfect\n"
	.string "for a future rod superstar like me!$"

ing_trainer1Defeat:
	.string "Aough… I'm no rod superstar just yet…$"

ing_trainer1PostBattle:
	.string "Whether you're a star fisher or not,\n"
	.string "the Fishing Shack is worth a visit.\p"
	.string "The strapping gents there are happy to\n"
	.string "let me access their magnificent RODs.$"



ing_trainer2::
	trainerbattle_single TRAINER_INGY_LASS, ing_trainer2Intro, ing_trainer2Defeat
	msgbox ing_trainer2PostBattle, MSGBOX_AUTOCLOSE
	end

ing_trainer2Intro:
	.string "My fists are all bruised from doing\n"
	.string "play-pretend with my little bro!\p"
	.string "Yeeeaagh!!! Cubchoo, annihilate them!!!$"

ing_trainer2Defeat:
	.string "Cubchoo… You're in Valhalla now…$"

ing_trainer2PostBattle:
	.string "Mom says I shouldn't fight so much.\p"
	.string "But the rush of play-pretend combat?\n"
	.string "It's seriously unmatched.\p"
	.string "The aliens can NOT win.$"

ing_trainer3::
	trainerbattle_single TRAINER_INGY_YOUNGSTER, ing_trainer3Intro, ing_trainer3Defeat
	msgbox ing_trainer3PostBattle, MSGBOX_AUTOCLOSE
	end

ing_trainer3Intro:
	.string "Me and big sis are fighting the evil\n"
	.string "aliens from the secret beach!$"

ing_trainer3Defeat:
	.string "You're… One of them!?$"

ing_trainer3PostBattle:
	.string "It gets pretty intense.\p"
	.string "Last week we fought the mafia which was\n"
	.string "mid but the aliens are cool.\p"
	.string "The stick over there is a magic sword.$"


ing_trainer4::
	trainerbattle_single TRAINER_INGY_BUG, ing_trainer4Intro, ing_trainer4Defeat
	msgbox ing_trainer4PostBattle, MSGBOX_AUTOCLOSE
	end

ing_trainer4Intro:
	.string "Face my team of… Wait. Don't fight yet!\n"
	.string "My Sewaddle is still over there!$"

ing_trainer4Defeat:
	.string "Okay, that was unfair of you.$"

ing_trainer4PostBattle:
	.string "If Sewaddle was here I would've won.\p"
	.string "Don't forget that.$"


