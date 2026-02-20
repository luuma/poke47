RustboroCity_DevonCorp_2F_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_DevonCorp_2F_OnTransition
	.byte 0

RustboroCity_DevonCorp_2F_OnTransition:
	call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	end

RustboroCity_DevonCorp_2F_EventScript_SetFossilReady::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 2
	return

RustboroCity_DevonCorp_2F_EventScript_TalkToPokemonScientist::
	lock
	faceplayer
	call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	msgbox RustboroCity_DevonCorp_2F_Text_DeviceForTalkingToPokemon, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_BallScientist::
	lock
	faceplayer
	call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	goto_if_set FLAG_MET_DEVON_EMPLOYEE, RustboroCity_DevonCorp_2F_EventScript_DevelopedBalls
	msgbox RustboroCity_DevonCorp_2F_Text_DevelopingNewBalls, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_DevelopedBalls::
	msgbox RustboroCity_DevonCorp_2F_Text_WeFinallyMadeNewBalls, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_PokenavScientist::
	lock
	faceplayer
	call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	goto_if_set FLAG_RECEIVED_POKENAV, RustboroCity_DevonCorp_2F_EventScript_HasPokenav
	msgbox RustboroCity_DevonCorp_2F_Text_IMadePokenav, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_HasPokenav::
	msgbox RustboroCity_DevonCorp_2F_Text_WowThatsAPokenav, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_PokemonDreamsScientist::
	lock
	faceplayer
	call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	msgbox RustboroCity_DevonCorp_2F_Text_DeviceToVisualizePokemonDreams, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_FossilScientist::
	lock
	faceplayer
	goto_if_eq VAR_FOSSIL_RESURRECTION_STATE, 2, RustboroCity_DevonCorp_2F_EventScript_FossilMonReady
	goto_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_StillRegenerating
	msgbox RustboroCity_DevonCorp_2F_Text_DevelopDeviceToResurrectFossils, MSGBOX_DEFAULT 
	goto_if_ne VAR_TEMP_2, 0, RustboroCity_DevonCorp_2F_EventScript_NoticeFossil
	checkitem ITEM_HELIX_FOSSIL, 1
	call_if_ne VAR_RESULT, FALSE, RustboroCity_DevonCorp_2F_EventScript_MultipushHelix 
	checkitem ITEM_DOME_FOSSIL, 1
	call_if_ne VAR_RESULT, FALSE, RustboroCity_DevonCorp_2F_EventScript_MultipushDome    
	checkitem ITEM_ROOT_FOSSIL, 1
	call_if_ne VAR_RESULT, FALSE, RustboroCity_DevonCorp_2F_EventScript_MultipushRoot
	checkitem ITEM_CLAW_FOSSIL, 1
	call_if_ne VAR_RESULT, FALSE, RustboroCity_DevonCorp_2F_EventScript_MultipushClaw    
	checkitem ITEM_SKULL_FOSSIL, 1
	call_if_ne VAR_RESULT, FALSE, RustboroCity_DevonCorp_2F_EventScript_MultipushSkull
	checkitem ITEM_ARMOR_FOSSIL, 1
	call_if_ne VAR_RESULT, FALSE, RustboroCity_DevonCorp_2F_EventScript_MultipushArmor
	checkitem ITEM_PLUME_FOSSIL, 1
	call_if_ne VAR_RESULT, FALSE, RustboroCity_DevonCorp_2F_EventScript_MultipushPlume
	checkitem ITEM_COVER_FOSSIL, 1
	call_if_ne VAR_RESULT, FALSE, RustboroCity_DevonCorp_2F_EventScript_MultipushCover
	checkitem ITEM_JAW_FOSSIL, 1
	call_if_ne VAR_RESULT, FALSE, RustboroCity_DevonCorp_2F_EventScript_MultipushJaw
	checkitem ITEM_SAIL_FOSSIL, 1
	call_if_ne VAR_RESULT, FALSE, RustboroCity_DevonCorp_2F_EventScript_MultipushSail
	checkitem ITEM_OLD_AMBER, 1
	call_if_eq VAR_RESULT, TRUE, RustboroCity_DevonCorp_2F_EventScript_MultipushOldAmber
	goto_if_ne VAR_TEMP_2, 0, RustboroCity_DevonCorp_2F_EventScript_NoticeFossil
	closemessage
	release
	end

