AquaHideout_UnusedRubyMap1_MapScripts::
	map_script MAP_SCRIPT_ON_LOAD, AquaDuo_OnLoad


AquaDuo_OnLoad::
	call_if_set FLAG_HIDE_SEAFLOOR_CAVERN_AQUA_GRUNTS, AquaDuo_SetMaptileFull
	call_if_ge VAR_HIDEOUT_DUO_SECTION, 4, AquaDuo_SetMaptile4
	call_if_eq VAR_HIDEOUT_DUO_SECTION, 3, AquaDuo_SetMaptile3
	call_if_eq VAR_HIDEOUT_DUO_SECTION, 2, AquaDuo_SetMaptile2
	call_if_eq VAR_HIDEOUT_DUO_SECTION, 1, AquaDuo_SetMaptile1
	end

AquaDuo_SetMaptileFull::
	setmetatile 18, 16, 0x229, FALSE
AquaDuo_SetMaptile4::
	setmetatile 15, 15, 0x229, FALSE
	setmetatile 12, 16, METATILE_Facility_CameraOffPressed, FALSE
AquaDuo_SetMaptile3::
	setmetatile 12, 17, 0x229, FALSE
	setmetatile 7, 13, METATILE_Facility_CameraOffPressed, FALSE
AquaDuo_SetMaptile2::
	setmetatile 3, 14, 0x203, FALSE
	setmetatile 7, 17, METATILE_Facility_CameraOffPressed, FALSE
AquaDuo_SetMaptile1::
	setmetatile 9, 22, 0x229, FALSE
	setmetatile 4, 20, METATILE_Facility_CameraOffPressed, FALSE
	goto_if_eq VAR_HIDEOUT_DUO_SECTION, 5, AquaDuo_SetMaptileOdds
	goto_if_eq VAR_HIDEOUT_DUO_SECTION, 6, AquaDuo_SetMaptileEvens
        return

AquaDuo_SetMaptileOdds::
	setmetatile 12, 20, 0x229, FALSE
	setmetatile 14, 19, METATILE_Facility_CameraOffPressed, FALSE
	setmetatile 17, 18, 0x2DA, FALSE

	setmetatile 15, 21, 0x229, FALSE
	setmetatile 15, 22, 0x229, FALSE
	setmetatile 19, 21, 0x229, FALSE
	setmetatile 19, 22, 0x229, FALSE
	setmetatile 21, 19, 0x229, FALSE
	setmetatile 22, 19, 0x229, FALSE
	setmetatile 23, 19, 0x229, FALSE
	setmetatile 17, 21, 0x3ec, TRUE
	setmetatile 17, 22, 0x3ec, TRUE
	setmetatile 21, 21, 0x3ec, TRUE
	setmetatile 21, 22, 0x3ec, TRUE
        return

AquaDuo_SetMaptileEvens::
	setmetatile 12, 20, 0x229, FALSE
	setmetatile 17, 18, METATILE_Facility_CameraOffPressed, FALSE
	setmetatile 14, 19, 0x2DA, FALSE
	setmetatile 17, 21, 0x229, FALSE
	setmetatile 17, 22, 0x229, FALSE
	setmetatile 21, 21, 0x229, FALSE
	setmetatile 21, 22, 0x229, FALSE
	setmetatile 15, 21, 0x3ec, TRUE
	setmetatile 15, 22, 0x3ec, TRUE
	setmetatile 19, 21, 0x3ec, TRUE
	setmetatile 19, 22, 0x3ec, TRUE
	setmetatile 21, 19, 0x3ec, TRUE
	setmetatile 22, 19, 0x3ec, TRUE
	setmetatile 23, 19, 0x3ec, TRUE
        return

AquaDuo_DroneWarp1::
	warpteleport MAP_AQUA_HIDEOUT_UNUSED_RUBY_MAP1, 7, 26
        waitstate
        end


AquaDuo_Switch5Alternate::
	lockall
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
        call_if_eq VAR_TEMP_1, 19, AquaDuo_cancelifX2
        call_if_eq VAR_TEMP_1, 21, AquaDuo_cancelifX
        call_if_eq VAR_TEMP_1, 22, AquaDuo_cancelifX
	playse SE_ICE_BREAK
	waitse
        setvar VAR_HIDEOUT_DUO_SECTION, 5
        call AquaDuo_SetMaptile1
	special DrawWholeMapView
        releaseall
        end

AquaDuo_Switch6Alternate::
	lockall
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
        call_if_eq VAR_TEMP_1, 19, AquaDuo_cancelifX2
        call_if_eq VAR_TEMP_1, 21, AquaDuo_cancelifX
        call_if_eq VAR_TEMP_1, 22, AquaDuo_cancelifX
	playse SE_ICE_BREAK
	waitse
        setvar VAR_HIDEOUT_DUO_SECTION, 6
        call AquaDuo_SetMaptile1
	special DrawWholeMapView
        releaseall
        end

AquaDuo_cancelifX2::
	goto_if_eq VAR_TEMP_0, 21, AquaDuo_ReleaseallEnd
	goto_if_eq VAR_TEMP_0, 22, AquaDuo_ReleaseallEnd
	goto_if_eq VAR_TEMP_0, 23, AquaDuo_ReleaseallEnd
	return

AquaDuo_cancelifX::
	goto_if_eq VAR_TEMP_0, 21, AquaDuo_ReleaseallEnd
	goto_if_eq VAR_TEMP_0, 19, AquaDuo_ReleaseallEnd
	goto_if_eq VAR_TEMP_0, 17, AquaDuo_ReleaseallEnd
	goto_if_eq VAR_TEMP_0, 15, AquaDuo_ReleaseallEnd
	return

AquaDuo_ReleaseallEnd::
        playSE SE_BOO
        waitse
        releaseall
        end

AquaDuo_Switch1::
	lockall
	playse SE_ICE_BREAK
	waitse
        setvar VAR_HIDEOUT_DUO_SECTION, 1
        call AquaDuo_SetMaptile1
	special DrawWholeMapView
        releaseall
        end

AquaDuo_Switch2::
	lockall
	playse SE_ICE_BREAK
	waitse
        setvar VAR_HIDEOUT_DUO_SECTION, 2
        call AquaDuo_SetMaptile2
	special DrawWholeMapView
        releaseall
        end

AquaDuo_Switch3::
	lockall
	playse SE_ICE_BREAK
	waitse
        setvar VAR_HIDEOUT_DUO_SECTION, 3
        call AquaDuo_SetMaptile3
	special DrawWholeMapView
        releaseall
        end

AquaDuo_Switch4::
	lockall
	playse SE_ICE_BREAK
	waitse
        setvar VAR_HIDEOUT_DUO_SECTION, 4
        call AquaDuo_SetMaptile4
	special DrawWholeMapView
        releaseall
        end

