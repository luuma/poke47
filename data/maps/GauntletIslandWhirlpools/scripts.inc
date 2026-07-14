


GauntletIslandWhirlpools_MapScripts::
	.byte 0

GauntletIsland_Boon1::
        lockall
	callnative ScrCmd_DoGauntletBoonList
	.byte 0
	checkitemspace ITEM_BERRY_JUICE
	goto_if_eq VAR_RESULT, FALSE, gauntlet_bag_space

	message GauntletIsland_txtWhichBoon
	waitmessage
        dynmultistack 0, 0, TRUE, 6, FALSE, VAR_0x800A, DYN_MULTICHOICE_CB_NONE
	callnative ScrCmd_LoadGauntletBoonInVarResultToboosboog
        copyvar VAR_GAUNTLET_1, VAR_RESULT
        goto gauntlet_boon_handler

gauntlet_boon_handler::
        goto_if_eq VAR_0x8009, 0, gauntlet_giveitemboon
        goto_if_eq VAR_0x8009, 1, gauntlet_giveitemboon @ This should check whether the TM can be learned by any member of the party and return to dynmultistack if player decides against it. Actually fuck that. it should just be possible to teach anything to anyone.
        goto_if_eq VAR_0x8009, 2, gauntlet_giveitemboon @ ditto for HMs
        goto_if_eq VAR_0x8009, 3, gauntlet_setflagboon
        goto_if_eq VAR_0x8009, 4, gauntlet_tutorboon
        goto_if_eq VAR_0x8009, 5, gauntlet_30berryboon
        goto_if_eq VAR_0x8009, 6, gauntlet_terrainSeeds
        goto_if_eq VAR_0x8009, 7, gauntlet_givemoneyboon
        goto_if_eq VAR_0x8009, 8, gauntlet_DEFSDEF
        @ goto_if_eq VAR_0x8009, 9, gauntlet_3randtms

        goto_if_eq VAR_0x8009, 10, gauntlet_giveitemboon
        goto_if_eq VAR_0x8009, 11, gauntlet_giveironhpupzinc
        goto_if_eq VAR_0x8009, 13, gauntlet_tutorboon//rerollplustutor
        goto_if_eq VAR_0x8009, 14, gauntlet_TOXICFLAME
GauntletIsland_return::
        callnative AddDevotionTo0x8008
        goto_if_eq VAR_0x8009, 12, GauntletIsland_Boon1
        goto_if_eq VAR_0x8009, 13, GauntletIsland_Boon1//rerollplustutor
        releaseall
        end

gauntlet_bag_space::
	message GauntletIsland_BagSpace
        releaseall
        end


gauntlet_giveitemboon::
	giveitem VAR_0x8005, VAR_0x8004
        goto GauntletIsland_return
	end

gauntlet_setflagboon::
        setflag VAR_0x8008
        goto GauntletIsland_return
	end

gauntlet_tutorboon::
	call MoveTutor_EventScript_OpenPartyMenu
	goto_if_eq VAR_RESULT, 0, MoveTutor_EventScript_FuryCutterDeclined
	goto GauntletIsland_return
	end


MoveTutor_EventScript_gauntletdeclined::
	message GauntletIsland_Compensated
        giveitem ITEM_HYPER_POTION
	goto GauntletIsland_return
	end


gauntlet_givemoneyboon::
	showmoneybox 0, 0
	addmoney VAR_0x8005
	updatemoneybox
	hidemoneybox
	message GauntletIsland_Compensated
        goto GauntletIsland_return
	end

gauntlet_30berryboon::
        giverandomberryX5 BERRY_ID_LIECHI, BERRY_ID_STARF
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
        giverandomberryX5 BERRY_ID_OCCA, BERRY_ID_ROSELI
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
        giverandomberryX5 BERRY_ID_POMEG, BERRY_ID_TAMATO
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
        giverandomberryX5 BERRY_ID_FIGY, BERRY_ID_IAPAPA
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
        giverandomberryX5 BERRY_ID_CHERI, BERRY_ID_SITRUS
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
        giverandomberryX5 BERRY_ID_CHERI, BERRY_ID_SITRUS
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
        goto GauntletIsland_return
	end

gauntlet_terrainSeeds::
	giveitem ITEM_GRASSY_SEED, 5
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
	giveitem ITEM_MISTY_SEED, 5
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
	giveitem ITEM_ELECTRIC_SEED, 5
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
	giveitem ITEM_PSYCHIC_SEED, 5
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
        goto GauntletIsland_return
	end

gauntlet_giveironhpupzinc::
	giveitem ITEM_HP_UP, 10
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
	giveitem ITEM_IRON, 10
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
	giveitem ITEM_ZINC, 10
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
        goto GauntletIsland_return
	end

gauntlet_DEFSDEF::
	giveitem ITEM_X_DEFEND, 10
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
	giveitem ITEM_X_SP_DEF, 10
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
        goto GauntletIsland_return
	end


gauntlet_TOXICFLAME::
	giveitem ITEM_TOXIC_ORB, 2
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
	giveitem ITEM_FLAME_ORB, 2
	goto_if_eq VAR_RESULT, 0, Common_EventScript_ShowBagIsFull
        goto GauntletIsland_return
	end


GauntletIsland_txtWhichBoon:
	.string "Possibilities swirl before you.\n"
	.string "Which boon will be chosen?$"

GauntletIsland_Compensated:
	.string "{PLAYER} received compensation.$"

GauntletIsland_txtHeyThatsDumbOfYou:
	.string "No POKéMON in your PARTY can\n"
	.string "currently be taught this.\p"
	.string "Continue anyway?$"

GauntletIsland_BagSpace:
	.string "There is not enough space in.\n"
	.string "the BAG.$"