RustboroCity_DevonCorp_2F_EventScript_MultipushHelix:: 
	setvar VAR_0x8008 ITEM_HELIX_FOSSIL          
    	dynmultipush RustboroCity_DevonCorp_2F_Text_HelixFossil, ITEM_HELIX_FOSSIL
	addvar VAR_TEMP_2, 1
	return

RustboroCity_DevonCorp_2F_EventScript_MultipushDome::
	setvar VAR_0x8008 ITEM_DOME_FOSSIL
    	dynmultipush RustboroCity_DevonCorp_2F_Text_DomeFossil, ITEM_DOME_FOSSIL
	addvar VAR_TEMP_2, 1
	return

RustboroCity_DevonCorp_2F_EventScript_MultipushRoot::
	setvar VAR_0x8008 ITEM_ROOT_FOSSIL
    	dynmultipush RustboroCity_DevonCorp_2F_Text_RootFossil, ITEM_ROOT_FOSSIL
	addvar VAR_TEMP_2, 1
	return

RustboroCity_DevonCorp_2F_EventScript_MultipushClaw::
	setvar VAR_0x8008 ITEM_CLAW_FOSSIL
    	dynmultipush RustboroCity_DevonCorp_2F_Text_ClawFossil, ITEM_CLAW_FOSSIL @ Ideally I should be able to point to an item name
	addvar VAR_TEMP_2, 1
	return

RustboroCity_DevonCorp_2F_EventScript_MultipushSkull::
	setvar VAR_0x8008 ITEM_SKULL_FOSSIL
    	dynmultipush RustboroCity_DevonCorp_2F_Text_SkullFossil, ITEM_SKULL_FOSSIL
	addvar VAR_TEMP_2, 1
	return

RustboroCity_DevonCorp_2F_EventScript_MultipushArmor::
	setvar VAR_0x8008 ITEM_ARMOR_FOSSIL
    	dynmultipush RustboroCity_DevonCorp_2F_Text_ArmorFossil, ITEM_ARMOR_FOSSIL
	addvar VAR_TEMP_2, 1
	return

RustboroCity_DevonCorp_2F_EventScript_MultipushPlume::
	setvar VAR_0x8008 ITEM_PLUME_FOSSIL
    	dynmultipush RustboroCity_DevonCorp_2F_Text_PlumeFossil, ITEM_PLUME_FOSSIL
	addvar VAR_TEMP_2, 1
	return

RustboroCity_DevonCorp_2F_EventScript_MultipushCover::
	setvar VAR_0x8008 ITEM_COVER_FOSSIL
    	dynmultipush RustboroCity_DevonCorp_2F_Text_CoverFossil, ITEM_COVER_FOSSIL
	addvar VAR_TEMP_2, 1
	return

RustboroCity_DevonCorp_2F_EventScript_MultipushJaw::
	setvar VAR_0x8008 ITEM_JAW_FOSSIL
    	dynmultipush RustboroCity_DevonCorp_2F_Text_JawFossil, ITEM_JAW_FOSSIL
	addvar VAR_TEMP_2, 1
	return

RustboroCity_DevonCorp_2F_EventScript_MultipushSail::
	setvar VAR_0x8008 ITEM_SAIL_FOSSIL
    	dynmultipush RustboroCity_DevonCorp_2F_Text_SailFossil, ITEM_SAIL_FOSSIL
	addvar VAR_TEMP_2, 1
	return

RustboroCity_DevonCorp_2F_EventScript_MultipushOldAmber::
	setvar VAR_0x8008 ITEM_OLD_AMBER
    	dynmultipush RustboroCity_DevonCorp_2F_Text_OldAmber, ITEM_OLD_AMBER
	addvar VAR_TEMP_2, 1
	return

