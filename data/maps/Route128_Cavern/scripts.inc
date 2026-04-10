Route128_Cavern_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, Route129Cave_OnLoad
	.byte 0

Route129Cave_OnLoad:
	call_if_set FLAG_129_BOULDER2, Route129_EventScript_setmaptile
	end

Route129_EventScript_setmaptile::
	setmetatile 64, 7, 0x279, 1
	setmetatile 64, 8, 0x2A4, 0
	return