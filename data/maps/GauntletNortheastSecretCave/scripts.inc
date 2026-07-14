GauntletNortheastSecretCave_MapScripts::
	.byte 0

GauntletNortheastSecretCave_TheAltar::
    lockall
    special DoSealedChamberShakingEffect_Short
    msgbox GauntletIsland_TxtCreepypastaAss
    delay 30
    msgbox GauntletIsland_TxtCreepypastaAss2
    delay 30
    msgbox GauntletIsland_TxtCreepypastaAss3
    releaseall
    end

GauntletIsland_TxtCreepypastaAss:
	.string "There is a scratching sound in\n"
	.string "the back of your neck.\p"
	.string "The altar reads\n"
	.string "“IN DEVOTION TO {PLAYER}.”$"

GauntletIsland_TxtCreepypastaAss2:
	.string "The altar reads\n"
	.string "“WHO BOILED THE QUIET LAKE\l"
	.string "ALIVE, LEAVING IT DEAD.”"

GauntletIsland_TxtCreepypastaAss3:
	.string "The altar reads\n"
	.string "“A PERMANENT CONSEQUENCE\l"
	.string "OF INSATIABLE CURIOSITY.”\p"
	.string "The altar reads\n"
	.string "“SOUND FAMILIAR?”$"
	.string "The altar reads\n"
	.string "“NO BAD DEED GOES UNREWARDED.”$"


GauntletIsland_Txt0IVHandler:
	.string "“SET WHICH STAT TO 0?”\p"