RustboroCity_DevonCorp_2F_EventScript_NoticeFossil::
	closemessage
	playse SE_PIN
	applymovement LOCALID_FOSSIL_SCIENTIST, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_FOSSIL_SCIENTIST, Common_Movement_Delay48
	waitmovement 0
	msgbox RustboroCity_DevonCorp_2F_Text_WantToBringFossilBackToLife, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_DeclineGiveFossil
	goto_if_ne VAR_TEMP_2, 1, RustboroCity_DevonCorp_2F_EventScript_ChooseFossil
	goto RustboroCity_DevonCorp_2F_EventScript_GiveFossil
	end

RustboroCity_DevonCorp_2F_EventScript_GiveFossil::
	bufferitemname STR_VAR_1, VAR_0x8008
	msgbox RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher, MSGBOX_DEFAULT
	removeitem VAR_0x8008
	setvar VAR_FOSSIL_RESURRECTION_STATE, 1
	copyvar VAR_WHICH_FOSSIL_REVIVED, VAR_0x8008
	release
	end

RustboroCity_DevonCorp_2F_EventScript_DeclineGiveFossil::
	msgbox RustboroCity_DevonCorp_2F_Text_OhIsThatSo, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_StillRegenerating::
	msgbox RustboroCity_DevonCorp_2F_Text_FossilRegeneratorTakesTime, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_FossilMonReady::
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, ITEM_HELIX_FOSSIL, RustboroCity_DevonCorp_2F_EventScript_OmanyteReady
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, ITEM_DOME_FOSSIL, RustboroCity_DevonCorp_2F_EventScript_KabutoReady
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, ITEM_ROOT_FOSSIL, RustboroCity_DevonCorp_2F_EventScript_LileepReady
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, ITEM_CLAW_FOSSIL, RustboroCity_DevonCorp_2F_EventScript_AnorithReady
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, ITEM_SKULL_FOSSIL, RustboroCity_DevonCorp_2F_EventScript_CranidosReady
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, ITEM_ARMOR_FOSSIL, RustboroCity_DevonCorp_2F_EventScript_ShieldonReady
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, ITEM_COVER_FOSSIL, RustboroCity_DevonCorp_2F_EventScript_TirtougaReady
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, ITEM_PLUME_FOSSIL, RustboroCity_DevonCorp_2F_EventScript_ArchenReady
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, ITEM_SAIL_FOSSIL, RustboroCity_DevonCorp_2F_EventScript_AmauraReady
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, ITEM_JAW_FOSSIL, RustboroCity_DevonCorp_2F_EventScript_TyruntReady
	goto_if_eq VAR_WHICH_FOSSIL_REVIVED, ITEM_OLD_AMBER, RustboroCity_DevonCorp_2F_EventScript_AerodactylReady
	end

RustboroCity_DevonCorp_2F_EventScript_OmanyteReady::
	bufferspeciesname STR_VAR_2, SPECIES_OMANYTE
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
        bufferspeciesname STR_VAR_1, SPECIES_OMANYTE
        setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_OMANYTE
        givemon SPECIES_OMANYTE, 20
        goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveFossilParty
        goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveFossilPC
        goto Common_EventScript_NoMoreRoomForPokemon
        end

RustboroCity_DevonCorp_2F_EventScript_KabutoReady::
	bufferspeciesname STR_VAR_2, SPECIES_KABUTO
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
        bufferspeciesname STR_VAR_1, SPECIES_KABUTO
        setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_KABUTO
        givemon SPECIES_KABUTO, 20
        goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveFossilParty
        goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveFossilPC
        goto Common_EventScript_NoMoreRoomForPokemon
        end

RustboroCity_DevonCorp_2F_EventScript_LileepReady::
	bufferspeciesname STR_VAR_2, SPECIES_LILEEP
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
        bufferspeciesname STR_VAR_1, SPECIES_LILEEP
        setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_LILEEP
        givemon SPECIES_LILEEP, 20
        goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveFossilParty
        goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveFossilPC
        goto Common_EventScript_NoMoreRoomForPokemon
        end

RustboroCity_DevonCorp_2F_EventScript_AnorithReady::
	bufferspeciesname STR_VAR_2, SPECIES_ANORITH
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
        bufferspeciesname STR_VAR_1, SPECIES_ANORITH
        setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_ANORITH
        givemon SPECIES_ANORITH, 20
        goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveFossilParty
        goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveFossilPC
        goto Common_EventScript_NoMoreRoomForPokemon
        end

