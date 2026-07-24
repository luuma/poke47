GauntletIslandNortheast_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, GauntletIslandNortheast_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, Route113_OnResume @ 	setstepcallback STEP_CB_ASH ; end
	map_script MAP_SCRIPT_ON_RETURN_TO_FIELD, GauntletIslandOnResume @ 	setstepcallback STEP_CB_ASH ; end
	.byte 0

GauntletIslandNortheast_OnTransition::
	call GauntletIsland_EventScript_SetAbnormalWeather
	goto_if_unset FLAG_GAUNTLET_1FBOULDER1, GauntletIslandNortheast_ice
	goto_if_unset FLAG_GAUNTLET_1FBOULDER2, GauntletIslandNortheast_ice
	goto_if_unset FLAG_GAUNTLET_0FBOULDER2, GauntletIslandNortheast_ice
	goto_if_unset FLAG_GAUNTLET_0FBOULDER2, GauntletIslandNortheast_ice
	goto GauntletIslandNortheast_fire

GauntletIslandNortheast_ice::
	setmaplayoutindex LAYOUT_AEGAUNTLET7
	end

GauntletIslandNortheast_fire::
	setmaplayoutindex LAYOUT_AEGAUNTLET7_2
	end

GauntletIsland_TheLake::
    lockall
    special DoSealedChamberShakingEffect_Short
    msgbox GauntletIsland_TxtDanielMullins 
    addvar VAR_GAUNTLET_9, 1
    releaseall
    end

GauntletIsland_TxtDanielMullins::
	.string "Deep under the ice, you hear\n"
	.string "something writhe.$"

GauntletIsland_AltarHP::
    lockall
    msgbox GauntletIsland_AltarHPInscription 
    goto_if_set FLAG_GAUNTLET_HP_ALTAR, GauntletIsland_AltarHPjUMP
    msgbox GauntletIsland_AltarHPTouch MSGBOX_YESNO
    goto_if_eq VAR_RESULT, FALSE, GauntletIsland_AltarReleaseEnd
    closemessage
    setvar B_VAR_WILD_AI_FLAGS 2@ 1 == CONSERVATIVE, 2 == RISKY,  3=BOSS, 5 = , other =normal
    setflag GAUNTLET_QUITTER_DETECTED
    forcesave
    closemessage
    call Common_EventScript_OutOfCenterPartyHeal
    clearflag GAUNTLET_QUITTER_DETECTED
    callnative ScrCmd_SetGauntletBossBattle
    .byte 0
    playmoncry VAR_RESULT, CRY_MODE_ENCOUNTER
    delay 40
    waitmoncry
    dowildbattle
    specialvar VAR_RESULT, GetBattleOutcome
    goto_if_eq VAR_RESULT, B_OUTCOME_LOST, GauntletIsland_AltarLoss
    goto_if_eq VAR_RESULT, B_OUTCOME_DREW, GauntletIsland_AltarLoss
    goto_if_eq VAR_RESULT, B_OUTCOME_RAN, GauntletIsland_AltarLoss
    goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, GauntletIsland_AltarLoss
    goto_if_eq VAR_RESULT, B_OUTCOME_FORFEITED, GauntletIsland_AltarLoss
    call Common_EventScript_OutOfCenterPartyHeal
    setvar B_VAR_WILD_AI_FLAGS, 0
    setvar VAR_0x8008, STAT_HP
    call GauntletIsland_AltarBlessing
    setflag FLAG_GAUNTLET_HP_ALTAR
    addvar VAR_GAUNTLET_9, 1
    msgbox GauntletIsland_AltarHPVictory
GauntletIsland_AltarHPjUMP::
    goto_if_gt VAR_GAUNTLET_1, 0, GauntletIsland_AltarQuiet
    goto_if_eq VAR_GAUNTLET_1, 0, GauntletIsland_Boon1
    releaseall
    end


GauntletIsland_AltarHPInscription:
	.string "An engraving on the ALTAR reads\n"
	.string "“IN DEVOTION TO THE ELDER WYRM.”$"


GauntletIsland_AltarHPTouch:
	.string "It trembles with draconic vitality.\p"
	.string "Touch the ALTAR?$"

GauntletIsland_AltarHPVictory:
	.string "A burning, steady light heals you.\n"
	.string "Your party's HP stat potential\l"
	.string "is now maximised.$"

