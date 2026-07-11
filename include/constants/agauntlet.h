#ifndef GUARD_GAUNTLET_H
#define GUARD_GAUNTLET_H

void GauntletStart(struct ScriptContext *ctx);
void GauntletEnd(struct ScriptContext *ctx);
void CallnativeGauntletItemBall(struct ScriptContext *ctx);
static void InitGauntletBagItems(void);
static void RespawnAbout24RandomGauntletItemBalls(void);
static bool32 GauntletPartySetup(void);
static bool32 SquashEarthRibbonInfo(void);


const int GauntletItemsLow[8] = {
    ITEM_POTION,
    ITEM_POTION,
    ITEM_POTION,
    ITEM_FLUFFY_TAIL,
    ITEM_ANTIDOTE,
    ITEM_ORAN_BERRY,
    ITEM_X_ACCURACY,
    ITEM_POTION
};

const int GauntletItemsMed[8] = {
    ITEM_POTION,
    ITEM_POTION,
    ITEM_SUPER_POTION,
    ITEM_PECHA_BERRY,
    ITEM_PERSIM_BERRY,
    ITEM_X_ATTACK,
    ITEM_X_DEFEND,
    ITEM_ORAN_BERRY
};

const int GauntletItemsHigh[8] = {
    ITEM_SUPER_POTION,
    ITEM_SUPER_POTION,
    ITEM_FULL_HEAL,
    ITEM_ETHER,
    ITEM_X_SPECIAL,
    ITEM_X_SP_DEF,
    ITEM_X_SPEED,
    ITEM_FULL_RESTORE
};

const int GauntletItemsEnd[8] = {
    ITEM_SUPER_POTION,
    ITEM_SUPER_POTION,
    ITEM_HYPER_POTION,
    ITEM_FULL_RESTORE,
    ITEM_FULL_HEAL,
    ITEM_LEPPA_BERRY,
    ITEM_LUM_BERRY,
    ITEM_REVIVE
};


enum ItemPool {
    GAUNTLET_ITEM_POOL_LOW,
    GAUNTLET_ITEM_POOL_MED,
    GAUNTLET_ITEM_POOL_HIGH,
    GAUNTLET_ITEM_POOL_END
};

enum GauntletAltar{
    GAUNTLET_ALTAR_HP_1 = 0,//eldwurm 
    GAUNTLET_ALTAR_ATK_2 = 3,//titan, groudon OR REGI
    GAUNTLET_ALTAR_DEF_3 = 6,//nereid, kyogre
    GAUNTLET_ALTAR_SPEED_4 = 9,//winged lion, arceus fight
    GAUNTLET_ALTAR_SPATK_5 = 12,//Dark Void, guzzlord
    GAUNTLET_ALTAR_SPDEF_6 = 15,//saphrotroph, harvest, shaymin sky
    GAUNTLET_ALTAR_BOSS_7 = 18,// scary legendaries
    GAUNTLET_ALTAR_MAX = 24
};

#endif //GUARD_GAUNTLET_H