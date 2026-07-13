GauntletSoutheastCave1f_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, GauntSECave_SetHoleWarp
	.byte 0

GauntSECave_SetHoleWarp:
	setstepcallback STEP_CB_CRACKED_FLOOR
	setholewarp MAP_GAUNTLET_SOUTHEAST_CAVE
	end
