GauntletIslandSouthwest_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, GauntletIslandOnTransition
	map_script MAP_SCRIPT_ON_RESUME, Route113_OnResume @ 	setstepcallback STEP_CB_ASH ; end
	map_script MAP_SCRIPT_ON_RETURN_TO_FIELD, GauntletIslandOnResume @ 	setstepcallback STEP_CB_ASH ; end
	.byte 0

GauntletIslandOnResume::
        goto_if_unset GAUNTLET_QUITTER_DETECTED, GauntletIslandOnResume_end@ STOP FUCKING SENDING THE PLAYER HOME
        clearflag GAUNTLET_QUITTER_DETECTED
        setvar B_VAR_WILD_AI_FLAGS, 0
GauntletIsland_EventScript_RetireGauntletChallenge::
        setvar VAR_0x8004, 1234
        delay 2
	warp MAP_ROUTE_100, 8, 11
	waitstate
	end

GauntletIslandOnResume_end:
	end

