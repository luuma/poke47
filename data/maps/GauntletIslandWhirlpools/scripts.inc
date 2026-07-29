


GauntletIslandWhirlpools_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, GauntletIslandOnTransition
	.byte 0

GauntletIsland_Boon1::
        lockall
	checkitemspace ITEM_BERRY_JUICE
	goto_if_eq VAR_RESULT, FALSE, gauntlet_bag_space
	callnative ScrCmd_DoGauntletBoonList
	.byte 0
	.byte 1
	message GauntletIsland_txtWhichBoon
	waitmessage
        dynmultistack 4, 2, TRUE, 6, FALSE, VAR_0x800A, DYN_MULTICHOICE_CB_NONE
	callnative ScrCmd_LoadGauntletBoonInVarResultToboosboog
        copyvar VAR_GAUNTLET_1, VAR_RESULT
        goto gauntlet_boon_handler

GauntletIsland_Boon2::
        lockall
	checkitemspace ITEM_BERRY_JUICE
	goto_if_eq VAR_RESULT, FALSE, gauntlet_bag_space
	callnative ScrCmd_DoGauntletBoonList
	.byte 1
	.byte 2
	message GauntletIsland_txtWhichBoon
	waitmessage
        dynmultistack 4, 2, TRUE, 6, FALSE, VAR_0x800A, DYN_MULTICHOICE_CB_NONE
	callnative ScrCmd_LoadGauntletBoonInVarResultToboosboog
        copyvar VAR_GAUNTLET_2, VAR_RESULT
	setflag FLAG_GAUNTLET_boon2
        removeobject VAR_LAST_TALKED
        goto gauntlet_boon_handler


GauntletIsland_Boon3::
        lockall
	checkitemspace ITEM_BERRY_JUICE
	goto_if_eq VAR_RESULT, FALSE, gauntlet_bag_space
	callnative ScrCmd_DoGauntletBoonList
	.byte 2
	.byte 3
	message GauntletIsland_txtWhichBoon
	waitmessage
        dynmultistack 4, 2, TRUE, 6, FALSE, VAR_0x800A, DYN_MULTICHOICE_CB_NONE
	callnative ScrCmd_LoadGauntletBoonInVarResultToboosboog
        copyvar VAR_GAUNTLET_3, VAR_RESULT
        goto gauntlet_boon_handler

GauntletIsland_Boon4::
        lockall
	checkitemspace ITEM_BERRY_JUICE
	goto_if_eq VAR_RESULT, FALSE, gauntlet_bag_space
	callnative ScrCmd_DoGauntletBoonList
	.byte 2
	.byte 4
	message GauntletIsland_txtWhichBoon
	waitmessage
        dynmultistack 4, 2, TRUE, 6, FALSE, VAR_0x800A, DYN_MULTICHOICE_CB_NONE
	callnative ScrCmd_LoadGauntletBoonInVarResultToboosboog
        copyvar VAR_GAUNTLET_4, VAR_RESULT
	setflag FLAG_GAUNTLET_boon4
        removeobject VAR_LAST_TALKED
        goto gauntlet_boon_handler

GauntletIsland_Boon5::
        lockall
	checkitemspace ITEM_BERRY_JUICE
	goto_if_eq VAR_RESULT, FALSE, gauntlet_bag_space
	callnative ScrCmd_DoGauntletBoonList
	.byte 3
	.byte 5
	message GauntletIsland_txtWhichBoon
	waitmessage
        dynmultistack 4, 2, TRUE, 6, FALSE, VAR_0x800A, DYN_MULTICHOICE_CB_NONE
	callnative ScrCmd_LoadGauntletBoonInVarResultToboosboog
        copyvar VAR_GAUNTLET_5, VAR_RESULT
        goto gauntlet_boon_handler

GauntletIsland_Boon6::
        lockall
	checkitemspace ITEM_BERRY_JUICE
	goto_if_eq VAR_RESULT, FALSE, gauntlet_bag_space
	callnative ScrCmd_DoGauntletBoonList
	.byte 3
	.byte 6
	message GauntletIsland_txtWhichBoon
	waitmessage
        dynmultistack 4, 2, TRUE, 6, FALSE, VAR_0x800A, DYN_MULTICHOICE_CB_NONE
	callnative ScrCmd_LoadGauntletBoonInVarResultToboosboog
        copyvar VAR_GAUNTLET_6, VAR_RESULT
	setflag FLAG_GAUNTLET_boon6
        removeobject VAR_LAST_TALKED
        goto gauntlet_boon_handler