GauntletIsland_Altaratk::
    lockall
    msgbox GauntletIsland_AltaratkInscription 
    goto_if_set FLAG_GAUNTLET_ATK_ALTAR, GauntletIsland_AltarATKjUMP
    msgbox GauntletIsland_AltaratkTouch MSGBOX_YESNO
    goto_if_eq VAR_RESULT, FALSE, GauntletIsland_AltarReleaseEnd
    closemessage
    setvar B_VAR_WILD_AI_FLAGS 1@ 1 == CONSERVATIVE, 2 == RISKY,  3=BOSS, other =normal
    setflag GAUNTLET_QUITTER_DETECTED
    forcesave
    closemessage
    call Common_EventScript_OutOfCenterPartyHeal
    clearflag GAUNTLET_QUITTER_DETECTED
    callnative ScrCmd_SetGauntletBossBattle
    .byte 3
    playmoncry VAR_RESULT, CRY_MODE_ENCOUNTER
    delay 40
    waitmoncry
    dowildbattle
    specialvar VAR_RESULT, GetBattleOutcome
    goto_if_eq VAR_RESULT, B_OUTCOME_LOST, GauntletIsland_AltarLoss
    goto_if_eq VAR_RESULT, B_OUTCOME_DREW, GauntletIsland_AltarLoss
    goto_if_eq VAR_RESULT, B_OUTCOME_RAN, GauntletIsland_AltarLoss
    @goto_if_eq VAR_RESULT, B_OUTCOME_FLED, GauntletIsland_AltarLoss NOT POSSIBLE
    goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, GauntletIsland_AltarLoss
    goto_if_eq VAR_RESULT, B_OUTCOME_FORFEITED, GauntletIsland_AltarLoss
    call Common_EventScript_OutOfCenterPartyHeal
    setvar B_VAR_WILD_AI_FLAGS, 0
    setvar VAR_0x8008, STAT_DEF
    call GauntletIsland_AltarBlessing
    setflag FLAG_GAUNTLET_ATK_ALTAR
    msgbox GauntletIsland_AltaratkVictory
GauntletIsland_AltarATKjUMP::
    goto_if_gt VAR_GAUNTLET_3, 0, GauntletIsland_AltarQuiet
    goto_if_eq VAR_GAUNTLET_3, 0, GauntletIsland_Boon3
    releaseall
    end


GauntletIsland_AltaratkInscription:
	.string "An engraving on the ALTAR reads\n"
	.string "“IN DEVOTION TO THE MOUNTAIN.”$"


GauntletIsland_AltaratkTouch:
	.string "It trembles with titanic strength.\p"
	.string "Touch the ALTAR?$"

GauntletIsland_AltaratkVictory:
	.string "A warms, steady light heals you.\n"
	.string "Your party's DEFENSE stat potential\l"
	.string "is now maximised.$"


GauntletIsland_AltarSpatk::
    lockall
    msgbox GauntletIsland_AltarSpatkInscription 
    goto_if_set FLAG_GAUNTLET_SPATK_ALTAR, GauntletIsland_AltarSATKjUMP
    msgbox GauntletIsland_AltarSpatkTouch MSGBOX_YESNO
    goto_if_eq VAR_RESULT, FALSE, GauntletIsland_AltarReleaseEnd
    closemessage
    setvar B_VAR_WILD_AI_FLAGS 1@ 1 == CONSERVATIVE, 2 == RISKY,  3=BOSS, other =normal
    setflag GAUNTLET_QUITTER_DETECTED
    forcesave
    closemessage
    call Common_EventScript_OutOfCenterPartyHeal
    clearflag GAUNTLET_QUITTER_DETECTED
    callnative ScrCmd_SetGauntletBossBattle
    .byte 6
    playmoncry VAR_RESULT, CRY_MODE_ENCOUNTER
    delay 40
    waitmoncry
    totemboost_defsdef B_POSITION_OPPONENT_LEFT @ I cant tell if this even fucking works.
    dowildbattle
    specialvar VAR_RESULT, GetBattleOutcome
    goto_if_eq VAR_RESULT, B_OUTCOME_LOST, GauntletIsland_AltarLoss
    goto_if_eq VAR_RESULT, B_OUTCOME_DREW, GauntletIsland_AltarLoss
    goto_if_eq VAR_RESULT, B_OUTCOME_RAN, GauntletIsland_AltarLoss
    goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, GauntletIsland_AltarLoss
    goto_if_eq VAR_RESULT, B_OUTCOME_FORFEITED, GauntletIsland_AltarLoss
    call Common_EventScript_OutOfCenterPartyHeal
    setvar B_VAR_WILD_AI_FLAGS, 0
    setvar VAR_0x8008, STAT_SPDEF
    call GauntletIsland_AltarBlessing
    @setvar VAR_0x8008, STAT_SPDEF
    @call GauntletIsland_AltarBlessing
    setflag FLAG_GAUNTLET_SPATK_ALTAR
    msgbox GauntletIsland_AltarSpatkVictory
