GauntletSoutheastCave_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, GauntletSoutheastCave_OnLoad
	.byte 0

GauntletSoutheastCave_OnLoad:
	call_if_set FLAG_GAUNTLET_0FBOULDER3, GauntletSoutheastCave_EventScript_setmaptile
        call_if_set FLAG_GAUNTLET_0FBOULDER1, GauntletSoutheastCave_EventScript_setmaptilelAVA1
	end

GauntletSoutheastCave_EventScript_setmaptile::
	setmetatile 34, 8, 0x279, 1
	setmetatile 34, 9, 0x2A4, 0
	return

GauntletSoutheastCave_EventScript_setmaptilelAVA1::
        goto_if_set FLAG_GAUNTLET_0FBOULDER2, GauntletSoutheastCave_EventScript_setmaptilelAVA
        return

GauntletSoutheastCave_EventScript_setmaptilelAVA::
	setmetatile 20, 3, 0x364, 1
	return