GauntletIsland_Boon7::
        lockall
	checkitemspace ITEM_BERRY_JUICE
	goto_if_eq VAR_RESULT, FALSE, gauntlet_bag_space
	callnative ScrCmd_DoGauntletBoonList
	.byte 3
	.byte 7
	message GauntletIsland_txtWhichBoon
	waitmessage
        dynmultistack 4, 2, TRUE, 6, FALSE, VAR_0x800A, DYN_MULTICHOICE_CB_NONE
	callnative ScrCmd_LoadGauntletBoonInVarResultToboosboog
        goto gauntlet_boon_handler

GauntletIsland_Boon8::
        lockall
	checkitemspace ITEM_BERRY_JUICE
	goto_if_eq VAR_RESULT, FALSE, gauntlet_bag_space
	callnative ScrCmd_DoGauntletBoonList @ also loads an internal value that is later corresponded to a var in setvartoboon.
	.byte 5
	.byte 8
	message GauntletIsland_txtWhichBoon
	waitmessage
        dynmultistack 4, 2, TRUE, 6, FALSE, VAR_0x800A, DYN_MULTICHOICE_CB_NONE
	callnative ScrCmd_LoadGauntletBoonInVarResultToboosboog
	setflag FLAG_GAUNTLET_boon8
        removeobject VAR_LAST_TALKED
        goto gauntlet_boon_handler

GauntletIsland_Boon9::
        lockall
	checkitemspace ITEM_BERRY_JUICE
	goto_if_eq VAR_RESULT, FALSE, gauntlet_bag_space
	callnative ScrCmd_DoGauntletBoonList @ also loads an internal value that is later corresponded to a var in setvartoboon.
	.byte 5
	.byte 9
	message GauntletIsland_txtWhichBoon
	waitmessage
        dynmultistack 4, 2, TRUE, 6, FALSE, VAR_0x800A, DYN_MULTICHOICE_CB_NONE
	callnative ScrCmd_LoadGauntletBoonInVarResultToboosboog
	setflag FLAG_GAUNTLET_boon9 // uses var gauntlet A. Only for sake of record-keeping.
        removeobject VAR_LAST_TALKED
        goto gauntlet_boon_handler



GauntletIsland_Reroll::
	callnative ScrCmd_DoGauntletBoonList
	.byte 3
	.byte 12 @ Doesn't load the result into a defined var.
	message GauntletIsland_txtWhichBoon
	waitmessage
        dynmultistack 4, 2, TRUE, 6, FALSE, VAR_0x800A, DYN_MULTICHOICE_CB_NONE
	callnative ScrCmd_LoadGauntletBoonInVarResultToboosboog
gauntlet_boon_handler::
        goto_if_eq VAR_0x8007, 15, gauntlet_giveitemboon
        goto_if_eq VAR_0x8007, 1, gauntlet_giveitemboon @ This should check whether the TM can be learned by any member of the party and return to dynmultistack if player decides against it. Actually fuck that. it should just be possible to teach anything to anyone.
        goto_if_eq VAR_0x8007, 2, gauntlet_giveitemboon @ ditto for HMs
        @ goto_if_eq VAR_0x8007, 3, gauntlet_setflagboon @ handled in ScrCmd_LoadGauntletBoonInVarResultToboosboog. 
        goto_if_eq VAR_0x8007, 4, gauntlet_tutorboon

        goto_if_eq VAR_0x8007, 13, gauntlet_tutorboon//rerollplustutor
        goto_if_eq VAR_0x8007, 9, gauntlet_giveHerbReroll
        goto_if_eq VAR_0x8007, 10, gauntlet_giveitemboon10
        goto_if_eq VAR_0x8007, 17, gauntlet_setweather
        goto_if_eq VAR_0x8007, 18, gauntlet_setstartingstatus
        goto_if_eq VAR_0x8007, 19, gauntlet_giveitemboon3

        goto_if_eq VAR_0x8007, 5, gauntlet_30berryboon
        goto_if_eq VAR_0x8007, 6, gauntlet_terrainSeeds
        goto_if_eq VAR_0x8007, 7, gauntlet_givemoneyboon

        goto_if_eq VAR_0x8007, 8, gauntlet_DEFSDEF
        goto_if_eq VAR_0x8007, 11, gauntlet_giveironhpupzinc
        goto_if_eq VAR_0x8007, 14, gauntlet_TOXICFLAME
        goto_if_eq VAR_0x8007, 16, gauntlet_rods
        goto_if_eq VAR_0x8007, 20, gauntlet_evolve
        goto_if_eq VAR_0x8007, 21, gauntlet_givepkmn

