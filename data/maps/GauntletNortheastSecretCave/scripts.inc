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

