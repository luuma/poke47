shaymin_MapScripts::
	.byte 0

shaymin_shaymin::
	lock
        faceplayer
	waitse
	playmoncry SPECIES_SHAYMIN, CRY_MODE_NORMAL
	waitmoncry
	msgbox shaymin_offerstofight, MSGBOX_YESNO
        goto_if_ne VAR_RESULT, YES, shayminreleaseallend
	setwildbattle SPECIES_SHAYMIN, 4
	waitse
	playmoncry SPECIES_SHAYMIN, CRY_MODE_ENCOUNTER
	waitmoncry
	delay 40
	special BattleSetup_StartLegendaryBattle
	specialvar VAR_RESULT, GetBattleOutcome
	goto_if_eq VAR_RESULT, B_OUTCOME_WON, shaymin_EventScript_ShayminGone
	goto_if_eq VAR_RESULT, B_OUTCOME_RAN, shaymin_EventScript_ShayminGone
	goto_if_eq VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED, shaymin_EventScript_ShayminGone
	goto shaymin_EventScript_CaughtShaymin
shayminreleaseallend::
	release
	end

shaymin_EventScript_ShayminGone::
        setflag FLAG_SHAYMIN_ENCOUNTERED
	goto Common_EventScript_RemoveStaticPokemon
	end


shaymin_EventScript_CaughtShaymin::
        removeobject VAR_LAST_TALKED
	msgbox shayminseemscontent, MSGBOX_DEFAULT
        setflag FLAG_SHAYMIN_CAUGHT
        setflag FLAG_SHAYMIN_ENCOUNTERED
	releaseall
	end

shaymin_offerstofight:
	.string "Kyuuu uuhn…\p"
	.string "… … … … … … … …\n"
	.string "… … … … … … … …\p"
	.string "The little POKéMON seems at peace,\n"
 	.string "but offers to grace you with a BATTLE.\p"
 	.string "Do you accept?$"

shayminseemscontent:
        .string "The little POKéMON seems overjoyed\n"
 	.string "to have made a new friend!$"
