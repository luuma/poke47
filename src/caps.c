#include "global.h"
#include "battle.h"
#include "event_data.h"
#include "caps.h"
#include "pokemon.h"
#include "item.h"


u32 GetCurrentLevelCap(void)
{
    static const u32 sLevelCapFlagMap[][2] =
    {
        {FLAG_RESCUED_BIRCH, 10},//0
        {FLAG_BADGE01_GET, 13},//1
        {FLAG_BADGE02_GET, 17},//1
        {FLAG_BADGE03_GET, 23},//2
        {FLAG_BADGE04_GET, 26},//3
        {FLAG_BADGE05_GET, 28},//3
        {FLAG_BADGE06_GET, 30},//3
        {FLAG_BADGE07_GET, 38},//4
        {FLAG_BADGE08_GET, 40},//6
        {FLAG_SIDNEY_SUCKER_PUNCH, 49},//0. high, to let people full-send champion
        {FLAG_PHOEBE_PHANTOM_FORCE, 50},//1
        {FLAG_JUAN_DAZZLING_GLEAM, 51},//2
        {FLAG_DRAKE_DRAGON_PULSE, 52},//3
        {FLAG_IS_CHAMPION, 53},//5
    };
    static const u32 sGauntletCapFlagMap[][2] =
    {
        {FLAG_GAUNTLET_HP_ALTAR, 7},//hp. This boss is easy enough.
        {FLAG_GAUNTLET_ATK_ALTAR, 14},//atk. This boss should try to kick yuor Ass.
        {FLAG_GAUNTLET_SPATK_ALTAR, 18},//def
        {FLAG_GAUNTLET_SPEED_ALTAR, 25},//speed
        {FLAG_GAUNTLET_DEF_ALTAR, 24},//spatk
        {FLAG_GAUNTLET_SPDEF_ALTAR, 27},//sdef
        {FLAG_GAUNTLET_BOSS_ALTAR, 31},//sdef
    };
    u32 i;

    if (FlagGet(FLAG_GAUNTLET_CHALLENGE))// starts later
    {
        if (VarGet(VAR_WILD_AI_FLAGS) != 0)
            return 90;
        for (i = 0; i < ARRAY_COUNT(sGauntletCapFlagMap); i++)
        {
            if (!FlagGet(sGauntletCapFlagMap[i][0]))
            {
                if (FlagGet(FLAG_RAISE_LEVEL_CAP))
                     return sGauntletCapFlagMap[i][1] + 3;
                else
                    return sGauntletCapFlagMap[i][1];
            }
        }
    }
    else if (CheckBagHasItem(ITEM_LEVEL_CAP, 1) || !FlagGet(FLAG_RESCUED_BIRCH) || VarGet(VAR_GAUNTLET_ACTIVE) == 1) // When exiting gauntlet, flag gauntlet challenge is cleared, then we check caps, then this is cleared.
    {
        for (i = 0; i < ARRAY_COUNT(sLevelCapFlagMap); i++)
        {
            if (!FlagGet(sLevelCapFlagMap[i][0]))
                return sLevelCapFlagMap[i][1];
        }
    }


    else if (B_LEVEL_CAP_TYPE == LEVEL_CAP_VARIABLE)
    {
        return VarGet(B_LEVEL_CAP_VARIABLE);
    }

    return MAX_LEVEL;
}

