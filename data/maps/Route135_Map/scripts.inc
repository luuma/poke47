Route135_Map_MapScripts::
	.byte 0

@SIGNS

Route135_sign1::
	msgbox Route135_route_sign, MSGBOX_SIGN
	end

Route135_route_sign:
	.string "Route Route135\p"
	.string "Parental advisory:\n"
	.string "no longer suitable for miners\l"
	.string "{UP_ARROW} Route 123$"

Route135_tip1::
	msgbox Route135_TIPS_sign, MSGBOX_SIGN
	end

Route135_TIPS_sign:
	.string "Devon Co. Mine.\n"
	.string "Hard hats MUST be worn on this site.$"

Route135_rocks::
	lockall
	clearflag FLAG_TEMP_1
	goto EventScript_RockSmash

@PEOPLE

Route135_Tune_Guy::	
	lock
	faceplayer
	goto_if_set FLAG_TEMP_1, Route135_tune_ask_stop
	msgbox Route135_Tune_GuyMsg, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, Route135_tune_out2
	setflag FLAG_TEMP_1
	fadenewbgm MUS_C_VS_LEGEND_BEAST
	msgbox Route135_EardrumsBuckled, MSGBOX_DEFAULT
	release
	end

Route135_tune_ask_stop::
	msgbox Route135_Ohstop, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, Route135_tune_out
	msgbox Route135_EardrumsBuckled, MSGBOX_DEFAULT
	release
	end

Route135_tune_out::
	clearflag FLAG_TEMP_1
	fadenewbgm MUS_GSC_ROUTE38
Route135_tune_out2::
	msgbox Route135_OkToneDown, MSGBOX_DEFAULT
	release
	end

Route135_Tune_GuyMsg:
	.string "I've been working on a lil' tune,\n"
	.string "the mine being closed an' all.\p"
	.string "Care to check it out?$"

Route135_EardrumsBuckled:
	.string "Alright!\n"
	.string "Keep your eardrums buckled up, kiddo!$"


Route135_Ohstop:
	.string "Yeeeeaahhh!! Oh, you want me to stop?$"

Route135_OkToneDown:
	.string "Aw, sure, I'll tone it down…$"

Route135_NpcSwimmer::
	lock
	msgbox Route135_SeabedSwimmer, MSGBOX_DEFAULT
	release
	end

Route135_SeabedSwimmer:
	.string "You can't make me move, sunshine.\p"
	.string "One, I'm buried neck deep in sand\n"
	.string "and two, it's just sooo warm…\p"
	.string "Seriously, it's like a duvet.\n" 
	.string "A sea-bed! Hahaaa!$"

Route135_Guitarist2::
	msgbox Route135_OlMineGo, MSGBOX_NPC
	end

Route135_OlMineGo:
	.string "Sad to watch the old mine go but\n"
	.string "heck I'm glad I don't have to\l"
	.string "drown in the sea alongside her!$"

Route135_runner::
	msgbox Route135_setalarm, MSGBOX_NPC
	end

Route135_setalarm:
	.string "I set my alarm early to go on\n"
	.string "a brisk jog before dawn.$"


Route135_Ninjaboy::
	lockall
	faceplayer
	msgbox Route135_watchthiiis, MSGBOX_DEFAULT
	delay 3
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFasterDown
	setmetatile 33, 39, 0x3C7, 3
	setmetatile 33, 40, 0x3C7, 3
	special DrawWholeMapView
	delay 3
	setmetatile 33, 39, 0x124, 3
	setmetatile 33, 40, 0x124, 3
	special DrawWholeMapView
	delay 15
	faceplayer
	msgbox Route135_didyouseeitdidyouseeit, MSGBOX_DEFAULT
	releaseall
	end


Route135_watchthiiis:
	.string "Watch this!$"

Route135_didyouseeitdidyouseeit:
	.string "Huh? Did you see it? Did you?\p"
	.string "Awesome, right?\n"
	.string "No, wait, um.\p"
	.string "I am the sands, and move as they do.\p"
	.string "I'm gonna be a Ninja Boy someday!$"


Route135_trainerPsychM::
	trainerbattle_single TRAINER_135_PSYCHICM, Route135_trainer1Intro, Route135_trainer1Defeat
	msgbox Route135_trainer1PostBattle, MSGBOX_AUTOCLOSE
	end

Route135_trainer1Intro:
	.string "I've seen visions of our fight,\n"
	.string "trainer.\p"
	.string "I already know your name!$"
Route135_trainer1Defeat:
	.string "Y-your name is TERI, right?$"
Route135_trainer1PostBattle:
	.string "Wait, no, don't tell me your name,\n"
	.string "let me guess.\p"

	.string "Is it JO? No? Are you called, maybe,\n"
	.string "SIGRUND? Is it {PLAYER}?\p"

	.string "No, don't talk, it's CHARLIE? Right?\n"
	.string "You're called CHARLIE?$"

Route135_trainerPsychF::
	trainerbattle_single TRAINER_135_PSYCHICF, Route135_trainer2Intro, Route135_trainer2Defeat
	msgbox Route135_trainer2PostBattle, MSGBOX_AUTOCLOSE
	end

Route135_trainer2Intro:
	.string "My supernatural powers…\p"
	.string "What can you ever hope to suppress\n"
	.string "them with?$"
Route135_trainer2Defeat:
	.string "…With ease, apparently.$"
