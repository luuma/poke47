GauntletSoutheastCave_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, GauntletSoutheastCave_OnLoad
	.byte 0

GauntletSoutheastCave_OnLoad:
	call_if_set FLAG_GAUNTLET_1FBOULDER3, GauntletSoutheastCave_EventScript_setmaptile
        goto_if_unset FLAG_GAUNTLET_1FBOULDER1, GauntletSoutheastCave_EventScript_jumpskip
        call_if_set FLAG_GAUNTLET_0FBOULDER1, GauntletSoutheastCave_EventScript_setmaptilelAVA1
GauntletSoutheastCave_EventScript_jumpskip::
        goto_if_unset FLAG_GAUNTLET_1FBOULDER2, GauntletSoutheastCave_EventScript_jumpskip2
        call_if_set FLAG_GAUNTLET_0FBOULDER2, GauntletSoutheastCave_EventScript_setmaptilelAVA2
GauntletSoutheastCave_EventScript_jumpskip2::
        end

GauntletSoutheastCave_EventScript_setmaptile::
	setmetatile 34, 8, 0x279, 1
	setmetatile 34, 9, 0x2A4, 0
        setflag FLAG_TEMP_14
	return

GauntletSoutheastCave_EventScript_setmaptilelAVA1::
	setmetatile 13, 16, 0x39a, 0
        removeobject LOCALID_0FBOULDER1
	return

GauntletSoutheastCave_EventScript_setmaptilelAVA2::
	setmetatile 16, 5, 0x39a, 0
        removeobject LOCALID_0FBOULDER2
        goto_if_set FLAG_TEMP_14, GauntletSoutheastCave_EventScript_setmaptilelAVAflow
        return

GauntletSoutheastCave_EventScript_setmaptilelAVAflowhandler::
        goto_if_unset FLAG_GAUNTLET_1FBOULDER2 GauntletSoutheastCave_EventScript_setmaptilelAVAflowRet
        goto_if_unset FLAG_GAUNTLET_1FBOULDER1 GauntletSoutheastCave_EventScript_setmaptilelAVAflowRet
GauntletSoutheastCave_EventScript_setmaptilelAVAflow::
	setmetatile 16, 3, 0x364, 1
GauntletSoutheastCave_EventScript_setmaptilelAVAflowRet::
	return

GauntletSoutheastCave_EventScript_FloorSwitchBoulder1::
	lockall
	goto_if_set FLAG_GAUNTLET_0FBOULDER1, GauntletSoutheastCave_EventScript_FloorSwitchAlreadyPressed
	setmetatile 13, 16, 0x39a, 0
        call_if_set FLAG_GAUNTLET_0FBOULDER2 GauntletSoutheastCave_EventScript_setmaptilelAVAflowhandler
	playse SE_ICE_BREAK
	setflag FLAG_GAUNTLET_0FBOULDER1
        hideobjectat LOCALID_0FBOULDER1, MAP_GAUNTLET_SOUTHEAST_CAVE
        removeobject LOCALID_0FBOULDER1
	special DrawWholeMapView
	waitse
GauntletSoutheastCave_EventScript_FloorSwitchAlreadyPressed::
	releaseall
	end

GauntletSoutheastCave_EventScript_FloorSwitchBoulder2::
	lockall
	goto_if_set FLAG_GAUNTLET_0FBOULDER2, GauntletSoutheastCave_EventScript_FloorSwitchAlreadyPressed
	setmetatile 16, 5, 0x39a, 0
        call_if_set FLAG_GAUNTLET_0FBOULDER1 GauntletSoutheastCave_EventScript_setmaptilelAVAflowhandler
	playse SE_ICE_BREAK
	setflag FLAG_GAUNTLET_0FBOULDER2
        hideobjectat LOCALID_0FBOULDER2, MAP_GAUNTLET_SOUTHEAST_CAVE
        removeobject LOCALID_0FBOULDER2
	special DrawWholeMapView
	waitse
	releaseall
	end