RustboroCity_DevonCorp_2F_EventScript_CranidosReady::
	bufferspeciesname STR_VAR_2, SPECIES_CRANIDOS
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
        bufferspeciesname STR_VAR_1, SPECIES_CRANIDOS
        setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_CRANIDOS
        givemon SPECIES_CRANIDOS, 20
        goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveFossilParty
        goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveFossilPC
        goto Common_EventScript_NoMoreRoomForPokemon
        end

RustboroCity_DevonCorp_2F_EventScript_ShieldonReady::
	bufferspeciesname STR_VAR_2, SPECIES_SHIELDON
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
        bufferspeciesname STR_VAR_1, SPECIES_SHIELDON
        setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_SHIELDON
        givemon SPECIES_SHIELDON, 20
        goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveFossilParty
        goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveFossilPC
        goto Common_EventScript_NoMoreRoomForPokemon
        end

RustboroCity_DevonCorp_2F_EventScript_ArchenReady::
	bufferspeciesname STR_VAR_2, SPECIES_ARCHEN
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
        bufferspeciesname STR_VAR_1, SPECIES_ARCHEN
        setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_ARCHEN
        givemon SPECIES_ARCHEN, 20
        goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveFossilParty
        goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveFossilPC
        goto Common_EventScript_NoMoreRoomForPokemon
        end

RustboroCity_DevonCorp_2F_EventScript_TirtougaReady::
	bufferspeciesname STR_VAR_2, SPECIES_TIRTOUGA
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
        bufferspeciesname STR_VAR_1, SPECIES_TIRTOUGA
        setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_TIRTOUGA
        givemon SPECIES_TIRTOUGA, 20
        goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveFossilParty
        goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveFossilPC
        goto Common_EventScript_NoMoreRoomForPokemon
        end


RustboroCity_DevonCorp_2F_EventScript_TyruntReady::
	bufferspeciesname STR_VAR_2, SPECIES_TYRUNT
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
        bufferspeciesname STR_VAR_1, SPECIES_TYRUNT
        setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_TYRUNT
        givemon SPECIES_TYRUNT, 20
        goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveFossilParty
        goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveFossilPC
        goto Common_EventScript_NoMoreRoomForPokemon
        end

RustboroCity_DevonCorp_2F_EventScript_AmauraReady::
	bufferspeciesname STR_VAR_2, SPECIES_AMAURA
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
        bufferspeciesname STR_VAR_1, SPECIES_AMAURA
        setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_AMAURA
        givemon SPECIES_AMAURA, 20
        goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveFossilParty
        goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveFossilPC
        goto Common_EventScript_NoMoreRoomForPokemon
        end

RustboroCity_DevonCorp_2F_EventScript_AerodactylReady::
	bufferspeciesname STR_VAR_2, SPECIES_AERODACTYL
	msgbox RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife, MSGBOX_DEFAULT
        bufferspeciesname STR_VAR_1, SPECIES_AERODACTYL
        setvar VAR_TEMP_TRANSFERRED_SPECIES, SPECIES_AERODACTYL
        givemon SPECIES_AERODACTYL, 20
        goto_if_eq VAR_RESULT, MON_GIVEN_TO_PARTY, RustboroCity_DevonCorp_2F_EventScript_ReceiveFossilParty
        goto_if_eq VAR_RESULT, MON_GIVEN_TO_PC, RustboroCity_DevonCorp_2F_EventScript_ReceiveFossilPC
        goto Common_EventScript_NoMoreRoomForPokemon
        end


RustboroCity_DevonCorp_2F_EventScript_ReceiveFossilParty::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_FinishReceiving
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceiving
	end

RustboroCity_DevonCorp_2F_EventScript_ReceiveFossilPC::
	call RustboroCity_DevonCorp_2F_EventScript_ReceivedFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	goto_if_eq VAR_RESULT, NO, RustboroCity_DevonCorp_2F_EventScript_TransferToPC
	call Common_EventScript_NameReceivedBoxMon
	goto RustboroCity_DevonCorp_2F_EventScript_TransferToPC
	end