u32 GetPreviousLevelCapForXP(void)
{
    static const u32 sLevelCapFlagMap[][2] =
    {
        {FLAG_RESCUED_BIRCH, 7},//0
        {FLAG_BADGE01_GET, 15},//+1
        {FLAG_BADGE02_GET, 18},//1
        {FLAG_BADGE03_GET, 23},//2
        {FLAG_BADGE04_GET, 26},//3
        {FLAG_BADGE05_GET, 28},//3
        {FLAG_BADGE06_GET, 31},//slightly higher because this is a long stretch and includes two pointless game lengtheners and a shitload of new fun tools.          
        {FLAG_BADGE07_GET, 38},//4
        {FLAG_BADGE08_GET, 41},//5. see above. Long stretch.
        {FLAG_SIDNEY_SUCKER_PUNCH, 50},//0. high, to let people full-send champion
        {FLAG_IS_CHAMPION, 55},// so doubled until lv50.
        {FLAG_DEFEATED_METEOR_FALLS_STEVEN, 105},// Perma double.
        {FLAG_GAUNTLET_CHALLENGE, 105},// Ensures boost while set. 
        //{FLAG_GAUNTLET_HP_ALTAR, 7},// Cancels all other boosts while set.
        //{FLAG_GAUNTLET_ATK_ALTAR, 10},// Cancels it out while set.
        //{FLAG_GAUNTLET_DEF_ALTAR, 15},// Cancels it out while set.
        //{FLAG_GAUNTLET_SPEED_ALTAR, 20},// Cancels it out while set.
        //{FLAG_GAUNTLET_SPATK_ALTAR, 23},// Cancels it out while set.
        //{FLAG_GAUNTLET_SPDEF_ALTAR, 26},// Cancels it out while set.
    };
    u32 i;

    for (i = ARRAY_COUNT(sLevelCapFlagMap) - 1; i >= 0; i--)
    {
        if (FlagGet(sLevelCapFlagMap[i][0]))
            return sLevelCapFlagMap[i][1];
    }
    return 1;// this will never happen
}


u32 GetSoftLevelCapExpValue(u32 level, u32 expValue)
{
    static const u32 sExpScalingDown[5] = { 4, 8, 16, 32, 64 };
    static const u32 sExpScalingUp[5]   = { 16, 8, 4, 2, 1 };

    u32 levelDifference;
    u32 currentLevelCap = GetCurrentLevelCap();
    u32 prevLevelCap = GetPreviousLevelCapForXP();
    //if (B_EXP_CAP_TYPE == EXP_CAP_NONE)
        //return expValue;

    if (level < currentLevelCap)
    {
        if (level < prevLevelCap)
        {
            levelDifference = prevLevelCap - level;
            if (levelDifference > ARRAY_COUNT(sExpScalingUp) - 1)
                return expValue*2;
            else
                return expValue + (expValue / sExpScalingUp[levelDifference]);// boost the leveling rate by about double if you're below the previous level cap.
        }
        else
        {
            return expValue;
        }
    }
    else if (CheckBagHasItem(ITEM_LEVEL_CAP, 1))
    {
        return 0;
    }
    else if (B_EXP_CAP_TYPE == EXP_CAP_SOFT)
    {
        levelDifference = level - currentLevelCap;
        if (levelDifference > ARRAY_COUNT(sExpScalingDown) - 1)
            return expValue / sExpScalingDown[ARRAY_COUNT(sExpScalingDown) - 1];
        else
            return expValue / sExpScalingDown[levelDifference];
    }
    else
    {
       return expValue;
    }
}

u32 GetCurrentEVCap(void)
{
    static const u16 sEvCapFlagMap[][2] = {
        // Define EV caps for each milestone
        {FLAG_BADGE01_GET, MAX_TOTAL_EVS *  1 / 17},
        {FLAG_BADGE02_GET, MAX_TOTAL_EVS *  3 / 17},
        {FLAG_BADGE03_GET, MAX_TOTAL_EVS *  5 / 17},
        {FLAG_BADGE04_GET, MAX_TOTAL_EVS *  7 / 17},
        {FLAG_BADGE05_GET, MAX_TOTAL_EVS *  9 / 17},
        {FLAG_BADGE06_GET, MAX_TOTAL_EVS * 11 / 17},
        {FLAG_BADGE07_GET, MAX_TOTAL_EVS * 13 / 17},
        {FLAG_BADGE08_GET, MAX_TOTAL_EVS * 15 / 17},
        {FLAG_IS_CHAMPION, MAX_TOTAL_EVS},
    };

    if (B_EV_CAP_TYPE == EV_CAP_FLAG_LIST)
    {
        for (u32 evCap = 0; evCap < ARRAY_COUNT(sEvCapFlagMap); evCap++)
        {
            if (!FlagGet(sEvCapFlagMap[evCap][0]))
                return sEvCapFlagMap[evCap][1];
        }
    }
    else if (B_EV_CAP_TYPE == EV_CAP_VARIABLE)
    {
        return VarGet(B_EV_CAP_VARIABLE);
    }
    else if (B_EV_CAP_TYPE == EV_CAP_NO_GAIN)
    {
        return 0;
    }

    return MAX_TOTAL_EVS;
}
