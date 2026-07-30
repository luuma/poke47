GauntletNortheastSecretCave_MapScripts::
	.byte 0

GauntletNortheastSecretCave_TheAltar::
    lockall
    hidefollower 0
    special DoSealedChamberShakingEffect_Short
    goto_if_set FLAG_TEMP_1, gauntlet_ivreducer_againhowcruel
    msgbox GauntletIsland_TxtCreepypastaAss
    delay 30
    msgbox GauntletIsland_TxtCreepypastaAss2
    delay 30
    msgbox GauntletIsland_TxtCreepypastaAss3
    delay 30
    msgbox GauntletIsland_TxtCreepypastaAss4

gauntlet_ivreducer_Declined::
    special ChoosePartyMon
    goto_if_ge VAR_0x8004, PARTY_SIZE, gauntlet_ivreducer_Declined
    message GauntletIsland_Txt0IVHandler
    waitmessage
gauntlet_ivreducer_Declined3::
    dynmultipush gText_HP4, STAT_HP
    dynmultipush gText_Attack3, STAT_ATK
    dynmultipush gText_Defense3, STAT_DEF
    dynmultipush gText_SpAtk4, STAT_SPATK
    dynmultipush gText_SpDef4, STAT_SPDEF
    dynmultipush gText_Speed2, STAT_SPEED
    dynmultistack 0, 0, FALSE, 6 FALSE, 0, NULL
    goto_if_gt VAR_RESULT, STAT_SPEED, gauntlet_ivreducer_Declined2// you aren't getting out of this one buddy
    callnative GauntletIsland_AltarDamning
    special DoSealedChamberShakingEffect_Short
    delay 30
    msgbox GauntletIsland_Txt0IVHandlermeanie
    setflag FLAG_TEMP_1
    releaseall
    end

gauntlet_ivreducer_Declined2:
    message GauntletIsland_cANTsTOP
    waitmessage
    goto gauntlet_ivreducer_Declined3
    end

gauntlet_ivreducer_againhowcruel:
    special ChoosePartyMon
    goto_if_ge VAR_0x8004, PARTY_SIZE, gauntlet_ivreducer_againhowcruel
    message GauntletIsland_Txt0IVHandlerAGAIN
    waitmessage
    goto gauntlet_ivreducer_Declined3
    end

GauntletIsland_TxtCreepypastaAss:
	.string "There is a scratching sound in\n"
	.string "the back of your neck.\p"
	.string "The ALTAR reads\n"
	.string "“IN DEVOTION TO {PLAYER}.”$"

GauntletIsland_TxtCreepypastaAss2:
	.string "The ALTAR reads\n"
	.string "“WHO BOILED THE QUIET LAKE\l"
	.string "ALIVE, LEAVING IT DEAD.”$"

GauntletIsland_TxtCreepypastaAss3:
	.string "The ALTAR reads\n"
	.string "“A PERMANENT CONSEQUENCE\l"
	.string "OF INSATIABLE CURIOSITY.”\p"
	.string "The ALTAR reads\n"
	.string "“SOUND FAMILIAR?”$"

GauntletIsland_TxtCreepypastaAss4:
	.string "The ALTAR reads\n"
	.string "“NO BAD DEED GOES UNREWARDED.”$"

GauntletIsland_Txt0IVHandler:
	.string "The ALTAR reads\n"
	.string "“SET WHICH IV TO 0?”$"

GauntletIsland_cANTsTOP:
	.string "You can't stop reading.$"

GauntletIsland_Txt0IVHandlermeanie:
	.string "The ALTAR was always blank.$"

GauntletIsland_Txt0IVHandlerAGAIN:
	.string "The ALTAR reads\n"
	.string "“ANOTHER? HOW CRUEL.”$"




slateport_evbottler::
    lockall
    faceplayer
    msgbox EvBottler_WannaBottle MSGBOX_YESNO
    goto_if_eq VAR_RESULT, TRUE, slateport_evbottlergo
    message EVBottler_TxtAwBeans
    releaseall
    end

slateport_evbottlergo::
    special ChoosePartyMon
    goto_if_ge VAR_0x8004, PARTY_SIZE, evbottler_Declined