GauntletIsland_AltarSATKjUMP::
    goto_if_gt VAR_GAUNTLET_5, 0, GauntletIsland_AltarQuiet
    goto_if_eq VAR_GAUNTLET_5, 0, GauntletIsland_Boon5
    releaseall
    end


GauntletIsland_AltarSpatkInscription:
	.string "An engraving on the ALTAR reads\n"
	.string "“IN DEVOTION TO THE DEPTHS.”$"


GauntletIsland_AltarSpatkTouch:
	.string "It wavers like a calm tide.\p"
	.string "Touch the ALTAR?$"

GauntletIsland_AltarSpatkVictory:
	.string "A cool, undulating glow heals you.\n"
	.string "Your party's SP.DEF stat potential\l"
	.string "is now maximised.$"

GauntletIsland_AltarSpeed::
    lockall
    msgbox GauntletIsland_AltarSpeedInscription 
    goto_if_set FLAG_GAUNTLET_SPEED_ALTAR, GauntletIsland_AltarSpeedjUMP
    msgbox GauntletIsland_AltarSpeedTouch MSGBOX_YESNO
    goto_if_eq VAR_RESULT, FALSE, GauntletIsland_AltarReleaseEnd
    closemessage
    setvar B_VAR_WILD_AI_FLAGS 3 @ 1 == CONSERVATIVE, 2 == RISKY,  <3=BOSS
    setflag GAUNTLET_QUITTER_DETECTED
    forcesave
    closemessage
    call Common_EventScript_OutOfCenterPartyHeal
    clearflag GAUNTLET_QUITTER_DETECTED
    callnative ScrCmd_SetGauntletBossBattle
    .byte 9
    playmoncry VAR_RESULT, CRY_MODE_ENCOUNTER
    delay 40
    waitmoncry
    totemboost_defsdefspe B_POSITION_OPPONENT_LEFT
    dowildbattle
    specialvar VAR_RESULT, GetBattleOutcome
    goto_if_eq VAR_RESULT, B_OUTCOME_LOST, GauntletIsland_AltarLoss
    goto_if_eq VAR_RESULT, B_OUTCOME_DREW, GauntletIsland_AltarLoss
    goto_if_eq VAR_RESULT, B_OUTCOME_RAN, GauntletIsland_AltarLoss
    goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, GauntletIsland_AltarLoss
    goto_if_eq VAR_RESULT, B_OUTCOME_FORFEITED, GauntletIsland_AltarLoss
    call Common_EventScript_OutOfCenterPartyHeal
    setvar B_VAR_WILD_AI_FLAGS, 0
    setvar VAR_0x8008, STAT_HP
    call GauntletIsland_AltarBlessing
    setflag FLAG_GAUNTLET_SPEED_ALTAR
    msgbox GauntletIsland_AltarSpeedVictory
GauntletIsland_AltarSpeedjUMP::
    goto_if_gt VAR_GAUNTLET_7, 0, GauntletIsland_AltarQuiet
    goto_if_eq VAR_GAUNTLET_7, 0, GauntletIsland_Boon7
    releaseall
    end


GauntletIsland_AltarSpeedInscription:
	.string "An engraving on the ALTAR reads\n"
	.string "“IN DEVOTION TO THE HEAVENS.”$"


GauntletIsland_AltarSpeedTouch:
	.string "Its sanctity is awe-inspiring.\p"
	.string "Touch the ALTAR?$"

GauntletIsland_AltarSpeedVictory:
	.string "The light of judgment heals you.\n"
	.string "Your party's SPEED stat potential\l"
	.string "is now maximised.$"


