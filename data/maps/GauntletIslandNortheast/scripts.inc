GauntletIslandNortheast_MapScripts::
	.byte 0



GauntletIsland_AltarHP::
    lockall
    msgbox GauntletIsland_AltarHPInscription 
    goto_if_set FLAG_GAUNTLET_HP_ALTAR, GauntletIsland_AltarQuiet
    msgbox GauntletIsland_AltarHPTouch MSGBOX_YESNO
    goto_if_eq VAR_RESULT, FALSE, GauntletIsland_AltarReleaseEnd
    closemessage
    setvar B_VAR_WILD_AI_FLAGS 1@ 1 == CONSERVATIVE, 2 == RISKY,  3=BOSS, other =normal
    call Common_EventScript_OutOfCenterPartyHeal
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
    releaseall
    end


GauntletIsland_AltarHPInscription:
	.string "An engraving on the ALTAR reads\n"
	.string "IN DEVOTION TO THE ELDER WYRM.$"


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
    goto_if_set FLAG_GAUNTLET_ATK_ALTAR, GauntletIsland_AltarQuiet
    msgbox GauntletIsland_AltaratkTouch MSGBOX_YESNO
    goto_if_eq VAR_RESULT, FALSE, GauntletIsland_AltarReleaseEnd
    closemessage
    setvar B_VAR_WILD_AI_FLAGS 1@ 1 == CONSERVATIVE, 2 == RISKY,  3=BOSS, other =normal
    call Common_EventScript_OutOfCenterPartyHeal
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
    setvar VAR_0x8008, STAT_ATK
    call GauntletIsland_AltarBlessing
    setflag FLAG_GAUNTLET_ATK_ALTAR
    addvar VAR_GAUNTLET_9, 1
    msgbox GauntletIsland_AltaratkVictory
    releaseall
    end


GauntletIsland_AltaratkInscription:
	.string "An engraving on the ALTAR reads\n"
	.string "IN DEVOTION TO THE MOUNTAIN.$"


GauntletIsland_AltaratkTouch:
	.string "It trembles with titanic strength.\p"
	.string "Touch the ALTAR?$"

GauntletIsland_AltaratkVictory:
	.string "A warms, steady light heals you.\n"
	.string "Your party's ATTACK stat potential\l"
	.string "is now maximised.$"


GauntletIsland_AltarSpatk::
    lockall
    msgbox GauntletIsland_AltarSpatkInscription 
    goto_if_set FLAG_GAUNTLET_SPATK_ALTAR, GauntletIsland_AltarQuiet
    msgbox GauntletIsland_AltarSpatkTouch MSGBOX_YESNO
    goto_if_eq VAR_RESULT, FALSE, GauntletIsland_AltarReleaseEnd
    closemessage
    setvar B_VAR_WILD_AI_FLAGS 1@ 1 == CONSERVATIVE, 2 == RISKY,  3=BOSS, other =normal
    call Common_EventScript_OutOfCenterPartyHeal
    callnative ScrCmd_SetGauntletBossBattle
    .byte 6
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
    setvar VAR_0x8008, STAT_SPATK
    call GauntletIsland_AltarBlessing
    @setvar VAR_0x8008, STAT_SPDEF
    @call GauntletIsland_AltarBlessing
    setflag FLAG_GAUNTLET_SPATK_ALTAR
    msgbox GauntletIsland_AltarSpatkVictory
    releaseall
    end


GauntletIsland_AltarSpatkInscription:
	.string "An engraving on the ALTAR reads\n"
	.string "IN DEVOTION TO THE DEPTHS.$"


GauntletIsland_AltarSpatkTouch:
	.string "It wavers like a calm tide.\p"
	.string "Touch the ALTAR?$"

GauntletIsland_AltarSpatkVictory:
	.string "A cool, undulating glow heals you.\n"
	.string "Your party's SP.ATK stat potential\l"
	.string "is now maximised.$"



