InteractWithOverworldWildEncounter::
    lock
    overworldwildencounterapproach
    applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark
    facetogether
    playmoncry VAR_0x8004, CRY_MODE_DOUBLES
    waitmoncry
    tryoverworldwildencounter
    waitstate
    end

OWEAutoBattleOverworldWildEncounter::
    lockall
    callnative ScriptFaceEachOtherFollowerOWE  
    applymovement VAR_LAST_TALKED, Common_Movement_ExclamationMark
    playmoncry VAR_0x8004, CRY_MODE_DOUBLES
    waitmoncry
    removeobject VAR_LAST_TALKED
    bufferlivemonnickname STR_VAR_1
    bufferspeciesname STR_VAR_2, VAR_0x8004
    msgbox InteractWithOverworldWildEncounter_Text_Buffer1DefeatedABuffer2, MSGBOX_DEFAULT @AUTOBATTLE
    releaseall
    end

InteractWithOverworldWildEncounter_Text_Buffer1DefeatedABuffer2:
	.string "{STR_VAR_1} fended off a {STR_VAR_2}!$"


OWEAutoBattling::
    lockall
    faceplayer
    bufferlivemonnickname STR_VAR_1
    playfirstmoncry
    msgbox gText_FollowerAutoQuestion2, MSGBOX_YESNO
    goto_if_eq VAR_RESULT, NO, EventScript_OWEAutoBattling
    clearflag FLAG_TEMP_1F
    callnative RemoveAutoBattlingPokemon
    @ removeobject VAR_LAST_TALKED
    updatefollowingmon
EventScript_OWEAutoBattling::
    releaseall
    end

gText_FollowerAutoQuestion2::
	.string "Bring {STR_VAR_1} to follow you?$"
