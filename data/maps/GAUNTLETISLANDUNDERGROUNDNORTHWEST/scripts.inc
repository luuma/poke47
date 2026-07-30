GAUNTLETISLANDUNDERGROUNDNORTHWEST_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, GAUNTLETISLANDUNDERGROUNDNORTHWEST_OnLoad
	.byte 0

GAUNTLETISLANDUNDERGROUNDNORTHWEST_OnLoad:
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	call_if_le VAR_TEMP_1, 1, opensesamegauntlettiles
        end

gauntlethouse_hiddenlever::
	lockall
        goto_if_set FLAG_TEMP_10, opensesamegauntletDONE
	msgbox theresalevergauntlet MSGBOX_YESNO
	goto_if_eq VAR_RESULT, YES, opensesamegauntlet
	releaseall
	end

opensesamegauntlet::
	msgbox theresalevergauntletpull
	waitmessage
	playse SE_TRUCK_DOOR
	call opensesamegauntlettiles
	delay 20
        releaseall
	end

opensesamegauntletDONE::
	msgbox theresalevergauntletpullD0NE
        releaseall
	end

opensesamegauntlettiles::
	setmetatile 4, 0, 0x2a6, 1
	setmetatile 5, 0, 0x2a7, 1
	setmetatile 6, 0, 0x2ee, 1

	setmetatile 4, 1, 0x2ae, 1
	setmetatile 5, 1, 0x2af, 1
	setmetatile 6, 1, 0x2f6, 0

	setmetatile 4, 2, 0x2d8, 0
	setmetatile 5, 2, 0x2d9, 0
	setmetatile 6, 2, 0x3ff, 0
	special DrawWholeMapView
	setflag FLAG_TEMP_10

        return

theresalevergauntlet:
	.string "There's a fake book in this bookcase.\n"
	.string "Give it a pull?$"

theresalevergauntletpull:
	.string "{PLAYER} pulled the fake book.$"


theresalevergauntletpullD0NE:
	.string "A single book juts out.$"