GauntletIsland_return::
        callnative AddDevotionTo0x8008
        call_if_eq VAR_0x8008, 0, GauntletIsland_saphmsg
        call_if_eq VAR_0x8008, 1, GauntletIsland_nereidmsg
        call_if_eq VAR_0x8008, 2, GauntletIsland_eldwmsg
        call_if_eq VAR_0x8008, 3, GauntletIsland_dsotm
        call_if_eq VAR_0x8008, 4, GauntletIsland_lith
        call_if_eq VAR_0x8008, 5, GauntletIsland_Wingymsg
        call_if_ge VAR_0x8008, 6, GauntletIsland_islandmsg

        goto_if_eq VAR_0x8007, 9, GauntletIsland_Reroll
        goto_if_eq VAR_0x8007, 12, GauntletIsland_Reroll
        goto_if_eq VAR_0x8007, 13, GauntletIsland_Reroll
        callnative ScrCmd_SetvarToBoon
        releaseall
        end

gauntlet_bag_space::
	msgbox GauntletIsland_BagSpace
        releaseall
        end

gauntlet_giveitemboon::
	giveitem VAR_0x8005, 1
        goto GauntletIsland_return
	end

gauntlet_giveitemboon10::
	giveitem VAR_0x8005, 10
        goto GauntletIsland_return
	end

gauntlet_giveitemboon3::
	giveitem VAR_0x8005, 3
        goto GauntletIsland_return
	end

gauntlet_giveHerbReroll:: @ This doesn't use as many vars to buffer info. Giveitem uses 0x8004 to 0x8007 inclusive. also there can only be one: this doesn't handle a full bag.
        bufferitemname STR_VAR_2, ITEM_REVIVAL_HERB
        giveitem_msg Gauntlet_Text_Obtained, ITEM_REVIVAL_HERB, 1
        goto GauntletIsland_return
	end

Gauntlet_Text_Obtained::
	.string "Obtained a {STR_VAR_2}!$"

gauntlet_setflagboon::
        setflag VAR_0x8008
        goto GauntletIsland_return
	end

gauntlet_tutorboon::
	copyvar VAR_0x8006, VAR_0x8005
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, gauntlet_tutorboon_DeclinedOnce
	goto GauntletIsland_return
	end


gauntlet_tutorboon_DeclinedOnce::
	msgbox GauntletIsland_TutorAnotherMon MSGBOX_YESNO
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_gauntletdeclined
	copyvar VAR_0x8005, VAR_0x8006
	goto gauntlet_tutorboon
	end

MoveTutor_EventScript_gauntletdeclined::
	msgbox GauntletIsland_Compensated
	waitmessage
	showmoneybox 0, 0
        delay 40
	addmoney 1000
	updatemoneybox
        playse SE_ITEMFINDER
        waitse
	hidemoneybox
	goto GauntletIsland_return
	end

gauntlet_evolve::
	special ChoosePartyMon
	goto_if_ge VAR_0x8004, PARTY_SIZE, gauntlet_evoboon_DeclinedOnce
	callnative Script_GauntletTriggerUniqueEvolution
        goto GauntletIsland_return
	end


gauntlet_evoboon_DeclinedOnce::
	msgbox GauntletIsland_EvoAMon MSGBOX_YESNO
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_gauntletdeclined
	goto gauntlet_evolve
	end


gauntlet_givepkmn::
	bufferspeciesname STR_VAR_1, SPECIES_ALOLAN_EXEGGUTOR
        setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_ALOLAN_EXEGGUTOR
        givemon SPECIES_ALOLAN_EXEGGUTOR, 20
        goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, gauntlet_givepkmn_Party
        goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, gauntlet_givepkmn_PC
	msgbox gText_NoMoreRoomForPokemon, MSGBOX_DEFAULT
        goto GauntletIsland_return
	end


gauntlet_givepkmn_Party::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, GauntletIsland_return
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto GauntletIsland_return
	end

gauntlet_givepkmn_PC::
	call gauntlet_givepkmn_ReceivedFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, gauntlet_givepkmn_TransferToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RustboroCity_DevonCorp_2F_EventScript_TransferToPC
	end

gauntlet_givepkmn_EventScript_TransferToPC::
	call Common_EventScript_TransferredToPC
	goto GauntletIsland_return
	end

