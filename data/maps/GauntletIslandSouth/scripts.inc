
GauntletIslandSouth_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, GauntletIslandOnTransition
	map_script MAP_SCRIPT_ON_RESUME, Route113_OnResume @ 	setstepcallback STEP_CB_ASH ; end
	.byte 0

GauntletIsland_IslandStirs::
    lockall
    special DoSealedChamberShakingEffect_Short
    msgbox GauntletIsland_TxtTheIslandStirs 
    addvar VAR_GAUNTLET_9, 1
    releaseall
    end

GauntletIsland_TxtTheIslandStirs:
	.string "The island stirs…$"

GauntletIsland_AltarsLit::
    lockall
    playse SE_LAVARIDGE_FALL_WARP
    special DoSealedChamberShakingEffect_Long
    waitse
    msgbox GauntletIsland_TxtTheAltarsFlareToLife 
    addvar VAR_GAUNTLET_9, 1
    release
    end

GauntletIsland_TxtTheAltarsFlareToLife:
	.string "With a resounding tremor,\n"
	.string "the ALTARS flare to life…$"

GauntletIsland_RavenCBBC::
    lockall
    special DoSealedChamberShakingEffect_Short
    msgbox GauntletIsland_TxtRavenCBBC 
    addvar VAR_GAUNTLET_9, 1
    releaseall
    end

GauntletIsland_TxtRavenCBBC:
	.string "Your challenge begins.$"

GauntletIsland_BeatAltar::
    lockall
    msgbox GauntletIsland_TxtBeatAltar
    closemessage
    applymovement LOCALID_PLAYER Common_Movement_WalkUp2
    waitmovement 0
    releaseall
    end


GauntletIsland_TxtBeatAltar:
	.string "Until you conquer the altar, your\n"
	.string "party cannot level up past a\l"
	.string "certain point.\p"
	.string "Decided to go back.$"

GauntletIsland_AltarLoss::
    setvar B_VAR_WILD_AI_FLAGS, 0
    warp MAP_ROUTE_100, 8, 11
    waitstate
    end

GauntletIsland_AltarBlessing::
    setvar VAR_0x8009, 0
GauntletIsland_AltarBlessingLoop::
    canhypertrain VAR_0x8008, VAR_0x8009
    goto_if_eq VAR_RESULT, TRUE, GauntletIsland_AltarTrain
GauntletIsland_AltarBlessingAddvar::
    addvar VAR_0x8009, 1
    getpartysize
    goto_if_lt VAR_0x8009, VAR_RESULT, GauntletIsland_AltarBlessingLoop
    return

GauntletIsland_AltarTrain::
    hypertrain VAR_0x8008, VAR_0x8009
    goto GauntletIsland_AltarBlessingAddvar
    end

GauntletIsland_AltarQuiet::
    msgbox GauntletIsland_AltarQuiettxt, MSGBOX_DEFAULT 
	call_if_set FLAG_GAUNTLET_HP_ALTAR, GauntletIsland_Multipushhp
	call_if_set FLAG_GAUNTLET_ATK_ALTAR,  GauntletIsland_MultipushATK 
	call_if_set FLAG_GAUNTLET_SPATK_ALTAR,  GauntletIsland_MultipushSPATK 
	call_if_set FLAG_GAUNTLET_SPEED_ALTAR,  GauntletIsland_MultipushSPE
	goto_if_ge VAR_TEMP_2, 1, GauntletIsland_Teleportmenu
	closemessage
	release
	end

GauntletIsland_Multipushhp::
        goto_if_eq VAR_LAST_TALKED, localid_hp, GauntletIsland_ret @ 2
	setvar VAR_0x8008 1
    	dynmultipush GauntletIsland_south, 1
	addvar VAR_TEMP_2, 1
GauntletIsland_ret::
	return

GauntletIsland_MultipushATK::
        goto_if_eq VAR_LAST_TALKED, localid_atk, GauntletIsland_ret @ 6
	setvar VAR_0x8008 2
    	dynmultipush GauntletIsland_east, 2
	addvar VAR_TEMP_2, 1
	return

GauntletIsland_MultipushSPATK::
        goto_if_eq VAR_LAST_TALKED, localid_spatk, GauntletIsland_ret @ 31
	setvar VAR_0x8008 3
    	dynmultipush GauntletIsland_west, 3
	addvar VAR_TEMP_2, 1
	return

GauntletIsland_MultipushSPE::
        goto_if_eq VAR_LAST_TALKED, localid_speed, GauntletIsland_ret @ 1
	setvar VAR_0x8008 4
    	dynmultipush GauntletIsland_north, 4
	addvar VAR_TEMP_2, 1
	return

GauntletIsland_south:
   	.string "SOUTH$"

GauntletIsland_east:
   	.string "EAST$"

GauntletIsland_west:
   	.string "WEST$"

GauntletIsland_north:
   	.string "NORTH$"

GauntletIsland_Altarteletext:
	.string "Would you like to use the\n"
	.string "ALTAR to teleport?$"


GauntletIsland_Teleportmenu::
	message GauntletIsland_Altarteletext
	waitmessage
        dynmultistack 0, 0, FALSE, 6, FALSE, VAR_0x800A, DYN_MULTICHOICE_CB_NONE
	copyvar VAR_0x8008, VAR_RESULT
        goto_if_eq VAR_0x8008, MULTI_B_PRESSED, RustboroCity_DevonCorp_2F_EventScript_CancelFossilSelect
        goto_if_eq VAR_0x8008, 1, GauntletIsland_Warp_hp
        goto_if_eq VAR_0x8008, 2, GauntletIsland_Warp_atk
        goto_if_eq VAR_0x8008, 3, GauntletIsland_Warp_satk
        goto_if_eq VAR_0x8008, 4, GauntletIsland_Warp_spe
        end

GauntletIsland_Warp_hp::
	warpteleport MAP_GAUNTLET_ISLAND_SOUTH, 24, 3
	waitstate
	end

GauntletIsland_Warp_atk::
	warpteleport MAP_GAUNTLET_ISLAND_NORTHEAST, 37, 39
	waitstate
	end

GauntletIsland_Warp_satk::
	warpteleport MAP_GAUNTLET_ISLAND_SOUTHWEST, 26, 15
	waitstate
	end

GauntletIsland_Warp_spe::
	warpteleport MAP_GAUNTLET_ISLAND_FINALE, 10, 41
	waitstate
	end

GauntletIsland_AltarQuiettxt:
	.string "The ALTAR is quiet.$"

GauntletIsland_AltarReleaseEnd::
    msgbox GauntletIsland_AltarReleaseEndtxt
    release
    end

GauntletIsland_AltarReleaseEndtxt:
	.string "You backed away to prepare.$"