GauntletIsland_AltarTWIN::
    lockall
    msgbox GauntletIsland_AltarTWINInscription 
    goto_if_set FLAG_GAUNTLET_BOSS_ALTAR, GauntletIsland_AltarBossjUMP
    special DoSealedChamberShakingEffect_Short
    msgbox GauntletIsland_AltarTWINInscription2
    setvar B_VAR_WILD_AI_FLAGS 3@ 1 == CONSERVATIVE, 2 == RISKY,  3=BOSS, 5 = , other =normal
    setflag GAUNTLET_QUITTER_DETECTED
    forcesave
    closemessage
    call Common_EventScript_OutOfCenterPartyHeal
    clearflag GAUNTLET_QUITTER_DETECTED
    msgbox GauntletIsland_AltarTWINInscription4
    callnative ScrCmd_SetGauntletPenultimateBossBattle
    playmoncry VAR_RESULT, CRY_MODE_ENCOUNTER
    delay 40
    waitmoncry
    totemboost_defsdef B_POSITION_OPPONENT_LEFT 
    callnative dolegendarybattleincdouble
    waitstate @ ugh.
    specialvar VAR_RESULT, GetBattleOutcome
    goto_if_eq VAR_RESULT, B_OUTCOME_LOST, GauntletIsland_AltarLoss
    goto_if_eq VAR_RESULT, B_OUTCOME_DREW, GauntletIsland_AltarLoss
    goto_if_eq VAR_RESULT, B_OUTCOME_RAN, GauntletIsland_AltarLoss
    goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, GauntletIsland_AltarLoss
    goto_if_eq VAR_RESULT, B_OUTCOME_FORFEITED, GauntletIsland_AltarLoss
    special DoSealedChamberShakingEffect_Short
    msgbox GauntletIsland_AltarTWINInscription3
@ Fuck you no healing pick the sap/mountain upgrade idiot
    callnative ScrCmd_SetGauntletFinalBossBattle
    playmoncry VAR_RESULT, CRY_MODE_ENCOUNTER
    delay 40
    waitmoncry
    playmoncry VAR_0x8007, CRY_MODE_ENCOUNTER
    delay 40
    waitmoncry
    @totemboost_defsdef B_POSITION_OPPONENT_LEFT @ HEHEHEE.
    @totemboost_defsdef B_POSITION_OPPONENT_RIGHT @ HOHOOHOHOHOHO.
    callnative dolegendarybattleincdouble
    waitstate
    specialvar VAR_RESULT, GetBattleOutcome
    goto_if_eq VAR_RESULT, B_OUTCOME_LOST, GauntletIsland_AltarLoss
    goto_if_eq VAR_RESULT, B_OUTCOME_DREW, GauntletIsland_AltarLoss
    goto_if_eq VAR_RESULT, B_OUTCOME_RAN, GauntletIsland_AltarLoss
    goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, GauntletIsland_AltarLoss
    goto_if_eq VAR_RESULT, B_OUTCOME_FORFEITED, GauntletIsland_AltarLoss
    call Common_EventScript_OutOfCenterPartyHeal
    setvar B_VAR_WILD_AI_FLAGS, 0
    setvar VAR_0x8008, STAT_DEF
    call GauntletIsland_AltarBlessing
    setvar VAR_0x8008, STAT_SPDEF
    call GauntletIsland_AltarBlessing
    setflag FLAG_GAUNTLET_BOSS_ALTAR
	setvar VAR_GAUNTLET_BOSS2 0
	setvar VAR_GAUNTLET_BOSS3 0
GauntletIsland_AltarBossjUMP::
    msgbox GauntletIsland_AltarBossVictory
    warp MAP_ROUTE_100, 8, 11
    waitstate
    end


GauntletIsland_AltarTWINInscription:
	.string "The engravings on the twin ALTARs\n"
	.string "cannot be read from here.\p"
	.string "But together, their power\n"
 	.string "is overwhelming.$"

GauntletIsland_AltarTWINInscription2:
	.string "There are certain DEITIES\n"
	.string "you showed no devotion to.\p"
	.string "It seems they are angry.$"

GauntletIsland_AltarTWINInscription3:
	.string "It isn't over.$"

GauntletIsland_AltarTWINInscription4:
	.string "A divine force approaches.$"

GauntletIsland_AltarBossVictory:
	.string "Your party's Defense and Sp. Defense\n"
	.string "stat potential is now maximised.\p"
	.string "With a final burst of power,\n"
	.string "{PLAYER} was banished from the ISLAND.$"
