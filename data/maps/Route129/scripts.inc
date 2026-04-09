Route129_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, Route129_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, Route129_OnLoad
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route129_OnFrame
	map_script MAP_SCRIPT_ON_RESUME, Route129_SetHoleWarp
	.byte 0

Route129_SetHoleWarp:
	setstepcallback STEP_CB_CRACKED_FLOOR
	setholewarp MAP_ROUTE128_CAVERN
	end

Route129_OnLoad:
	call_if_unset FLAG_REGI_DOORS_OPENED, Route129_EventScript_CloseAncientTomb
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_129_WEST, AbnormalWeather_EventScript_PlaceTilesRoute129West
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_129_EAST, AbnormalWeather_EventScript_PlaceTilesRoute129East
	end


Route129_EventScript_CloseAncientTomb::
	setmetatile 24, 5, METATILE_General_RockWall_RockBase, TRUE
	setmetatile 24, 6, METATILE_General_RockWall_SandBase, TRUE
	return

Route129_OnTransition:
	call_if_eq VAR_SHOULD_END_ABNORMAL_WEATHER, 1, AbnormalWeather_EventScript_HideMapNamePopup
	call_if_ge VAR_SOOTOPOLIS_CITY_STATE, 4, Route129_EventScript_CheckSetAbnormalWeather
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_129_WEST, AbnormalWeather_StartKyogreWeather
	call_if_eq VAR_ABNORMAL_WEATHER_LOCATION, ABNORMAL_WEATHER_ROUTE_129_EAST, AbnormalWeather_StartKyogreWeather
	setvar VAR_ICE_STEP_COUNT, 1
	end

Route129_EventScript_CheckSetAbnormalWeather::
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	return

Route129_OnFrame:
	map_script_2 VAR_SHOULD_END_ABNORMAL_WEATHER, 1, AbnormalWeather_EventScript_EndEventAndCleanup_1
	map_script_2 VAR_ICE_STEP_COUNT, 0, EventScript_FallDownHole
	.2byte 0

Route129_EventScript_Chase::
	trainerbattle_single TRAINER_CHASE, Route129_Text_ChaseIntro, Route129_Text_ChaseDefeat
	msgbox Route129_Text_ChasePostBattle, MSGBOX_AUTOCLOSE
	end

Route129_EventScript_Allison::
	trainerbattle_single TRAINER_ALLISON, Route129_Text_AllisonIntro, Route129_Text_AllisonDefeat
	msgbox Route129_Text_AllisonPostBattle, MSGBOX_AUTOCLOSE
	end

Route129_EventScript_Reed::
	trainerbattle_single TRAINER_REED, Route129_Text_ReedIntro, Route129_Text_ReedDefeat
	msgbox Route129_Text_ReedPostBattle, MSGBOX_AUTOCLOSE
	end

Route129_EventScript_Tisha::
	trainerbattle_single TRAINER_TISHA, Route129_Text_TishaIntro, Route129_Text_TishaDefeat
	msgbox Route129_Text_TishaPostBattle, MSGBOX_AUTOCLOSE
	end

Route129_EventScript_Clarence::
	trainerbattle_single TRAINER_CLARENCE, Route129_Text_ClarenceIntro, Route129_Text_ClarenceDefeat
	msgbox Route129_Text_ClarencePostBattle, MSGBOX_AUTOCLOSE
	end


Route129_gate0::
	addvar VAR_TEMP_0, 1
	end
	
Route129_gaterset2::
	setvar VAR_TEMP_0, 0
	goto_if_eq VAR_129_CYCLE_STATE, 2, Route129_gaterset3
	goto_if_eq VAR_129_CYCLE_STATE, 1, Route129_gaterset3
	end

Route129_gaterset3::
	addvar VAR_129_CYCLE_STATE, 1
	end





Route129_EventScript_boygo::
	lock
	faceplayer
	goto_if_eq VAR_129_CYCLE_STATE, 0, Route129_EventScript_beginchallenge
	goto_if_eq VAR_129_CYCLE_STATE, 4, Route129_EventScript_beginchallenge2
	goto_if_eq VAR_129_CYCLE_STATE, 3, Route129_EventScript_crosstheline
Route129_EventScript_okwhat::
	setvar VAR_129_CYCLE_STATE, 0
	msgbox Route129_Text_okwhat, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route129_EventScript_oklame
	goto Route129_EventScript_beginchallenge2
	release
	end

Route129_EventScript_beginchallenge2::
	specialvar VAR_RESULT, GetPlayerAvatarBike
	goto_if_ne VAR_RESULT, 2, Route129_EventScript_PlayerRidingAcroBike
	msgbox Route129_Text_RatedForNumberOfCollisions2, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route129_EventScript_oklame
	msgbox Route129_Text_321GO, MSGBOX_DEFAULT
	special Special_BeginCyclingRoadChallenge
	setvar VAR_129_CYCLE_STATE, 1
	releaseall
	end


Route129_EventScript_beginchallenge::
	specialvar VAR_RESULT, GetPlayerAvatarBike
	goto_if_ne VAR_RESULT, 2, Route129_EventScript_PlayerRidingAcroBike
	msgbox Route129_Text_RatedForNumberOfCollisions, MSGBOX_DEFAULT
	call_if_set FLAG_BEAT_RECORD Route129_EventScript_brorecord
	msgbox Route129_Text_RatedForNumberOfCollisions3, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route129_EventScript_oklame
	msgbox Route129_Text_321GO, MSGBOX_DEFAULT
	special Special_BeginCyclingRoadChallenge
	setvar VAR_129_CYCLE_STATE, 1
	releaseall
	end

Route129_EventScript_brorecord::
	msgbox Route129_Text_RatedForNumberOfCollisions2, MSGBOX_DEFAULT
	return