RustboroCity_DevonCorp_2F_EventScript_TransferToPC::
	call Common_EventScript_TransferredToPC
	goto RustboroCity_DevonCorp_2F_EventScript_FinishReceiving
	end

RustboroCity_DevonCorp_2F_EventScript_ReceivedFanfare::
	playfanfare MUS_OBTAIN_ITEM
	message RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher
	waitmessage
	waitfanfare
	return

RustboroCity_DevonCorp_2F_EventScript_FinishReceiving::
	setvar VAR_FOSSIL_RESURRECTION_STATE, 0
	setflag FLAG_RECEIVED_REVIVED_FOSSIL_MON
	release
	end

RustboroCity_DevonCorp_2F_EventScript_ChooseFossil::
	buffernumberstring STR_VAR_2, VAR_TEMP_2 
	message RustboroCity_DevonCorp_2F_Text_TwoFossilsPickOne
	waitmessage
	setvar VAR_TEMP_2, 0 @ must be done, so that var temp 2 keeps in line with the state of the dynamic multichoice
        dynmultistack 0, 0, FALSE, 6, FALSE, VAR_0x800A, DYN_MULTICHOICE_CB_SHOW_ITEM @ may as well
	copyvar VAR_0x8008, VAR_RESULT
        goto_if_eq VAR_0x8008, MULTI_B_PRESSED, RustboroCity_DevonCorp_2F_EventScript_CancelFossilSelect
        goto RustboroCity_DevonCorp_2F_EventScript_GiveFossil
	end

RustboroCity_DevonCorp_2F_EventScript_CancelFossilSelect::
	release
	end

RustboroCity_DevonCorp_2F_EventScript_MatchCallScientist::
	lock
	faceplayer
	call_if_eq VAR_FOSSIL_RESURRECTION_STATE, 1, RustboroCity_DevonCorp_2F_EventScript_SetFossilReady
	goto_if_ge VAR_RUSTBORO_CITY_STATE, 6, RustboroCity_DevonCorp_2F_EventScript_WorkOnNext
	msgbox RustboroCity_DevonCorp_2F_Text_DevelopNewPokenavFeature, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_EventScript_WorkOnNext::
	msgbox RustboroCity_DevonCorp_2F_Text_WhatToWorkOnNext, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_2F_Text_DeviceForTalkingToPokemon:
	.string "We're developing a device for talking\n"
	.string "with POKéMON.\p"
	.string "But we haven't had much success…$"

RustboroCity_DevonCorp_2F_Text_DevelopingNewBalls:
	.string "I'm developing new kinds of\n"
	.string "POKé BALLS…\p"
	.string "But I haven't made much headway…$"

RustboroCity_DevonCorp_2F_Text_WeFinallyMadeNewBalls:
	.string "We finally made new kinds of\n"
	.string "POKé BALLS!\p"
	.string "The REPEAT BALL makes it easier to\n"
	.string "catch POKéMON you've caught before.\p"
	.string "The TIMER BALL gets better at catching\n"
	.string "POKéMON the longer a battle runs.\p"
	.string "Both are proudly developed by\n"
	.string "the DEVON CORPORATION.\p"
	.string "Please give them a try!$"

RustboroCity_DevonCorp_2F_Text_IMadePokenav:
	.string "I made the POKéNAV!\p"
	.string "As an engineer, I feel blessed to have\n"
	.string "made something so great!$"

RustboroCity_DevonCorp_2F_Text_WowThatsAPokenav:
	.string "Oh, wow!\n"
	.string "That's a POKéNAV!\p"
	.string "It came about as a result of our\n"
	.string "PRESIDENT's desire to learn about\l"
	.string "the feelings of POKéMON.\p"
	.string "Would you like me to describe its\n"
	.string "features in detail?\p"
	.string "No, no. I think you'll find out just by\n"
	.string "trying the POKéNAV out.$"

RustboroCity_DevonCorp_2F_Text_DeviceToVisualizePokemonDreams:
	.string "I'm trying to develop a device that\n"
	.string "visually reproduces the dreams of\l"
	.string "POKéMON…\p"
	.string "But it's not going well.$"

RustboroCity_DevonCorp_2F_Text_DevelopDeviceToResurrectFossils:
	.string "I've been trying to develop a device\n"
	.string "that resurrects POKéMON from fossils…\p"
	.string "And, it's working!$"

