Indoor_route_136_fisherman_MapScripts::
	.byte 0
@SIGNS
ing_fisherman_sign1::
	msgbox ing_fisherman_challengesign, MSGBOX_SIGN
	end

ing_fisherman_challengesign:
	.string "The Fisherman's Capture Challenge!\n"
	.string "Can you catch them all?\p"
	.string "OLD ROD: Finneon, Basculin,\n"
	.string "Froakie, Tympole, Dhelmise.\p"
	.string "GOOD ROD: Clauncher, Stunfisk, Wimpod\n"
	.string "Wishiwashi, Alomomola.\p"
	.string "SUPER ROD: Palpitoad, Bruxish, Skrelp,\n"
	.string "Frogadier, Lumineon.$"


@PEOPLE

ing_fisher1::
	msgbox ing_fisher1text, MSGBOX_NPC
	end

ing_fisher1text:
	.string "Back in my day there were two\n"
	.string "Basculins. Red and blue. Simple.\l"
	.string "Like in the Bible.\p"
	.string "A lass came in from Route 119.\n"
	.string "Her Basculin was flippin' white!\p"
	.string "What the 'eck's that about!?\n"
	.string "World's gone mad.$"

ing_fisher3::
	msgbox ing_fisher3text, MSGBOX_NPC
	end

ing_fisher3text:
	.string "Three tips fer fishin.\p"
	.string "Fish the mornin' or evenin'.\n"
	.string "Put yer line surrounded by land close.\l"
	.string "Fish with yer fingers crossed.$"


ing_fisher2::
	lock
	faceplayer
	goto_if_set FLAG_FISHERMAN_MASTER, ing_fisher_fishermaster
	checkitem ITEM_OLD_ROD
	goto_if_eq VAR_RESULT, FALSE, ing_fisher_getyoustarted
	setvar VAR_0x8004, 1
 	bufferitemname STR_VAR_3, ITEM_OLD_ROD
	checkitem ITEM_GOOD_ROD 
	call_if_eq VAR_RESULT, TRUE, ing_goodrod
	checkitem ITEM_SUPER_ROD 
	call_if_eq VAR_RESULT, TRUE, ing_superrod
	specialvar VAR_RESULT, CheckFishVsRod
	buffernumberstring STR_VAR_2, VAR_0x8006
	goto_if_eq VAR_RESULT, TRUE, ing_fisher_upgrade
	buffernumberstring STR_VAR_1, VAR_0x8005 
	msgbox ing_fisher2text, MSGBOX_DEFAULT
	release 
	end

ing_goodrod::
	setvar VAR_0x8004, 2
 	bufferitemname STR_VAR_3, ITEM_GOOD_ROD
	return

ing_superrod::
	setvar VAR_0x8004, 3
 	bufferitemname STR_VAR_3, ITEM_SUPER_ROD
	return

ing_fisher2text:
	.string "Oi oi, our fishing challenger!\p"
	.string "Looks like like you got {STR_VAR_1} fish\n"
	.string "out of {STR_VAR_2} with that {STR_VAR_3}.\p"
	.string "If you close that out, I'll get you\n"
	.string "something proper good for catching.$"

ing_fisherUpgradeMsg:
	.string "Oi oi saveloy!\n"
	.string "{STR_VAR_2} out of {STR_VAR_2}! Booyah.\p"
	.string "Here's the spoils of your success.$"

ing_fisher_getyoustarted::
	msgbox ing_fisher_getyoustarted1, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, ing_fisher_nopedthefish
	msgbox ing_fisher_getyoustarted2, MSGBOX_DEFAULT
	giveitem ITEM_OLD_ROD
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_OLD_ROD
	msgbox ing_fisherlureballshere, MSGBOX_DEFAULT
	giveitem ITEM_LURE_BALL, 5
	msgbox ing_soonanglersupreme, MSGBOX_DEFAULT
	release
	end

ing_fisher_nopedthefish::
	msgbox ing_fisher_oh, MSGBOX_DEFAULT
	release
	end

ing_fisher_getyoustarted1:
	.string "Oi oi, saveloy! The glint in your eye!\n"
	.string "You, my friend, are up for a challenge!\p"
	.string "A fishing challenge! A battle of wits\n"
	.string "between you and the raging tide!\p"
	.string "Am I right?$"

ing_fisher_oh:
	.string "Oh.$"

ing_fisher_getyoustarted2:
	.string "Yet you ain't yet met a bloke willing\n"
	.string "to give you your own FISHING ROD.\p"
	.string "It just won't do, champ!\n"
	.string "It just won't do. Here, take this.$"

ing_soonanglersupreme:
	.string "Good luck on your quest, scamp.\n"
	.string "Soon you'll be an angler supreme!$"


ing_fisher_upgrade::
	goto_if_eq VAR_0x8004, 3, ing_fisher_givesomething
	goto_if_eq VAR_0x8004, 2, ing_fisher_givesuperrod
	msgbox ing_fisherUpgradeMsg, MSGBOX_DEFAULT
	giveitem ITEM_GOOD_ROD
	msgbox ing_fisherlureballshere, MSGBOX_DEFAULT
	giveitem ITEM_LURE_BALL, 5
	msgbox ing_soonanglersupreme, MSGBOX_DEFAULT
	release
	end

ing_fisher_givesuperrod::
	msgbox ing_fisherUpgradeMsg, MSGBOX_DEFAULT
	giveitem ITEM_SUPER_ROD
	msgbox ing_fisherlureballshere, MSGBOX_DEFAULT
	giveitem ITEM_LURE_BALL, 5
	msgbox ing_soonanglersupreme, MSGBOX_DEFAULT
	release
	end

ing_fisher_givesomething::
	msgbox ing_fisherUpgradeMsg, MSGBOX_DEFAULT
	giveitem ITEM_CATCHING_CHARM
	setflag FLAG_FISHERMAN_MASTER  
ing_fisher_fishermaster::
	msgbox ing_fisherhopefuture, MSGBOX_DEFAULT
	release
	end

ing_fisherlureballshere:
	.string "And something to get you to the\n"
	.string "next step!$"

ing_fisherhopefuture:
	.string "Bravo you scamp.\p"
	.string "You are an angler supreme!$"