Route135_trainer2PostBattle:
	.string "Why are you so unimpressed by my ability\n"
	.string "to float a POKé BALL with my mind?\p"
	.string "Have you seriously seen someone\n"
	.string "do that before?!$"


Route135_trainerExpert::
	trainerbattle_single TRAINER_RED_135_EXPERT, Route135_trainer3Intro, Route135_trainer3Defeat
	msgbox Route135_trainer3PostBattle, MSGBOX_AUTOCLOSE
	end
Route135_trainer3Intro:
	.string "The sea's lovely salty over here.\n"
	.string "I don't need to move a muscle.$"
Route135_trainer3Defeat:
	.string "Well fought.$"
Route135_trainer3PostBattle:
	.string "These colder climes do my time-worn\n"
	.string "bones a world of good.$"


Route135_trainerAngy::
	trainerbattle_single TRAINER_135_BATTLEGIRL, Route135_trainer4Intro, Route135_trainer4Defeat
	msgbox Route135_trainer4PostBattle, MSGBOX_AUTOCLOSE
	end
Route135_trainer4Intro:
	.string "What! You dare to disrupt my training!?\p"
	.string "I'll suplex your obnoxious ass!\n"
	.string "The nerve of it!$"
Route135_trainer4Defeat:
	.string "You come to my beach, block my path,\n"
	.string "and now this!?$"
Route135_trainer4PostBattle:
	.string "Out of my way!\p"
	.string "I'll set Pangoro on you again!\n"
	.string "You're so rude!$"



Route135_trainerBelt::
	trainerbattle_single TRAINER_135_BLACKBELT, Route135_trainer5Intro, Route135_trainer5Defeat
	msgbox Route135_trainer5PostBattle, MSGBOX_AUTOCLOSE
	end
Route135_trainer5Intro:
	.string "Prepare to fight!$"
Route135_trainer5Defeat:
	.string "You outprepared me!$"
Route135_trainer5PostBattle:
	.string "Preparation is vital!$"

Route135_trainerSailor::
	trainerbattle_single TRAINER_135_SAILOR, Route135_trainer6Intro, Route135_trainer6Defeat
	msgbox Route135_trainer6PostBattle, MSGBOX_AUTOCLOSE
	end

Route135_trainer6Intro:
	.string "Beware my bounty of muscular\n"
	.string "machismo!$"
Route135_trainer6Defeat:
	.string "I've been bested!$"
Route135_trainer6PostBattle:
	.string "Haha!\p"
	.string "Young trainer, you may have me beat,\n"
	.string "but my spirits shall never be\l"
	.string "knocked down!$"


Route135_trainerSeamus::
	trainerbattle_single TRAINER_135_SEAMUS, Route135_trainer7Intro, Route135_trainer7Defeat
	msgbox Route135_trainer7PostBattle, MSGBOX_AUTOCLOSE
	end
Route135_trainer7Intro:
	.string "Honestly, I'm guaranteed to lose.\p"
	.string "Lucky I've got the best lass in Hoenn\n"
	.string "by my side, right?$"

Route135_trainer7Defeat:
	.string "Blimey, LILY, you're better than I thought…$"
Route135_trainer7PostBattle:
	.string "SEAMUS: LILY is deadly, kiddo!\p"
	.string "She's second best butterfly in all Hoenn!\n"
	.string "And she's fourth at front crawl!$"

Route135_trainerLily::
	trainerbattle_single TRAINER_135_LILY, Route135_trainer8Intro, Route135_trainer8Defeat
	msgbox Route135_trainer8PostBattle, MSGBOX_AUTOCLOSE
	end
Route135_trainer8Intro:
	.string "Hey Trainer! SEAMUS here says\n"
	.string "he and Gastrodon are weaker than me.\p"
	.string "Shall we prove him wrong?$"

Route135_trainer8Defeat:
	.string "See! I blew it!\p"
	.string "I can't be accused of false modesty,\n"
	.string "am I right, SEAMUS?$"

Route135_trainer8PostBattle:
	.string "LILY: SEAMUS can flatter all he likes:\n"
	.string "I threw the battle and it's only fair\l"
	.string "he gets reimbursed.\p"
	.string "How does a drink sound, SEAMUS?$"


Route135_trainerGuitarist::
	trainerbattle_single TRAINER_135_GUITARIST, Route135_trainer9Intro, Route135_trainer9Defeat
	msgbox Route135_trainer9PostBattle, MSGBOX_AUTOCLOSE
	end

Route135_trainer9Intro:
	.string "I dig rocks and dig rock!$"

Route135_trainer9Defeat:
	.string "Yowzah! You ground me into the ground!$"

Route135_trainer9PostBattle:
	.string "Well I, uh, used to dig rocks and\n"
	.string "dig rock…\p"
	.string "But when the mine got shut down,\n"
	.string "I shifted jobs.\p"
	.string "Now I'm more into heavy metals and\n"
	.string "heavy metal!$"


Route135_trainerSwimmerKT::
	trainerbattle_single TRAINER_135_SWIMMERF, Route135_trainerAIntro, Route135_trainerADefeat
	msgbox Route135_trainerAPostBattle, MSGBOX_AUTOCLOSE
	end
Route135_trainerAIntro:
	.string "Are WATER-type POKéMON wet?$"

Route135_trainerADefeat:
	.string "Hey! I wasn't ready!$"

Route135_trainerAPostBattle:
	.string "I think WATER-type POKéMON don't count as\n"
	.string "wet, cause some of them ARE water.$"
