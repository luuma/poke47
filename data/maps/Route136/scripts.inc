Route136_MapScripts::
	.byte 0

Route136_Triangle1::
	lockall
	braillemsgbox Braille_Text_Triangle1
	releaseall
	end

Route136_sign_uselesstip::
	msgbox Route136_uselesstipmessage, MSGBOX_SIGN
	end

Route136_Triangle2::
	lockall
	braillemsgbox Braille_Text_Triangle2
	releaseall
	end


Route136_TurnedStone::
	lockall
	setmetatile 31, 8, 124, 1
	setmetatile 32, 8, 100, 1
	setmetatile 33, 8, 124, 1
	special DrawWholeMapView
	delay 6
	setmetatile 31, 9, 0x91, 1
	setmetatile 32, 9, 167, 0
	setmetatile 33, 9, 0x91, 1
	special DrawWholeMapView
	releaseall
	end

Route136_Triangle3::
	lockall
	braillemsgbox Braille_Text_Triangle3
	releaseall
	end

Route136_EventScript_Lifeorb::
	lock
	goto_if_set FLAG_RECEIVED_LIFEORB, Route136_EventScript_LifeorbTaken
	msgbox Route136_Lifeorb_Found, MSGBOX_DEFAULT
	finditem ITEM_LIFE_ORB 1
	setflag FLAG_RECEIVED_LIFEORB
	release
	end

Route136_EventScript_LifeorbTaken::
	msgbox Route136_Lifeorb_Taken, MSGBOX_DEFAULT
	release
	end

Route136_uselesstipmessage:
	.string "TRAINER TIPS\p"
	.string "Items can be found everywhere!\n"
	.string "Leave no stone unturned.$"

Route136_Lifeorb_Found:
	.string "Feeling around on the rock ledge,\n"
	.string "{PLAYER}'s fingers close around a tiny\l"
	.string "concealed spherical object.\p"
	.string "{PLAYER} carefully extracted it.$"

Route136_Lifeorb_Taken:
	.string "There is a carved indentation in the\n"
	.string "rocks, where the Life Orb once rested.$"