gauntlet_givepkmn_ReceivedFanfare::
	playfanfare MUS_OBTAIN_ITEM
	message gauntlet_givepkmn_Text_ReceivedMon
	waitmessage
	waitfanfare
	return

GauntletIsland_EvoAMon:
	.string "Evolve a POKéMON?$"


gauntlet_givepkmn_Text_ReceivedMon



gauntlet_givemoneyboon::
	goto_if_gt VAR_0x8005, 9000, gauntlet_givemoneyboonbig
	message GauntletIsland_Compensated
	waitmessage
	showmoneybox 0, 0
        delay 40
	addmoney 1000
	updatemoneybox
        playse SE_ITEMFINDER
        waitse
	addmoney 1000
	updatemoneybox
        playse SE_ITEMFINDER
        waitse
	addmoney 1000
	updatemoneybox
        playse SE_ITEMFINDER
        waitse
	addmoney 1000
	updatemoneybox
        playse SE_ITEMFINDER
        waitse
	addmoney 1000
	updatemoneybox
        playse SE_ITEMFINDER
        waitse
	hidemoneybox
        goto GauntletIsland_return
	end

gauntlet_givemoneyboonbig::
	message GauntletIsland_Compensated
	waitmessage
	showmoneybox 0, 0
        delay 40
	addmoney 10000
	updatemoneybox
        playse SE_ITEMFINDER
        waitse
	addmoney 10000
	updatemoneybox
        playse SE_ITEMFINDER
        waitse
	addmoney 10000
	updatemoneybox
        playse SE_ITEMFINDER
        waitse
	addmoney 10000
	updatemoneybox
        playse SE_ITEMFINDER
        waitse
	addmoney 10000
	updatemoneybox
        playse SE_ITEMFINDER
        waitse
	hidemoneybox
        goto GauntletIsland_return
	end

Gauntlet_EventScript_ShowBagIsFull::
	msgbox gText_TooBadBagIsFull, MSGBOX_DEFAULT
        goto GauntletIsland_return
        end

gauntlet_30berryboon::
        giverandomberryX5 BERRY_ID_LIECHI, BERRY_ID_STARF
	goto_if_eq VAR_RESULT, 0, Gauntlet_EventScript_ShowBagIsFull
        giverandomberryX5 BERRY_ID_OCCA, BERRY_ID_ROSELI
	goto_if_eq VAR_RESULT, 0, Gauntlet_EventScript_ShowBagIsFull
        giverandomberryX5 BERRY_ID_POMEG, BERRY_ID_TAMATO
	goto_if_eq VAR_RESULT, 0, Gauntlet_EventScript_ShowBagIsFull
        giverandomberryX5 BERRY_ID_FIGY, BERRY_ID_IAPAPA
	goto_if_eq VAR_RESULT, 0, Gauntlet_EventScript_ShowBagIsFull
        giverandomberryX5 BERRY_ID_CHERI, BERRY_ID_SITRUS
	goto_if_eq VAR_RESULT, 0, Gauntlet_EventScript_ShowBagIsFull
        giverandomberryX5 BERRY_ID_CHERI, BERRY_ID_SITRUS
	goto_if_eq VAR_RESULT, 0, Gauntlet_EventScript_ShowBagIsFull
        goto GauntletIsland_return
	end

gauntlet_terrainSeeds::
	giveitem ITEM_GRASSY_SEED, 5
	goto_if_eq VAR_RESULT, 0, Gauntlet_EventScript_ShowBagIsFull
	giveitem ITEM_MISTY_SEED, 5
	goto_if_eq VAR_RESULT, 0, Gauntlet_EventScript_ShowBagIsFull
	giveitem ITEM_ELECTRIC_SEED, 5
	goto_if_eq VAR_RESULT, 0, Gauntlet_EventScript_ShowBagIsFull
	giveitem ITEM_PSYCHIC_SEED, 5
	goto_if_eq VAR_RESULT, 0, Gauntlet_EventScript_ShowBagIsFull
        goto GauntletIsland_return
	end

gauntlet_rods::
        giveitem ITEM_OLD_ROD
	goto_if_eq VAR_RESULT, 0, Gauntlet_EventScript_ShowBagIsFull
	setvar VAR_0x8004, 1
	specialvar VAR_RESULT, CheckFishVsRod
        goto_if_eq VAR_RESULT, FALSE, GauntletIsland_return @ DONE IN Same way as the fisher shack.
        giveitem ITEM_GOOD_ROD
	goto_if_eq VAR_RESULT, 0, Gauntlet_EventScript_ShowBagIsFull
	setvar VAR_0x8004, 2
	specialvar VAR_RESULT, CheckFishVsRod
        goto_if_eq VAR_RESULT, FALSE, GauntletIsland_return
        giveitem ITEM_SUPER_ROD
	goto_if_eq VAR_RESULT, 0, Gauntlet_EventScript_ShowBagIsFull
        goto GauntletIsland_return
        end

