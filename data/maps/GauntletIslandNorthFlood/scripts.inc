GauntletIslandNorthFlood_MapScripts::
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
	walk_in_place_up
	step_end

GauntletMoveLeftstaircase:
	walk_right
	walk_right
	walk_in_place_up
	step_end