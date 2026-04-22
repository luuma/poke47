DewBeach106_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DewBeach106_OnTransition
	.byte 0

DewBeach106_OnTransition:
	special UpdateShoalTideFlag
	goto_if_set FLAG_SYS_SHOAL_TIDE, DewBeach106_SetHighTide
	goto DewBeach106_SetLowTide

DewBeach106_SetHighTide::
	setmaplayoutindex LAYOUT_DEW_BEACH
	end

DewBeach106_SetLowTide::
	setmaplayoutindex LAYOUT_DEW_BEACH_LOWTIDE
	end
