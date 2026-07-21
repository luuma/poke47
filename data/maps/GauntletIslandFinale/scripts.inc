GauntletIslandFinale_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, GauntletIslandOnTransition
	map_script MAP_SCRIPT_ON_RESUME, Route113_OnResume @ 	setstepcallback STEP_CB_ASH ; end
	map_script MAP_SCRIPT_ON_RETURN_TO_FIELD, GauntletIslandOnResume @ 	setstepcallback STEP_CB_ASH ; end
	.byte 0