RustboroCity_DevonCorp_2F_Text_WantToBringFossilBackToLife:
	.string "Wait! That thing you have there…\n"
	.string "Is that a POKéMON fossil?\p"
	.string "Would you like to bring that POKéMON\n"
	.string "back to life?\p"
	.string "I can with my newly developed\n"
	.string "FOSSIL REGENERATOR.$"

RustboroCity_DevonCorp_2F_Text_OhIsThatSo:
	.string "Oh, is that so?\p"
	.string "DEVON's technological expertise\n"
	.string "is outstanding, I tell you.$"

RustboroCity_DevonCorp_2F_Text_TwoFossilsPickOne:
	.string "Oh, now that's a surprise!\n"
	.string "You have not one, but {STR_VAR_2}, fossils?\p"
	.string "Unfortunately, my machine can only\n"
	.string "regenerate one POKéMON at a time.\p"
	.string "Would you like to pick one of your\n"
	.string "fossils for regeneration?$"

RustboroCity_DevonCorp_2F_Text_HandedFossilToResearcher:
	.string "Excellent!\n"
	.string "Let's do this right away.\p"
	.string "{PLAYER} handed the {STR_VAR_1} to\n"
	.string "the DEVON RESEARCHER.$"

RustboroCity_DevonCorp_2F_Text_FossilRegeneratorTakesTime:
	.string "The FOSSIL REGENERATOR, which I made,\n"
	.string "is incredible.\p"
	.string "But it has one drawback--it takes\n"
	.string "a long time to work.\p"
	.string "So, uh… How about you go for a stroll\n"
	.string "and look around for a while?$"

RustboroCity_DevonCorp_2F_Text_FossilizedMonBroughtBackToLife:
	.string "Thanks for waiting!\p"
	.string "Your fossilized POKéMON has been\n"
	.string "brought back to life!\p"
	.string "The fossil was an ancient POKéMON.\n"
	.string "{STR_VAR_2}, it was!$"

RustboroCity_DevonCorp_2F_Text_ReceivedMonFromResearcher:
	.string "{PLAYER} received {STR_VAR_2} from\n"
	.string "the DEVON RESEARCHER.$"

@ Unused
@ RustboroCity_DevonCorp_2F_Text_TooManyPokemon:
	@ .string "Uh-oh, you've got too many POKéMON.\n"
	@ .string "You have no room for this one.$"

RustboroCity_DevonCorp_2F_Text_DevelopNewPokenavFeature:
	.string "I'm trying to develop a new feature\n"
	.string "for the POKéNAV…\p"
	.string "But it's not going well.$"

RustboroCity_DevonCorp_2F_Text_WhatToWorkOnNext:
	.string "Well, now what shall I work on\n"
	.string "developing next?\p"
	.string "Our company allows us to make our\n"
	.string "inspirations into reality.\p"
	.string "One couldn't ask for a better\n"
	.string "environment as an engineer.$"

RustboroCity_DevonCorp_2F_Text_DomeFossil:
	.string "Dome Fossil$"

RustboroCity_DevonCorp_2F_Text_HelixFossil:
	.string "Helix Fossil$"

RustboroCity_DevonCorp_2F_Text_ClawFossil:
	.string "Claw Fossil$"

RustboroCity_DevonCorp_2F_Text_RootFossil:
	.string "Root Fossil$"

RustboroCity_DevonCorp_2F_Text_ArmorFossil:
	.string "Armor Fossil$"

RustboroCity_DevonCorp_2F_Text_SkullFossil:
	.string "Skull Fossil$"

RustboroCity_DevonCorp_2F_Text_PlumeFossil:
	.string "Plume Fossil$"

RustboroCity_DevonCorp_2F_Text_CoverFossil:
	.string "Cover Fossil$"

RustboroCity_DevonCorp_2F_Text_JawFossil:
	.string "Jaw Fossil$"

RustboroCity_DevonCorp_2F_Text_SailFossil:
	.string "Sail Fossil$"

RustboroCity_DevonCorp_2F_Text_OldAmber:
	.string "Old Amber$"