slateport_evbottler_return::
    message EVBottler_Txt0EVHandler
    waitmessage
    dynmultipush gText_HP4, STAT_HP
    dynmultipush gText_Attack3, STAT_ATK
    dynmultipush gText_Defense3, STAT_DEF
    dynmultipush gText_SpAtk4, STAT_SPATK
    dynmultipush gText_SpDef4, STAT_SPDEF
    dynmultipush gText_Speed2, STAT_SPEED
    dynmultistack 0, 0, FALSE, 6 FALSE, 0, NULL
    goto_if_gt VAR_RESULT, STAT_SPDEF, evbottler_Declined2
    callnative ScrCmd_EVBottler
    goto_if_eq VAR_0x8006, 0, evbottler_none
    checkitemspace VAR_0x8005, VAR_0x8006
    goto_if_eq VAR_RESULT, FALSE, evbottler_notenoughitemspace
    bufferitemname STR_VAR_1, VAR_0x8005
    msgbox EvBottler_BottleEVs
    applymovement VAR_LAST_TALKED, EVbottlerspin
    msgbox EvBottler_BottleEVsYell
    waitmovement
    faceplayer
    callnative ScrCmd_ZeroEvsOfPartyIndex
    giveitem VAR_0x8005, VAR_0x8006
    message EvBottler_Bottlecomplete
    releaseall
    end

evbottler_none::
    msgbox EvBottler_BottleNothing
    releaseall
    end

evbottler_notenoughitemspace::
    msgbox EvBottler_NotEnoughItemSpace
    releaseall
    end

evbottler_Declined::
    msgbox EvBottler_WantChoosePartyMember MSGBOX_YESNO
    goto_if_eq VAR_RESULT, TRUE, slateport_evbottlergo
    message EVBottler_TxtAwBeans
    releaseall
    end

evbottler_Declined2::
    msgbox EvBottler_WantChooseStat MSGBOX_YESNO
    goto_if_eq VAR_RESULT, TRUE, slateport_evbottler_return
    message EVBottler_TxtAwBeans
    releaseall
    end

EvBottler_Bottlecomplete:
	.string "Yeehaw! You BOTTLE believe it!$"

EvBottler_WannaBottle:
	.string "Yeehaw! I am the EV BOTTLER.\p"
	.string "I can clear the messy EVs off of your\n"
	.string "partners and bottle them up. Cowabunga!\p"
	.string "I'll set their EVs to 0, and make\n"
	.string "1 Vitamin for every 15 EVs cleaned!\p"
	.string "Let me loose?? I'm BOTTLE-READY!$"

EvBottler_NotEnoughItemSpace:
	.string "“Too bad! The bag is full.”\n"
	.string "That's what I'd say if I was a\l"
	.string "message right now.\p"
	.string "Make space for my items! Zzzap!$"

EVBottler_Txt0EVHandler:
	.string "Set which EV to 0?\n"
	.string "15 cleared EVs make 1 Vitamin!$"

EvBottler_BottleEVs:
	.string "Cover those ears, kid, I have to yell\n"
	.string "or else this will NOT work.$"
EvBottler_BottleEVsYell:
	.string "EV BOTTLER TECHNIQUE:\n"
	.string "BRRRRRRONCOOOOO TWO THOUSANNNND\l"
	.string "Ultimate {STR_VAR_1} H E A R T !$"

EVbottlerspin:@ spin the bottler
        walk_in_place_slow_down
        walk_in_place_slow_left
        walk_in_place_slow_up
        walk_in_place_slow_right
	walk_in_place_down
	walk_in_place_down
	walk_in_place_left
	walk_in_place_left
	walk_in_place_up
	walk_in_place_up
	walk_in_place_right
	walk_in_place_right
	walk_in_place_down
	walk_in_place_left
	walk_in_place_up
	walk_in_place_right
	walk_in_place_down
	step_end

EvBottler_WantChoosePartyMember:
	.string "Guaaah?? Did you want to choose\n"
	.string "a party member?$"

EvBottler_WantChooseStat:
	.string "Aiyiyi! Don't you want to reduce\n"
	.string "an EV to 0?$"


EvBottler_BottleNothing:
	.string "Hunh? There's not enough EV juice\n"
	.string "here to be bottled!\p"
EVBottler_TxtAwBeans:
	.string "Geah! Aw, beans!$"


