

GauntletIslandSouth_MapScripts::
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
    msgbox GauntletIsland_AltarQuiettxt
    release
    end

GauntletIsland_AltarQuiettxt:
	.string "The ALTAR is quiet.$"

GauntletIsland_AltarReleaseEnd::
    msgbox GauntletIsland_AltarReleaseEndtxt
    release
    end

GauntletIsland_AltarReleaseEndtxt:
	.string "You backed away to prepare.$"


