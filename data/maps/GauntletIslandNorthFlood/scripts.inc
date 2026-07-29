GauntletIslandNorthFlood_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, GauntletIslandOnTransition @ Ah they can have their weather. whatever
	map_script MAP_SCRIPT_ON_RETURN_TO_FIELD, GauntletIslandOnResume @ Banish the weak lol
	.byte 0


gauntlet_boss_left_staircase::
lockall
applymovement LOCALID_PLAYER, GauntletMoveLeftstaircase
waitmovement
goto GauntletIsland_AltarTWIN
end


gauntlet_boss_right_staircase::
lockall
applymovement LOCALID_PLAYER, GauntletMoveRightstaircase
waitmovement
goto GauntletIsland_AltarTWIN
end


GauntletMoveRightstaircase:
	walk_left
	walk_left
	walk_up
	walk_in_place_down
	step_end

GauntletMoveLeftstaircase:
	walk_right
	walk_right
	walk_up
	walk_in_place_down
	step_end