Route129_EventScript_PlayerRidingAcroBike::
	msgbox Route129_Text_AcroBikesDoNotQualify, MSGBOX_DEFAULT
	release
	end


Route129_EventScript_oklame::
	msgbox Route129_Text_oklame, MSGBOX_DEFAULT
	release
	end

Route129_Text_oklame:
	.string "OK. Lame.$"


Route129_Text_okwhat:
	.string "OK. Let's just say that one didn't\n"
	.string "count or something.\l"
	.string "I'll forget I just, like, saw that.\p"
	.string "Want to try again?$"

Route129_EventScript_crosstheline::
	specialvar VAR_RESULT, GetPlayerAvatarBike
	goto_if_ne VAR_RESULT, 2, Route129_EventScript_okwhat
	msgbox Route129_Text_crossline, MSGBOX_DEFAULT
	release
	end

Route129_Text_crossline:
	.string "Cross the line!\n"
	.string "Cross the line!!!! Cross the line!$"


Route129_Text_321GO:
	.string "3.\p"
	.string "2.\n"
	.string "1.\l"
	.string "GO!$"

Route129_Text_AlwaysAimHigher:
	.string "Either way aim higher. Try harder.\n"
	.string "You better be back soon!$"

Route129_Text_AcroBikesDoNotQualify:
	.string "Hmm. Looks like you're not on a\n"
	.string "MACH BIKE… MACH BIKES are cool.\p"
	.string "My big bro practices by going round\n"
	.string "2 LAPS of this course every day.$"

Route129_Text_RatedForNumberOfCollisions:
	.string "Hmm. Looks like you're on a MACH BIKE.\n"
	.string "MACH BIKES are cool.\p"
	.string "I bet if you did 2 LAPS of this course,\n"
	.string "you might beat my big bro's record…$"

Route129_Text_RatedForNumberOfCollisions2:
	.string "If you can beat his record on time\n"
	.string "and collisions, I'll give you something\l"
	.string "that's basically priceless.\p"
Route129_Text_RatedForNumberOfCollisions3:
	.string "…\n"
	.string "So?? Ready??? Or what.$"


Route129_EventScript_CyclingChallengeEnd::
	lockall
	applymovement LOCALID_BIKEBOY, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	call Route129_EventScript_CyclingChallengeResults
	msgbox Route129_Text_AlwaysAimHigher, MSGBOX_DEFAULT
	releaseall
	end

Route129_EventScript_CyclingChallengeResults::
	special Finish129RoadChallenge
	msgbox Route110_Text_CyclingChallengeResultSummary, MSGBOX_DEFAULT
	buffernumberstring STR_VAR_1, VAR_RESULT
	msgbox Route129_Text_OUTOF10, MSGBOX_DEFAULT
	switch VAR_RESULT
	case 10, Route129_EventScript_ChallengeReactionBest
	case 9, Route129_EventScript_ChallengeReactionGood2
	case 8, Route129_EventScript_ChallengeReactionGood2
	case 7, Route129_EventScript_ChallengeReactionGood
	case 6, Route129_EventScript_ChallengeReactionGood
	case 5, Route129_EventScript_ChallengeReactionOk
	case 4, Route129_EventScript_ChallengeReactionOk
	case 3, Route129_EventScript_ChallengeReactionOk
	case 2, Route129_EventScript_ChallengeReactionBad
	case 1, Route129_EventScript_ChallengeReactionBad
	case 0, Route129_EventScript_ChallengeReactionWorst
	end

Route129_EventScript_givebiketicket::
	msgbox Route129_text_waitnoway, MSGBOX_DEFAULT
	giveitem ITEM_BIKE_VOUCHER
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_BEAT_RECORD
	return

Route129_Text_OUTOF10:
	.string "I'd give that like a {STR_VAR_1} out of 10.$"

Route129_text_waitnoway:
	.string "Either way aim higher. Try… \n"
	.string "Wait wait wait wait wait wait wait\l"
	.string "You DID IT!\p"
	.string "You beat big bro's record straight up!\p"
	.string "Oh! Your prize! It's a BIKE VOUCHER.\n"
	.string "It's yours! It's yours! Take it!$"


Route129_EventScript_ChallengeReactionBest::
	msgbox Route110_Text_ChallengeReactionBest, MSGBOX_DEFAULT
	call_if_unset FLAG_BEAT_RECORD, Route129_EventScript_givebiketicket
	goto Route129_EventScript_EndChallenge
	end

Route129_EventScript_ChallengeReactionGood2::
	msgbox Route110_Text_ChallengeReactionGood, MSGBOX_DEFAULT
	call_if_unset FLAG_BEAT_RECORD, Route129_EventScript_givebiketicket
	goto Route129_EventScript_EndChallenge
	end

Route129_EventScript_ChallengeReactionGood::
	msgbox Route110_Text_ChallengeReactionGood, MSGBOX_DEFAULT
	goto Route129_EventScript_EndChallenge
	end

Route129_EventScript_ChallengeReactionOk::
	msgbox Route110_Text_ChallengeReactionOk, MSGBOX_DEFAULT
	goto Route129_EventScript_EndChallenge
	end

Route129_EventScript_ChallengeReactionBad::
	msgbox Route110_Text_ChallengeReactionBad, MSGBOX_DEFAULT
	goto Route110_EventScript_EndChallenge
	end

Route129_EventScript_ChallengeReactionWorst::
	msgbox Route110_Text_ChallengeReactionWorst, MSGBOX_DEFAULT
	goto Route110_EventScript_EndChallenge
	end

Route129_EventScript_EndChallenge::
	setvar VAR_129_CYCLE_STATE, 4
	savebgm MUS_DUMMY
	fadedefaultbgm
	return


