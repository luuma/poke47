GuantletIslandNorth_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, GauntletIslandOnTransition
	map_script MAP_SCRIPT_ON_RESUME, Route113_OnResume @ 	setstepcallback STEP_CB_ASH ; end
	.byte 0

GauntletIslandOnTransition::
	call GauntletIsland_EventScript_SetAbnormalWeather
        end

GauntletIsland_EventScript_SetAbnormalWeather::
        setweather VAR_GAUNTLET_WEATHER
        return

GuantletIslandNorth_EventScript_SignLocked::
	msgbox GauntletIslandNorth_Text_SignLocked, MSGBOX_SIGN
	end

GauntletIslandNorth_Text_SignLocked:
	.string "FLOOD RISK\n"
	.string "DO NOT ENTER$"

GuantletIslandNorth_EventScript_SignTown::
	msgbox GauntletIslandNorth_Text_SignTown, MSGBOX_SIGN
	end

GauntletIslandNorth_Text_SignTown:
	.string "GAUNT CITY\p"
	.string "“In the quiet waters,\n"
	.string "growing forever.”$"
