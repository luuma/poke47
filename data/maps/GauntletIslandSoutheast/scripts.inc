
GauntletIslandSoutheast_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, GauntletIslandSoutheast_OnTransition
	.byte 0

GauntletIslandSoutheast_OnTransition:
	special UpdateShoalTideFlag
	goto_if_set FLAG_SYS_SHOAL_TIDE, GauntletIslandSoutheast_SetHighTide
	goto GauntletIslandSoutheast_SetLowTide

GauntletIslandSoutheast_SetHighTide::
	setmaplayoutindex LAYOUT_AEGAUNTLET6
	end

GauntletIslandSoutheast_SetLowTide::
	setmaplayoutindex LAYOUT_AEGAUNTLET6_LOWTIDE
	end

GauntletIslandLow_ItemBall::
    callnative CallnativeGauntletItemBall
    .byte 0
    finditem VAR_RESULT, 1
    end

GauntletIslandLow_ItemBall_two::
    callnative CallnativeGauntletItemBall
    .byte 0
    finditem VAR_RESULT, 2
    end

GauntletIslandMed_ItemBall::
    callnative CallnativeGauntletItemBall
    .byte 1
    finditem VAR_RESULT, 1
    end

GauntletIslandHigh_ItemBall::
    callnative CallnativeGauntletItemBall
    .byte 2
    finditem VAR_RESULT, 1
    end

GauntletIslandEnd_ItemBall::
    callnative CallnativeGauntletItemBall
    .byte 3
    finditem VAR_RESULT 1
    end