gauntlet_giveironhpupzinc::
	giveitem ITEM_HP_UP, 10
	goto_if_eq VAR_RESULT, 0, Gauntlet_EventScript_ShowBagIsFull
	giveitem ITEM_IRON, 10
	goto_if_eq VAR_RESULT, 0, Gauntlet_EventScript_ShowBagIsFull
	giveitem ITEM_ZINC, 10
	goto_if_eq VAR_RESULT, 0, Gauntlet_EventScript_ShowBagIsFull
        goto GauntletIsland_return
	end

gauntlet_DEFSDEF::
	giveitem ITEM_X_DEFEND, 10
	goto_if_eq VAR_RESULT, 0, Gauntlet_EventScript_ShowBagIsFull
	giveitem ITEM_X_SP_DEF, 10
	goto_if_eq VAR_RESULT, 0, Gauntlet_EventScript_ShowBagIsFull
        goto GauntletIsland_return
	end


gauntlet_TOXICFLAME::
	giveitem ITEM_TOXIC_ORB, 2
	goto_if_eq VAR_RESULT, 0, Gauntlet_EventScript_ShowBagIsFull
	giveitem ITEM_FLAME_ORB, 2
	goto_if_eq VAR_RESULT, 0, Gauntlet_EventScript_ShowBagIsFull
        goto GauntletIsland_return
	end


gauntlet_setweather::
        copyvar VAR_GAUNTLET_WEATHER, VAR_0x8005
        setweather VAR_GAUNTLET_WEATHER
	doweather
	special WaitWeather
	delay 30
        goto GauntletIsland_return
	end

gauntlet_setstartingstatus::
        callnative ScrCmd_SetGauntletVarStartingStatus
        goto GauntletIsland_return
	end


GauntletIsland_saphmsg::
	msgbox GauntletIsland_txtsaphmsg
        return

GauntletIsland_nereidmsg::
	msgbox GauntletIsland_txtnereidmsg
        return

GauntletIsland_eldwmsg::
	msgbox GauntletIsland_txteldwmsg
        return

GauntletIsland_lith::
	msgbox GauntletIsland_txtlithmsg
        return

GauntletIsland_dsotm::
	msgbox GauntletIsland_txtdsotmmsg
        return

GauntletIsland_Wingymsg::
	msgbox GauntletIsland_txtWingymsg
        return

GauntletIsland_islandmsg::
	msgbox GauntletIsland_txtdevotiontoislandmsg
        return

GauntletIsland_txtsaphmsg:
	.string "Your devotion to the cycle of\n"
	.string "harvest and decay is noted.$"

GauntletIsland_txtnereidmsg:
	.string "Your devotion to the tricks\n"
	.string "of the ocean nereids is noted.$"

GauntletIsland_txteldwmsg:
	.string "Your devotion to the strength\n"
	.string "of the elder dragon is noted.$"

GauntletIsland_txtlithmsg:
	.string "Your devotion to the might and\n"
	.string "patience of the mountain is noted.$"

GauntletIsland_txtdsotmmsg:
	.string "Your devotion to the curious\n"
	.string "and eerie is noted.$"

GauntletIsland_txtWingymsg:
	.string "Your devotion to the glory and\n"
	.string "justice of the Winged Lion is noted.$"

GauntletIsland_txtdevotiontoislandmsg:
	.string "Your devotion to the island\n"
	.string "is noted.$"


GauntletIsland_txtWhichBoon:
	.string "Possibilities swirl before you.\n"
	.string "Which BOON will be chosen?$"

GauntletIsland_Compensated:
	.string "{PLAYER} received compensation.$"

GauntletIsland_txtHeyThatsDumbOfYou:
	.string "No POKéMON in your PARTY can\n"
	.string "currently be taught this.\p"
	.string "Continue anyway?$"

GauntletIsland_TutorAnotherMon:
	.string "Tutor a different POKéMON?$"

GauntletIsland_EvoAMon:
	.string "Evolve a POKéMON?$"

GauntletIsland_BagSpace:
	.string "There is not enough space in.\n"
	.string "the BAG.$"

