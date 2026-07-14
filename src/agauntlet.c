#include "global.h"

#include "event_data.h"
#include "field_specials.h"
#include "item.h"
#include "pokemon_storage_system.h"
#include "pokemon.h"
#include "random.h"
#include "script.h"

// boons
#include "malloc.h"
#include "string_util.h"
#include "script_menu.h"

#include "constants/agauntlet.h"
#include "constants/vars.h"

static void InitGauntletBagItems(void);
static void RespawnAbout24RandomGauntletItemBalls(void);
static bool32 GauntletPartySetup(void);
static bool32 SquashEarthRibbonInfo(void);

static enum BoonType GetGauntletBoonType(u32 id);
static enum GauntletTypes GetGauntletAltar(u32 id);
static enum BoonType GetGauntletSpecial(u32 id);

static u8 GetGauntletBoon(enum GauntletTypes type, enum GauntletRarity rarity, u8 MultichoiceOptions[4]);
static void DoGauntletBoonList(u8 stapleWeight, u8 commonWeight, u8 rareWeight, u8 epicWeight);
static bool8 dynmultipushFromGauntletVar(u32 id);


static void RespawnAbout24RandomGauntletItemBalls(void)
{
    u32 i;
    for (i = FLAG_GAUNTLET_3; i <= FLAG_GAUNTLET_LAST; i++)
        FlagClear(i);
    //assertf(FALSE, "RespawnAbout24RandomGauntletItemBalls i=%d", i);

    for (i = FLAG_GAUNTLET_MINT_A; i <= FLAG_GAUNTLET_MINT_G; i++)
        FlagClear(i);

    for (i = 0; i < 34; i++)
        FlagSet(FLAG_GAUNTLET_3 + ((Random()+i) % FLAGS_GAUNTLET));

    return;//Roll 34 random sets in the flags. Giving roughly 48*(1-(47/48)^34) item balls, or 24.04 item balls. But could be anywhere from 1 to 34 removed!
}

static void InitGauntletBagItems(void)//COPY of initpyramiditems but gives some heal balls
{
    u32 i;
    for (i = 0; i < PYRAMID_BAG_ITEMS_COUNT; i++)
    {
        gSaveBlock2Ptr->frontier.pyramidBag.itemId[1][i] = ITEM_NONE;
        gSaveBlock2Ptr->frontier.pyramidBag.quantity[1][i] = ITEM_NONE;
    }
    AddPyramidBagItem(ITEM_HEAL_BALL, 4);
    assertf(FALSE, "InitGauntletBagItems i=%d", i);
    return;
}

static bool32 GauntletPartySetup(void)
{
    //if (GetMonData(&gParties[B_TRAINER_PLAYER][1], MON_DATA_SPECIES) != SPECIES_NONE)
        //return FALSE;// check if party count is more than one and if so, go to EventScript_AccessPokemonStorage.
    if (GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_SPECIES_OR_EGG) == SPECIES_EGG)
        return FALSE;// Failsafe
    if (GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_HP) == 0)
        return FALSE;// Failsafe
    bool32 btrue = TRUE;
    bool32 bfalse = FALSE;
    SetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_EARTH_RIBBON, &btrue);
    u8 checkcopy = CopyMonToPC(&gParties[B_TRAINER_PLAYER][0]);
    if (checkcopy == MON_CANT_GIVE)// copy and check it happened successfully.
    {
        SetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_EARTH_RIBBON, &bfalse);
        return FALSE;
    }
    enum Species species = GetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_SPECIES);
    u32 expPoints = gExperienceTables[gSpeciesInfo[species].growthRate][5];
    SetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_EXP, &expPoints);
    u32 lv = 5;
    SetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_LEVEL, &lv);
    //devolve. fuck it lol.
    enum Species prespecies = GetSpeciesPreEvolution(species);
    if (prespecies != SPECIES_NONE)
    {
        enum Species prespecies2 = GetSpeciesPreEvolution(prespecies);
        if (prespecies2 != SPECIES_NONE)
            SetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_SPECIES, &prespecies2);
        else
            SetMonData(&gParties[B_TRAINER_PLAYER][0], MON_DATA_SPECIES, &prespecies);
    }
    GiveMonInitialMoveset(&gParties[B_TRAINER_PLAYER][0]);
    CalculateMonStats(&gParties[B_TRAINER_PLAYER][0]);
    return TRUE;
}
static u8 Squash(struct Pokemon *mon1, struct BoxPokemon *checkingMon)
{
                
                enum Species species = GetBoxMonData(checkingMon, MON_DATA_SPECIES);
                u8 Level = GetLevelFromBoxMonExp(checkingMon);
                u32 exp = GetBoxMonData(checkingMon, MON_DATA_EXP);
                enum Item heldItem = GetBoxMonData(checkingMon, MON_DATA_HELD_ITEM);


                //assertf(FALSE, "species %d", species);
                //assertf(FALSE, "exp %d", exp);
                //assertf(FALSE, "helditm %d", heldItem);
                //assertf(FALSE, "level %d", Level);
                //assertf(FALSE, "taerget %d", h); I went fucking MENTAL trying to debug this.


                SetMonData(mon1, MON_DATA_SPECIES, &species);
                SetMonData(mon1, MON_DATA_EXP, &exp);
                SetMonData(mon1, MON_DATA_HELD_ITEM, &heldItem);
                SetMonData(mon1, MON_DATA_LEVEL, &Level);

                u32 k;
                for (k=0; k< MAX_MON_MOVES; k++)
                    SetMonMoveSlot(mon1, GetBoxMonData(checkingMon, MON_DATA_MOVE1 + k), k);

                CalculateMonStats(mon1);
                return Level;
}

static bool32 SquashEarthRibbonInfo(void)
{
    u32 h;
    u32 contd = FALSE;
    struct Pokemon *mon;
    for (h = 0; h < PARTY_SIZE; h++)
    {
        if (GetMonData(&gParties[B_TRAINER_PLAYER][h], MON_DATA_EARTH_RIBBON))
        {
            contd = TRUE;
            mon = &gParties[B_TRAINER_PLAYER][h];
            break;
        }
    }
    if (!contd)
        return FALSE; 

    u32 i, j;
    contd = FALSE;
    u8 Level = 5;
    enum Species species;
    SetPCBoxToSendMon(VarGet(VAR_PC_BOX_TO_SEND_MON));
    i = StorageGetCurrentBox();

    do
    {
        for (j = 0; j < IN_BOX_COUNT; j++)
        {
            struct BoxPokemon *checkingMon = GetBoxedMonPtr(i, j);
            if (GetBoxMonData(checkingMon, MON_DATA_SPECIES) == SPECIES_NONE)
                continue;
            contd = GetBoxMonData(checkingMon, MON_DATA_EARTH_RIBBON);
            if (contd == TRUE)
            {
                Level = Squash(mon, checkingMon);
                ZeroBoxMonAt(i,j);
                bool32 neveragain = FALSE;
                SetMonData(mon, MON_DATA_EARTH_RIBBON, &neveragain);
                contd = TRUE;
                break;
            }
        }
        if (contd == TRUE);
            break;
        i++;
        if (i == TOTAL_BOXES_COUNT)
            i = 0;
    } while (i != StorageGetCurrentBox());


    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (i == h)
            continue;
        if (GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_SPECIES) == SPECIES_NONE)
            continue;
        if (GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_LEVEL) > Level)
        {
            species = GetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_SPECIES);
            SetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_LEVEL, &Level);
            u32 expPoints = gExperienceTables[gSpeciesInfo[species].growthRate][Level];// has to be done from scratch or else we do some delevel shit.
            SetMonData(&gParties[B_TRAINER_PLAYER][i], MON_DATA_EXP, &expPoints);
        }
    }
    return contd;
}

/// These need to go in the save file.
static rng_value_t seedBoss;
static rng_value_t seedItems;
static rng_value_t seedItemsmed;
static rng_value_t seedItemshigh;
static rng_value_t seedItemsend;
static rng_value_t seedMintHaha;

static rng_value_t seedBoons;

static void GauntletSeedRng(void)
{
    u32 setup = Random32();
    seedBoss = LocalRandomSeed(setup);
    seedItems = LocalRandomSeed(setup);
    seedItemsmed = LocalRandomSeed(setup);
    seedItemshigh = LocalRandomSeed(setup);
    seedItemsend = LocalRandomSeed(setup);
    seedMintHaha = LocalRandomSeed(setup);
    seedBoons = LocalRandomSeed(setup);
}

u32 GauntletReadRng(u32 integer)//Nearly working but not quite.
{ 
    return LocalRandom32(&seedBoss) % integer;
}

static u32 GauntletReadRngBoons(u32 integer)
{ 
    return LocalRandom32(&seedBoons) % integer;
}

enum Item GauntletReturnRngMint(void)
{ 
    return ITEM_LONELY_MINT + LocalRandom32(&seedMintHaha) % 21;// number between 0 and 20, with serious mint being item 101.
}

void GauntletStart(struct ScriptContext *ctx)
{
    bool32 SuccessfulPartySetup = GauntletPartySetup();
    if (SuccessfulPartySetup)
    {
        GauntletSeedRng();
        RespawnAbout24RandomGauntletItemBalls();
        FlagSet(FLAG_GAUNTLET_CHALLENGE);
        FlagSet(FLAG_STORING_ITEMS_IN_PYRAMID_BAG);//PRObably not needed.
        VarSet(VAR_GAUNTLET_8, 1);// used for an OnFrame route 100 map script. Tracks to FLAG_GAUNTLET_CHALLENGE
        VarSet(VAR_GAUNTLET_9, 0);// tutorial
        InitGauntletBagItems();// must happen after flag gauntlet challenge set.
    }
    VarSet(VAR_RESULT, SuccessfulPartySetup);
    return;
}

void GauntletEnd(struct ScriptContext *ctx)// This will be callnative'd from a global script that runs and records info. it may be worth calling this in e.g. like, a script that runs everywhere constantly except gauntlet island
{
    bool32 SuccessfulSquash = SquashEarthRibbonInfo();
    FlagClear(FLAG_GAUNTLET_CHALLENGE);
    FlagClear(FLAG_STORING_ITEMS_IN_PYRAMID_BAG);//PRObably not needed.
    VarSet(VAR_GAUNTLET_8, 0);
    VarSet(VAR_RESULT, SuccessfulSquash);
    return;
}


const int GauntletItemsLow[7] = {
    ITEM_HP_UP,
    ITEM_PP_UP,
    ITEM_POTION,
    ITEM_FLUFFY_TAIL,
    ITEM_PECHA_BERRY,
    ITEM_ORAN_BERRY,
    ITEM_FULL_HEAL
};

const int GauntletItemsMed[8] = {
    ITEM_PROTEIN,
    ITEM_IRON,
    ITEM_SUPER_POTION,
    ITEM_CHERI_BERRY,
    ITEM_PERSIM_BERRY,
    ITEM_X_ATTACK,
    ITEM_X_DEFEND,
    ITEM_ABILITY_CAPSULE
};

const int GauntletItemsHigh[9] = {
    ITEM_ZINC,
    ITEM_CALCIUM,
    ITEM_CARBOS,
    ITEM_X_SPECIAL,
    ITEM_X_SP_DEF,
    ITEM_X_SPEED,
    ITEM_FULL_HEAL,
    ITEM_FULL_RESTORE,
    ITEM_ABILITY_PATCH
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

void CallnativeGauntletItemBall(struct ScriptContext *ctx)
{
   enum ItemPool itemPool = ScriptReadByte(ctx);
   u32 rand;
   enum Item item = ITEM_BERRY_JUICE;
   switch (itemPool){
      case GAUNTLET_ITEM_POOL_LOW:
          rand = LocalRandom32(&seedItems) % 7;
          item =  GauntletItemsLow[rand];
          break;
      case GAUNTLET_ITEM_POOL_MED:
          rand = LocalRandom32(&seedItemsmed) % 8;
          item =  GauntletItemsMed[rand];
          break;
      case GAUNTLET_ITEM_POOL_HIGH:
          rand = LocalRandom32(&seedItemshigh) % 9;
          item =  GauntletItemsHigh[rand];
          break;
      case GAUNTLET_ITEM_POOL_END:
          rand = LocalRandom32(&seedItemsend) % 8;
          item =  GauntletItemsEnd[rand];
          break;
      default: break;
   }
   if (CheckBagHasSpace(item, 2)==0)
       VarSet(VAR_RESULT, 0); 
   else
       VarSet(VAR_RESULT, item); 
   return;
}

void TryUpdateRocksReveal(void)// script callnative
{
    if (!FlagGet(FLAG_GAUNTLET_CHALLENGE))
    {
        VarSet(VAR_RESULT, FALSE);
        return;
    }
    if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(MAP_GAUNTLET_ISLAND_SOUTHWEST)
        && gSaveBlock1Ptr->location.mapNum == MAP_NUM(MAP_GAUNTLET_ISLAND_SOUTHWEST))
    {
        if (FlagGet(FLAG_TEMP_12) && !FlagGet(FLAG_TEMP_11) && !FlagGet(FLAG_GAUNTLET_SHOWROCK_1))
            VarSet(VAR_RESULT, 1);

        if (FlagGet(FLAG_TEMP_14) && FlagGet(FLAG_TEMP_15) && !FlagGet(FLAG_TEMP_13) && !FlagGet(FLAG_TEMP_17) && !FlagGet(FLAG_GAUNTLET_SHOWROCK_2))
            VarSet(VAR_RESULT, 2);
    }
    else if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(MAP_GAUNTLET_ISLAND_SOUTHWEST)
        && gSaveBlock1Ptr->location.mapNum == MAP_NUM(MAP_GAUNTLET_ISLAND_SOUTHWEST)) // Can make these discrete. I have decided not to because it could mean someone gets a timer ball, has a eureka moment, then finds out they were "wrong".
    {
        if (FlagGet(FLAG_TEMP_11) 
         && FlagGet(FLAG_TEMP_12)
         && FlagGet(FLAG_TEMP_13)
         && FlagGet(FLAG_TEMP_14)
         && FlagGet(FLAG_TEMP_15)
         && !FlagGet(FLAG_TEMP_16)
         && !FlagGet(FLAG_TEMP_17)
         && !FlagGet(FLAG_TEMP_18)
        && !FlagGet(FLAG_GAUNTLET_SHOWROCK_3))
            VarSet(VAR_RESULT, 3);

        else if (!FlagGet(FLAG_TEMP_11) 
         && !FlagGet(FLAG_TEMP_12)
         && FlagGet(FLAG_TEMP_13)
         && !FlagGet(FLAG_TEMP_14)
         && FlagGet(FLAG_TEMP_15)
         && FlagGet(FLAG_TEMP_16)
         && FlagGet(FLAG_TEMP_17)
         && FlagGet(FLAG_TEMP_18)
        && !FlagGet(FLAG_GAUNTLET_SHOWROCK_4))
            VarSet(VAR_RESULT, 4);
    }
    return;
}

void CallnativeGauntletItemBallMultichoice(struct ScriptContext *ctx)
{
   enum ItemPool itemPool = ScriptReadByte(ctx);
   u32 rand = (Random() % 8);
   switch (itemPool){
      case GAUNTLET_ITEM_POOL_LOW:  VarSet(VAR_RESULT,  GauntletItemsLow[rand]); return;
      case GAUNTLET_ITEM_POOL_MED:  VarSet(VAR_RESULT,  GauntletItemsMed[rand]); return;
      case GAUNTLET_ITEM_POOL_HIGH: VarSet(VAR_RESULT, GauntletItemsHigh[rand]); return;
      case GAUNTLET_ITEM_POOL_END:  VarSet(VAR_RESULT,  GauntletItemsEnd[rand]); return;
      default: break;
   }
   VarSet(VAR_RESULT, ITEM_BERRY_JUICE); 
   return;
}


//#############
//#   BOONS   #
//#############



struct BoonGauntlet
{
    const u8 name[30];
    enum GauntletTypes altar;
    enum BoonType boonType;
    u32 special;
};


const struct BoonGauntlet BoonList[GB_LENGTH] = {
[GB_TOXIC] =      {         .name =_("TM TOXIC"),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TM,         .special = ITEM_TM_TOXIC,     },
[GB_30_RANDOM_BERRIES] =      {         .name =_("30 RANDOM BERRIES"),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_30_BERRIES,         .special = 0,     },
[GB_LIFE_DEW] =      {         .name =_("TM LIFE DEW"),         .altar = TYPE_NEREID,         .boonType = BOON_TM,         .special = ITEM_TM_LIFE_DEW,     },
[GB_EXP_SHARE] =      {         .name =_("EXP SHARE"),         .altar = TYPE_NEREID,         .boonType = BOON_ITEM,         .special = ITEM_EXP_SHARE,     },
[GB_CHOICE_SCARF] =      {         .name =_("CHOICE SCARF"),         .altar = TYPE_ELDWYRM,         .boonType = BOON_ITEM,         .special = ITEM_CHOICE_SCARF,     },
[GB_LIFE_ORB] =      {         .name =_("LIFE ORB"),         .altar = TYPE_ELDWYRM,         .boonType = BOON_ITEM,         .special = ITEM_LIFE_ORB,     },
[GB_PROTECT] =      {         .name =_("TM PROTECT"),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_PROTECT,     },
[GB_EVIOLITE] =      {         .name =_("EVIOLITE"),         .altar = TYPE_MONOLITH,         .boonType = BOON_ITEM,         .special = ITEM_EVIOLITE,     },
[GB_10X_HYPER_POTION] =      {         .name =_("10X HYPER POTION"),         .altar = TYPE_MONOLITH,         .boonType = BOON_10XITEM,         .special = 0,     },
[GB_SHOCK_SHIELD] =      {         .name =_("SHOCK SHIELD"),         .altar = TYPE_MONOLITH,         .boonType = BOON_ITEM,         .special = ITEM_SHOCK_SHIELD,     },
[GB_FOCUS_SASH] =      {         .name =_("FOCUS SASH"),         .altar = TYPE_WINGED_LION,         .boonType = BOON_ITEM,         .special = ITEM_FOCUS_SASH,     },
[GB_REROLL_INTO_WINGED_LION] =      {         .name =_("REROLL INTO WINGED LION"),         .altar = TYPE_WINGED_LION,         .boonType = BOON_REROLL,         .special = 0,     },
[GB_AROMATHERAPY] =      {         .name =_("TM AROMATHERAPY"),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TM,         .special = ITEM_TM_AROMATHERAPY,     },
[GB_LEECH_SEED] =      {         .name =_("TM LEECH SEED"),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TM,         .special = ITEM_TM_LEECH_SEED,     },
[GB_WORRY_SEED] =      {         .name =_("TM WORRY SEED"),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TM,         .special = ITEM_TM_WORRY_SEED,     },
[GB_TWINEEDLE] =      {         .name =_("TUTOR TWINEEDLE"),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TUTOR,         .special = MOVE_TWINEEDLE,     },
[GB_U_TURN] =      {         .name =_("TM U TURN"),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TM,         .special = ITEM_TM_U_TURN,     },
[GB_VENOM_DRENCH] =      {         .name =_("TM VENOM DRENCH"),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TM,         .special = ITEM_TM_VENOM_DRENCH,     },
[GB_VENOSHOCK] =      {         .name =_("TM VENOSHOCK"),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TM,         .special = ITEM_TM_VENOSHOCK,     },
[GB_BLACK_SLUDGE] =      {         .name =_("BLACK SLUDGE"),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_ITEM,         .special = ITEM_BLACK_SLUDGE,     },
[GB_SHED_SHELL] =      {         .name =_("SHED SHELL"),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_ITEM,         .special = ITEM_SHED_SHELL,     },
[GB_20_TERRAIN_SEEDS] =      {         .name =_("20 TERRAIN SEEDS"),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TERRAIN_SEEDS,         .special = 0,     },
[GB_BIG_ROOT] =      {         .name =_("BIG ROOT"),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_ITEM,         .special = ITEM_BIG_ROOT,     },
[GB_TOXIC_ORB_AND_FLAME_ORB] =      {         .name =_("TOXIC ORB AND FLAME ORB"),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TOXICANDFLAMEORB,         .special = 0,     },
[GB_MIRACLE_SEED] =      {         .name =_("MIRACLE SEED"),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_ITEM,         .special = ITEM_MIRACLE_SEED,     },
[GB_SILVER_POWDER] =      {         .name =_("SILVER POWDER"),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_ITEM,         .special = ITEM_SILVER_POWDER,     },
[GB_POISON_BARB] =      {         .name =_("POISON BARB"),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_ITEM,         .special = ITEM_POISON_BARB,     },
[GB_STICKY_BARB] =      {         .name =_("STICKY BARB"),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_ITEM,         .special = ITEM_STICKY_BARB,     },
[GB_CUT] =      {         .name =_("HM CUT"),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_HM,         .special = ITEM_HM_CUT,     },
[GB_SAFETY_GOGGLES] =      {         .name =_("SAFETY GOGGLES"),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_ITEM,         .special = ITEM_SAFETY_GOGGLES,     },
[GB_AQUA_RING] =      {         .name =_("TM AQUA RING"),         .altar = TYPE_NEREID,         .boonType = BOON_TM,         .special = ITEM_TM_AQUA_RING,     },
[GB_RAIN_DANCE] =      {         .name =_("TM RAIN DANCE"),         .altar = TYPE_NEREID,         .boonType = BOON_TM,         .special = ITEM_TM_RAIN_DANCE,     },
[GB_SOAK] =      {         .name =_("TM SOAK"),         .altar = TYPE_NEREID,         .boonType = BOON_TM,         .special = ITEM_TM_SOAK,     },
[GB_AURORA_VEIL] =      {         .name =_("TM AURORA VEIL"),         .altar = TYPE_NEREID,         .boonType = BOON_TM,         .special = ITEM_TM_AURORA_VEIL,     },
[GB_HAIL] =      {         .name =_("TM HAIL"),         .altar = TYPE_NEREID,         .boonType = BOON_TM,         .special = ITEM_TM_HAIL,     },
[GB_DRAINING_KISS] =      {         .name =_("TM DRAINING KISS"),         .altar = TYPE_NEREID,         .boonType = BOON_TM,         .special = ITEM_TM_DRAINING_KISS,     },
[GB_MONEY] =      {         .name =_("MONEY"),         .altar = TYPE_NEREID,         .boonType = BOON_MONEY,         .special = 10000,     },
[GB_ICE_PUNCH] =      {         .name =_("TUTOR ICE PUNCH"),         .altar = TYPE_NEREID,         .boonType = BOON_TUTOR,         .special = MOVE_ICE_PUNCH,     },
[GB_FLAME_CHARGE] =      {         .name =_("TM FLAME CHARGE"),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TM,         .special = ITEM_TM_FLAME_CHARGE,     },
[GB_SUNNY_DAY] =      {         .name =_("TM SUNNY DAY"),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TM,         .special = ITEM_TM_SUNNY_DAY,     },
[GB_FIRE_PUNCH] =      {         .name =_("TUTOR FIRE PUNCH"),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TUTOR,         .special = MOVE_FIRE_PUNCH,     },
[GB_THUNDER_PUNCH] =      {         .name =_("TUTOR THUNDER PUNCH"),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TUTOR,         .special = MOVE_THUNDER_PUNCH,     },
[GB_EXPLOSION] =      {         .name =_("TUTOR EXPLOSION"),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TUTOR,         .special = MOVE_EXPLOSION,     },
[GB_DRAGON_CHEER] =      {         .name =_("TM DRAGON CHEER"),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TM,         .special = ITEM_TM_DRAGON_CHEER,     },
[GB_EXPERT_BELT] =      {         .name =_("EXPERT BELT"),         .altar = TYPE_ELDWYRM,         .boonType = BOON_ITEM,         .special = ITEM_EXPERT_BELT,     },
[GB_CHARCOAL] =      {         .name =_("CHARCOAL"),         .altar = TYPE_ELDWYRM,         .boonType = BOON_ITEM,         .special = ITEM_CHARCOAL,     },
[GB_MAGNET] =      {         .name =_("MAGNET"),         .altar = TYPE_ELDWYRM,         .boonType = BOON_ITEM,         .special = ITEM_MAGNET,     },
[GB_DRAGON_FANG] =      {         .name =_("DRAGON FANG"),         .altar = TYPE_ELDWYRM,         .boonType = BOON_ITEM,         .special = ITEM_DRAGON_FANG,     },
[GB_DRAGON_BREATH] =      {         .name =_("TUTOR DRAGON BREATH"),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TUTOR,         .special = MOVE_DRAGON_BREATH,     },
[GB_BATON_PASS] =      {         .name =_("TM BATON PASS"),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_BATON_PASS,     },
[GB_ENCORE] =      {         .name =_("TM ENCORE"),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_ENCORE,     },
[GB_ENDEAVOR] =      {         .name =_("TM ENDEAVOR"),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_ENDEAVOR,     },
[GB_HIDDEN_POWER] =      {         .name =_("TM HIDDEN POWER"),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_HIDDEN_POWER,     },
[GB_PAIN_SPLIT] =      {         .name =_("TM PAIN SPLIT"),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_PAIN_SPLIT,     },
[GB_SLEEP_TALK] =      {         .name =_("TM SLEEP TALK"),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_SLEEP_TALK,     },
[GB_SUBSTITUTE] =      {         .name =_("TM SUBSTITUTE"),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_SUBSTITUTE,     },
[GB_WEATHER_BALL] =      {         .name =_("TM WEATHER BALL"),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_WEATHER_BALL,     },
[GB_WISH] =      {         .name =_("TM WISH"),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_WISH,     },
[GB_CALM_MIND] =      {         .name =_("TM CALM MIND"),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_CALM_MIND,     },
[GB_LIGHT_SCREEN] =      {         .name =_("TM LIGHT SCREEN"),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_LIGHT_SCREEN,     },
[GB_PSYCHO_CUT] =      {         .name =_("TM PSYCHO CUT"),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_PSYCHO_CUT,     },
[GB_REFLECT] =      {         .name =_("TM REFLECT"),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_REFLECT,     },
[GB_TRICK] =      {         .name =_("TM TRICK"),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_TRICK,     },
[GB_TRICK_ROOM] =      {         .name =_("TM TRICK ROOM"),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_TRICK_ROOM,     },
[GB_CURSE] =      {         .name =_("TM CURSE"),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_CURSE,     },
[GB_DESTINY_BOND] =      {         .name =_("TM DESTINY BOND"),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_DESTINY_BOND,     },
[GB_HONE_CLAWS] =      {         .name =_("TM HONE CLAWS"),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_HONE_CLAWS,     },
[GB_TAUNT] =      {         .name =_("TM TAUNT"),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_TAUNT,     },
[GB_SOFT_BOILED] =      {         .name =_("TUTOR SOFT BOILED"),         .altar = TYPE_DSOTM,         .boonType = BOON_TUTOR,         .special = MOVE_SOFT_BOILED,     },
[GB_COPYCAT] =      {         .name =_("TUTOR COPYCAT"),         .altar = TYPE_DSOTM,         .boonType = BOON_TUTOR,         .special = MOVE_COPYCAT,     },
[GB_LASER_FOCUS] =      {         .name =_("TUTOR LASER FOCUS"),         .altar = TYPE_DSOTM,         .boonType = BOON_TUTOR,         .special = MOVE_LASER_FOCUS,     },
[GB_POWER_SPLIT] =      {         .name =_("TUTOR POWER SPLIT"),         .altar = TYPE_DSOTM,         .boonType = BOON_TUTOR,         .special = MOVE_POWER_SPLIT,     },
[GB_BODY_SLAM] =      {         .name =_("TUTOR BODY SLAM"),         .altar = TYPE_DSOTM,         .boonType = BOON_TUTOR,         .special = MOVE_BODY_SLAM,     },
[GB_COUNTER] =      {         .name =_("TUTOR COUNTER"),         .altar = TYPE_DSOTM,         .boonType = BOON_TUTOR,         .special = MOVE_COUNTER,     },
[GB_DEFENSE_CURL] =      {         .name =_("TUTOR DEFENSE CURL"),         .altar = TYPE_DSOTM,         .boonType = BOON_TUTOR,         .special = MOVE_DEFENSE_CURL,     },
[GB_DREAM_EATER] =      {         .name =_("TUTOR DREAM EATER"),         .altar = TYPE_DSOTM,         .boonType = BOON_TUTOR,         .special = MOVE_DREAM_EATER,     },
[GB_WIZARD_CAPE] =      {         .name =_("WIZARD CAPE"),         .altar = TYPE_DSOTM,         .boonType = BOON_ITEM,         .special = ITEM_DAMAGE_BOUNCEABLES,     },
[GB_ROCK_SMASH] =      {         .name =_("HM ROCK SMASH"),         .altar = TYPE_MONOLITH,         .boonType = BOON_HM,         .special = ITEM_HM_ROCK_SMASH,     },
[GB_STRENGTH] =      {         .name =_("HM STRENGTH"),         .altar = TYPE_MONOLITH,         .boonType = BOON_HM,         .special = ITEM_HM_STRENGTH,     },
[GB_AUTOTOMIZE] =      {         .name =_("TM AUTOTOMIZE"),         .altar = TYPE_MONOLITH,         .boonType = BOON_TM,         .special = ITEM_TM_AUTOTOMIZE,     },
[GB_STEEL_BEAM] =      {         .name =_("TM STEEL BEAM"),         .altar = TYPE_MONOLITH,         .boonType = BOON_TM,         .special = ITEM_TM_STEEL_BEAM,     },
[GB_IRON_DEFENSE] =      {         .name =_("TM IRON DEFENSE"),         .altar = TYPE_MONOLITH,         .boonType = BOON_TM,         .special = ITEM_TM_IRON_DEFENSE,     },
[GB_ANCIENT_POWER] =      {         .name =_("TM ANCIENT POWER"),         .altar = TYPE_MONOLITH,         .boonType = BOON_TM,         .special = ITEM_TM_ANCIENT_POWER,     },
[GB_SANDSTORM] =      {         .name =_("TM SANDSTORM"),         .altar = TYPE_MONOLITH,         .boonType = BOON_TM,         .special = ITEM_TM_SANDSTORM,     },
[GB_DIG] =      {         .name =_("TM DIG"),         .altar = TYPE_MONOLITH,         .boonType = BOON_TM,         .special = ITEM_TM_DIG,     },
[GB_SAND_TOMB] =      {         .name =_("TM SAND TOMB"),         .altar = TYPE_MONOLITH,         .boonType = BOON_TM,         .special = ITEM_TM_SAND_TOMB,     },
[GB_ROCK_SLIDE_TUTOR] =      {         .name =_("TUTOR ROCK SLIDE"),         .altar = TYPE_MONOLITH,         .boonType = BOON_TUTOR,         .special = MOVE_ROCK_SLIDE,     },
[GB_ROLLOUT] =      {         .name =_("TUTOR ROLLOUT"),         .altar = TYPE_MONOLITH,         .boonType = BOON_TUTOR,         .special = MOVE_ROLLOUT,     },
[GB_MUD_SLAP] =      {         .name =_("TUTOR MUD SLAP"),         .altar = TYPE_MONOLITH,         .boonType = BOON_TUTOR,         .special = MOVE_MUD_SLAP,     },
[GB_ROCKY_HELMET] =      {         .name =_("ROCKY HELMET"),         .altar = TYPE_MONOLITH,         .boonType = BOON_ITEM,         .special = ITEM_ROCKY_HELMET,     },
[GB_ASSAULT_VEST] =      {         .name =_("ASSAULT VEST"),         .altar = TYPE_MONOLITH,         .boonType = BOON_ITEM,         .special = ITEM_ASSAULT_VEST,     },
[GB_HEAVY_DUTY_BOOTS] =      {         .name =_("HEAVY DUTY BOOTS"),         .altar = TYPE_MONOLITH,         .boonType = BOON_ITEM,         .special = ITEM_HEAVY_DUTY_BOOTS,     },
[GB_10X_FULL_RESTORE] =      {         .name =_("10X FULL RESTORE"),         .altar = TYPE_MONOLITH,         .boonType = BOON_10XITEM,         .special = ITEM_FULL_RESTORE,     },
[GB_COVERT_CLOAK] =      {         .name =_("COVERT CLOAK"),         .altar = TYPE_MONOLITH,         .boonType = BOON_ITEM,         .special = ITEM_COVERT_CLOAK,     },
[GB_10X_PP_UP] =      {         .name =_("10X PP UP"),         .altar = TYPE_MONOLITH,         .boonType = BOON_10XITEM,         .special = ITEM_PP_UP,     },
[GB_BULK_UP] =      {         .name =_("TM BULK UP"),         .altar = TYPE_WINGED_LION,         .boonType = BOON_TM,         .special = ITEM_TM_BULK_UP,     },
[GB_COACHING] =      {         .name =_("TM COACHING"),         .altar = TYPE_WINGED_LION,         .boonType = BOON_TM,         .special = ITEM_TM_COACHING,     },
[GB_POWER_UP_PUNCH] =      {         .name =_("TM POWER UP PUNCH"),         .altar = TYPE_WINGED_LION,         .boonType = BOON_TM,         .special = ITEM_TM_POWER_UP_PUNCH,     },
[GB_UPPER_HAND] =      {         .name =_("TM UPPER HAND"),         .altar = TYPE_WINGED_LION,         .boonType = BOON_TM,         .special = ITEM_TM_UPPER_HAND,     },
[GB_ROOST] =      {         .name =_("TM ROOST"),         .altar = TYPE_WINGED_LION,         .boonType = BOON_TM,         .special = ITEM_TM_ROOST,     },
[GB_TAILWIND] =      {         .name =_("TM TAILWIND"),         .altar = TYPE_WINGED_LION,         .boonType = BOON_TM,         .special = ITEM_TM_TAILWIND,     },
[GB_WHIRLWIND] =      {         .name =_("TM WHIRLWIND"),         .altar = TYPE_WINGED_LION,         .boonType = BOON_TM,         .special = ITEM_TM_WHIRLWIND,     },
[GB_SEISMIC_TOSS] =      {         .name =_("TUTOR SEISMIC TOSS"),         .altar = TYPE_WINGED_LION,         .boonType = BOON_TUTOR,         .special = MOVE_SEISMIC_TOSS,     },
[GB_FOCUS_BAND] =      {         .name =_("FOCUS BAND"),         .altar = TYPE_WINGED_LION,         .boonType = BOON_ITEM,         .special = ITEM_FOCUS_BAND,     },
[GB_SHARP_BEAK] =      {         .name =_("SHARP BEAK"),         .altar = TYPE_WINGED_LION,         .boonType = BOON_ITEM,         .special = ITEM_SHARP_BEAK,     },
[GB_PUNCHING_GLOVE] =      {         .name =_("PUNCHING GLOVE"),         .altar = TYPE_WINGED_LION,         .boonType = BOON_ITEM,         .special = ITEM_PUNCHING_GLOVE,     },
[GB_EJECT_PACK] =      {         .name =_("EJECT PACK"),         .altar = TYPE_WINGED_LION,         .boonType = BOON_ITEM,         .special = ITEM_EJECT_PACK,     },
[GB_EJECT_BUTTON] =      {         .name =_("EJECT BUTTON"),         .altar = TYPE_WINGED_LION,         .boonType = BOON_ITEM,         .special = ITEM_EJECT_BUTTON,     },
[GB_RED_CARD] =      {         .name =_("RED CARD"),         .altar = TYPE_WINGED_LION,         .boonType = BOON_ITEM,         .special = ITEM_RED_CARD,     },
[GB_AIR_BALLOON] =      {         .name =_("AIR BALLOON"),         .altar = TYPE_WINGED_LION,         .boonType = BOON_ITEM,         .special = ITEM_AIR_BALLOON,     },
[GB_FLYING_GEM] =      {         .name =_("FLYING GEM"),         .altar = TYPE_WINGED_LION,         .boonType = BOON_ITEM,         .special = ITEM_FLYING_GEM,     },
[GB_TUTOR_METRONOME_AND_REROLL] =      {         .name =_("TUTOR METRONOME AND REROLL"),         .altar = TYPE_WINGED_LION,         .boonType = BOON_REROLLPLUSTUTOR,         .special = MOVE_METRONOME,     },
[GB_FLAIL] =      {         .name =_("TUTOR FLAIL"),         .altar = TYPE_WINGED_LION,         .boonType = BOON_TUTOR,         .special = MOVE_FLAIL,     },
[GB_ENDURE] =      {         .name =_("TUTOR ENDURE"),         .altar = TYPE_WINGED_LION,         .boonType = BOON_TUTOR,         .special = MOVE_ENDURE,     },
[GB_10X_X_SPEED] =      {         .name =_("10X X SPEED"),         .altar = TYPE_WINGED_LION,         .boonType = BOON_10XITEM,         .special = ITEM_X_SPEED,     },
[GB_FALSE_SWIPE] =      {         .name =_("TUTOR FALSE SWIPE"),         .altar = TYPE_COLOURLESS,         .boonType = BOON_TUTOR,         .special = MOVE_FALSE_SWIPE,     },
[GB_MEGA_KICK] =      {         .name =_("TUTOR MEGA KICK"),         .altar = TYPE_COLOURLESS,         .boonType = BOON_TUTOR,         .special = MOVE_MEGA_KICK,     },
[GB_MEGA_PUNCH] =      {         .name =_("TUTOR MEGA PUNCH"),         .altar = TYPE_COLOURLESS,         .boonType = BOON_TUTOR,         .special = MOVE_MEGA_PUNCH,     },
[GB_SWAGGER] =      {         .name =_("TUTOR SWAGGER"),         .altar = TYPE_COLOURLESS,         .boonType = BOON_TUTOR,         .special = MOVE_SWAGGER,     },
[GB_SWIFT] =      {         .name =_("TUTOR SWIFT"),         .altar = TYPE_COLOURLESS,         .boonType = BOON_TUTOR,         .special = MOVE_SWIFT,     },
[GB_PSYCH_UP] =      {         .name =_("TUTOR PSYCH UP"),         .altar = TYPE_COLOURLESS,         .boonType = BOON_TUTOR,         .special = MOVE_PSYCH_UP,     },
[GB_SNORE] =      {         .name =_("TUTOR SNORE"),         .altar = TYPE_COLOURLESS,         .boonType = BOON_TUTOR,         .special = MOVE_SNORE,     },
[GB_FLASH] =      {         .name =_("HM FLASH"),         .altar = TYPE_COLOURLESS,         .boonType = BOON_HM,         .special = ITEM_HM_FLASH,     },
[GB_GIGA_DRAIN] =      {         .name =_("TM GIGA DRAIN"),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TM,         .special = ITEM_TM_GIGA_DRAIN,     },
[GB_SOLAR_BEAM] =      {         .name =_("TM SOLAR BEAM"),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TM,         .special = ITEM_TM_SOLAR_BEAM,     },
[GB_STICKY_WEB] =      {         .name =_("TM STICKY WEB"),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TM,         .special = ITEM_TM_STICKY_WEB,     },
[GB_X_SCISSOR] =      {         .name =_("TM X SCISSOR"),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TM,         .special = ITEM_TM_X_SCISSOR,     },
[GB_NATURE_POWER] =      {         .name =_("HM NATURE POWER"),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_HM,         .special = ITEM_HM_NATURE_POWER,     },
[GB_WATERFALL] =      {         .name =_("HM WATERFALL"),         .altar = TYPE_NEREID,         .boonType = BOON_HM,         .special = ITEM_HM_WATERFALL,     },
[GB_DIVE] =      {         .name =_("HM DIVE"),         .altar = TYPE_NEREID,         .boonType = BOON_HM,         .special = ITEM_HM_DIVE,     },
[GB_BLIZZARD] =      {         .name =_("TM BLIZZARD"),         .altar = TYPE_NEREID,         .boonType = BOON_TM,         .special = ITEM_TM_BLIZZARD,     },
[GB_TRIPLE_AXEL] =      {         .name =_("TM TRIPLE AXEL"),         .altar = TYPE_NEREID,         .boonType = BOON_TM,         .special = ITEM_TM_TRIPLE_AXEL,     },
[GB_DAZZLING_GLEAM] =      {         .name =_("TM DAZZLING GLEAM"),         .altar = TYPE_NEREID,         .boonType = BOON_TM,         .special = ITEM_TM_DAZZLING_GLEAM,     },
[GB_FROST_BREATH] =      {         .name =_("TUTOR FROST BREATH"),         .altar = TYPE_NEREID,         .boonType = BOON_TUTOR,         .special = MOVE_FROST_BREATH,     },
[GB_MYSTIC_WATER] =      {         .name =_("MYSTIC WATER"),         .altar = TYPE_NEREID,         .boonType = BOON_ITEM,         .special = ITEM_MYSTIC_WATER,     },
[GB_NEVER_MELT_ICE] =      {         .name =_("NEVER MELT ICE"),         .altar = TYPE_NEREID,         .boonType = BOON_ITEM,         .special = ITEM_NEVER_MELT_ICE,     },
[GB_FAIRY_FEATHER] =      {         .name =_("FAIRY FEATHER"),         .altar = TYPE_NEREID,         .boonType = BOON_ITEM,         .special = ITEM_FAIRY_FEATHER,     },
[GB_LUCKY_EGG] =      {         .name =_("LUCKY EGG"),         .altar = TYPE_NEREID,         .boonType = BOON_ITEM,         .special = ITEM_LUCKY_EGG,     },
[GB_BLAZE_KICK] =      {         .name =_("TM BLAZE KICK"),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TM,         .special = ITEM_TM_BLAZE_KICK,     },
[GB_FLAMETHROWER] =      {         .name =_("TM FLAMETHROWER"),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TM,         .special = ITEM_TM_FLAMETHROWER,     },
[GB_OVERHEAT] =      {         .name =_("TM OVERHEAT"),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TM,         .special = ITEM_TM_OVERHEAT,     },
[GB_WILL_O_WISP] =      {         .name =_("TM WILL O WISP"),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TM,         .special = ITEM_TM_WILL_O_WISP,     },
[GB_THUNDER] =      {         .name =_("TM THUNDER"),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TM,         .special = ITEM_TM_THUNDER,     },
[GB_THUNDERBOLT] =      {         .name =_("TM THUNDERBOLT"),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TM,         .special = ITEM_TM_THUNDERBOLT,     },
[GB_THUNDER_WAVE] =      {         .name =_("TM THUNDER WAVE"),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TM,         .special = ITEM_TM_THUNDER_WAVE,     },
[GB_VOLT_SWITCH] =      {         .name =_("TM VOLT SWITCH"),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TM,         .special = ITEM_TM_VOLT_SWITCH,     },
[GB_ZING_ZAP] =      {         .name =_("TM ZING ZAP"),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TM,         .special = ITEM_TM_ZING_ZAP,     },
[GB_DRAGON_CLAW] =      {         .name =_("TM DRAGON CLAW"),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TM,         .special = ITEM_TM_DRAGON_CLAW,     },
[GB_SWORDS_DANCE] =      {         .name =_("TM SWORDS DANCE"),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_SWORDS_DANCE,     },
[GB_REST] =      {         .name =_("TM REST"),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_REST,     },
[GB_PHANTOM_FORCE] =      {         .name =_("TM PHANTOM FORCE"),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_PHANTOM_FORCE,     },
[GB_SHADOW_BALL] =      {         .name =_("TM SHADOW BALL"),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_SHADOW_BALL,     },
[GB_DARK_PULSE] =      {         .name =_("TM DARK PULSE"),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_DARK_PULSE,     },
[GB_KNOCK_OFF] =      {         .name =_("TM KNOCK OFF"),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_KNOCK_OFF,     },
[GB_NASTY_PLOT] =      {         .name =_("TM NASTY PLOT"),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_NASTY_PLOT,     },
[GB_SUCKER_PUNCH] =      {         .name =_("TM SUCKER PUNCH"),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_SUCKER_PUNCH,     },
[GB_IRON_HEAD] =      {         .name =_("TM IRON HEAD"),         .altar = TYPE_MONOLITH,         .boonType = BOON_TM,         .special = ITEM_TM_IRON_HEAD,     },
[GB_METEOR_BEAM] =      {         .name =_("TM METEOR BEAM"),         .altar = TYPE_MONOLITH,         .boonType = BOON_TM,         .special = ITEM_TM_METEOR_BEAM,     },
[GB_ROCK_SLIDE] =      {         .name =_("TM ROCK SLIDE"),         .altar = TYPE_MONOLITH,         .boonType = BOON_TM,         .special = ITEM_TM_ROCK_SLIDE,     },
[GB_SCORCHING_SANDS] =      {         .name =_("TM SCORCHING SANDS"),         .altar = TYPE_MONOLITH,         .boonType = BOON_TM,         .special = ITEM_TM_SCORCHING_SANDS,     },
[GB_10X_IRON_10X_HP_UP_10X_ZINC] =      {         .name =_("10X IRON, 10X HP UP, 10X ZINC"),         .altar = TYPE_MONOLITH,         .boonType = BOON_10IRON10HPUP10ZINC,         .special = 0,     },
[GB_BRICK_BREAK] =      {         .name =_("TM BRICK BREAK"),         .altar = TYPE_WINGED_LION,         .boonType = BOON_TM,         .special = ITEM_TM_BRICK_BREAK,     },
[GB_DRAIN_PUNCH] =      {         .name =_("TM DRAIN PUNCH"),         .altar = TYPE_WINGED_LION,         .boonType = BOON_TM,         .special = ITEM_TM_DRAIN_PUNCH,     },
[GB_ACROBATICS] =      {         .name =_("TM ACROBATICS"),         .altar = TYPE_WINGED_LION,         .boonType = BOON_TM,         .special = ITEM_TM_ACROBATICS,     },
[GB_AIR_SLASH] =      {         .name =_("TM AIR SLASH"),         .altar = TYPE_WINGED_LION,         .boonType = BOON_TM,         .special = ITEM_TM_AIR_SLASH,     },
[GB_BODY_PRESS] =      {         .name =_("TUTOR BODY PRESS"),         .altar = TYPE_WINGED_LION,         .boonType = BOON_TUTOR,         .special = MOVE_BODY_PRESS,     },
[GB_STRENGTH_RARER] =      {         .name =_("HM STRENGTH"),         .altar = TYPE_COLOURLESS,         .boonType = BOON_HM,         .special = ITEM_HM_STRENGTH,     },
[GB_BULLET_SEED] =      {         .name =_("TM BULLET SEED"),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TM,         .special = ITEM_TM_BULLET_SEED,     },
[GB_ENERGY_BALL] =      {         .name =_("TM ENERGY BALL"),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TM,         .special = ITEM_TM_ENERGY_BALL,     },
[GB_LUNGE] =      {         .name =_("TM LUNGE"),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TM,         .special = ITEM_TM_LUNGE,     },
[GB_POLLEN_PUFF] =      {         .name =_("TM POLLEN PUFF"),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TM,         .special = ITEM_TM_POLLEN_PUFF,     },
[GB_SLUDGE_BOMB] =      {         .name =_("TM SLUDGE BOMB"),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TM,         .special = ITEM_TM_SLUDGE_BOMB,     },
[GB_SURF] =      {         .name =_("HM SURF"),         .altar = TYPE_NEREID,         .boonType = BOON_HM,         .special = ITEM_HM_SURF,     },
[GB_ICE_BEAM] =      {         .name =_("TM ICE BEAM"),         .altar = TYPE_NEREID,         .boonType = BOON_TM,         .special = ITEM_TM_ICE_BEAM,     },
[GB_PLAY_ROUGH] =      {         .name =_("TM PLAY ROUGH"),         .altar = TYPE_NEREID,         .boonType = BOON_TM,         .special = ITEM_TM_PLAY_ROUGH,     },
[GB_MORE_MONEY] =      {         .name =_("MORE MONEY"),         .altar = TYPE_NEREID,         .boonType = BOON_MONEY,         .special = 30000,     },
[GB_DRACO_METEOR] =      {         .name =_("TM DRACO METEOR"),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TM,         .special = ITEM_TM_DRACO_METEOR,     },
[GB_CHOICE_SPECS] =      {         .name =_("CHOICE SPECS"),         .altar = TYPE_ELDWYRM,         .boonType = BOON_ITEM,         .special = ITEM_CHOICE_SPECS,     },
[GB_CHOICE_BAND] =      {         .name =_("CHOICE BAND"),         .altar = TYPE_ELDWYRM,         .boonType = BOON_ITEM,         .special = ITEM_CHOICE_BAND,     },
[GB_HYPER_BEAM] =      {         .name =_("TM HYPER BEAM"),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_HYPER_BEAM,     },
[GB_RETURN] =      {         .name =_("TM RETURN"),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_RETURN,     },
[GB_PSYCHIC] =      {         .name =_("TM PSYCHIC"),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_PSYCHIC,     },
[GB_DOUBLE_EDGE] =      {         .name =_("TUTOR DOUBLE EDGE"),         .altar = TYPE_DSOTM,         .boonType = BOON_TUTOR,         .special = MOVE_DOUBLE_EDGE,     },
[GB_STONE_EDGE] =      {         .name =_("TM STONE EDGE"),         .altar = TYPE_MONOLITH,         .boonType = BOON_TM,         .special = ITEM_TM_STONE_EDGE,     },
[GB_EARTHQUAKE] =      {         .name =_("TM EARTHQUAKE"),         .altar = TYPE_MONOLITH,         .boonType = BOON_TM,         .special = ITEM_TM_EARTHQUAKE,     },
[GB_10X_REVIVE] =      {         .name =_("10X REVIVE"),         .altar = TYPE_MONOLITH,         .boonType = BOON_10XITEM,         .special = ITEM_REVIVE,     },
[GB_FOCUS_BLAST] =      {         .name =_("TM FOCUS BLAST"),         .altar = TYPE_WINGED_LION,         .boonType = BOON_TM,         .special = ITEM_TM_FOCUS_BLAST,     },
};


static const enum GauntletTypes GetGauntletAltar(u32 id)
{
    return BoonList[id].altar;
}

static const enum BoonType GetGauntletBoonType(u32 id)
{
    return BoonList[id].boonType;
}

static const enum BoonType GetGauntletSpecial(u32 id)
{
    return BoonList[id].special;
}

static bool8 dynmultipushFromGauntletVar(u32 id)
{
    const u8 *name = BoonList[id].name;

    Script_RequestEffects(SCREFF_V1 | SCREFF_HARDWARE);

    u8 *nameBuffer = Alloc(100);
    struct ListMenuItem listItem;
    StringExpandPlaceholders(nameBuffer, name);
    listItem.name = nameBuffer;
    listItem.id = id;
    MultichoiceDynamic_PushElement(listItem);
    return FALSE;
}

#define NUM_GAUNTLET_DEITIES 6
#define NUM_GAUNTLET_OPTION_COLOURS 7

void ScrCmd_DoGauntletBoonList(struct ScriptContext *ctx)
{
   enum ItemPool itemPool = ScriptReadByte(ctx);
   switch (itemPool){
      default:
      case GAUNTLET_ITEM_POOL_LOW: DoGauntletBoonList(50, 25, 12, 1); return;
      case GAUNTLET_ITEM_POOL_MED: DoGauntletBoonList(25, 25, 25, 1); return;
      case GAUNTLET_ITEM_POOL_HIGH: DoGauntletBoonList(15, 25, 35, 5); return;
      case GAUNTLET_ITEM_POOL_END:  DoGauntletBoonList(15, 25, 25, 35); return;
   }
   return;
}

void ScrCmd_LoadGauntletBoonInVarResultToboosboog(struct ScriptContext *ctx)
{
    u8 id = VarGet(VAR_RESULT);

    enum BoonType boon = BoonList[id].boonType;
    VarSet(VAR_0x8004, 1);// how it is handled in giving item
    VarSet(VAR_0x8005, BoonList[id].special);//item, flag, etc.
    VarSet(VAR_0x8006, BoonList[id].boonType);//
    VarSet(VAR_0x8008, BoonList[id].altar);
    assertf(FALSE, "boontype=%d", boon);

    VarSet(VAR_0x8009, boon); // Used by the switch we returnto after dynmultistack
    switch (boon)
    {
        case BOON_30_BERRIES:
        case BOON_TERRAIN_SEEDS:
            VarSet(VAR_0x8004, 5);break;
        case BOON_10XITEM:
        case BOON_XATTACKXSPECIAL:
        case BOON_XDEFXSPDEF:
        case BOON_10IRON10HPUP10ZINC:
            VarSet(VAR_0x8004, 10);break;
        case BOON_FLAG:
        case BOON_TUTOR:
        case BOON_MONEY:
        case BOON_3RANDOMTMS:
        case BOON_REROLL:
        case BOON_REROLLPLUSTUTOR:
        case BOON_TYPE_LENGTH:
        case BOON_ITEM:
        case BOON_TM:
        case BOON_HM:
        default:
            break;
    }
    return;
}

#define GAUNTLET_MENU_OPTIONS 4

#define BIT_SAPH 0b11
#define BIT_NEREID 0b1100
#define BIT_ELDWYRM 0b110000
#define BIT_DSOTM 0b11000000
#define BIT_MONOLITH 0b11
#define BIT_WINGED_LION 0b11100
#define BIT_CAPPED 0b100000

void AddDevotionTo0x8008(void)
{
    enum GauntletTypes altar = VarGet(VAR_0x8008);
    u32 isCapped = 0;
    u32 devotions1 = VarGet(VAR_GAUNTLET_BITFIELD_1);
    u32 devotions2 = VarGet(VAR_GAUNTLET_BITFIELD_2);

    assertf(FALSE, "dev1=%d", devotions1);
    assertf(FALSE, "dev2=%d", devotions2);

    u8 playerDevotions[TYPE_DEVOTION_LENGTH] =
    {
        [TYPE_SAPROTROPH] = devotions1 & BIT_SAPH,
        [TYPE_NEREID] = (devotions1 & BIT_NEREID) >> 2,
        [TYPE_ELDWYRM] = (devotions1 & BIT_ELDWYRM) >> 4,
        [TYPE_DSOTM] = (devotions1 & BIT_DSOTM) >> 6,
        [TYPE_MONOLITH] = devotions2 & BIT_MONOLITH,
        [TYPE_WINGED_LION] = (devotions2 & BIT_WINGED_LION) >> 2,
    };
    u32 cap = 3;
    if (altar == TYPE_WINGED_LION)
        cap = 7;
    if (playerDevotions[altar] <= cap)
         playerDevotions[altar] = playerDevotions[altar]+1;

    u32 i;
    for (i=0; i<TYPE_COLOURLESS; i++)
    {
        if (playerDevotions[i] > 0) 
            isCapped++;
    }
    if (isCapped > 3)
        isCapped = BIT_CAPPED;
    else
        isCapped = 0;

    VarSet(VAR_GAUNTLET_BITFIELD_1, (playerDevotions[TYPE_SAPROTROPH] | playerDevotions[TYPE_NEREID] << 2 | playerDevotions[TYPE_ELDWYRM] <<4 | playerDevotions[TYPE_DSOTM]<<6));
    VarSet(VAR_GAUNTLET_BITFIELD_2, (playerDevotions[TYPE_MONOLITH] |  playerDevotions[TYPE_WINGED_LION]<<2 | isCapped));
    return;
}



 
static void DoGauntletBoonList(u8 stapleWeight, u8 commonWeight, u8 rareWeight, u8 epicWeight)
{
    u32 devotions1 = VarGet(VAR_GAUNTLET_BITFIELD_1);
    u32 devotions2 = VarGet(VAR_GAUNTLET_BITFIELD_2);

    u8 playerDevotions[TYPE_DEVOTION_LENGTH] =
    {
        [TYPE_SAPROTROPH] = devotions1 & BIT_SAPH,
        [TYPE_NEREID] = (devotions1 & BIT_NEREID) >> 2,
        [TYPE_ELDWYRM] = (devotions1 & BIT_ELDWYRM) >> 4,
        [TYPE_DSOTM] = (devotions1 & BIT_DSOTM) >> 6,
        [TYPE_MONOLITH] = devotions2 & BIT_MONOLITH,
        [TYPE_WINGED_LION] = (devotions2 & BIT_WINGED_LION) >> 2,
    };
    bool32 isCapped = devotions2 & 0b100000;
    u8 MultichoiceOptions[4] = {0, 0, 0, 0};
    u8 devotion_weight[4] = {20, 20, 20, 20};
    u8 rarity_weight[4] = {stapleWeight, commonWeight, rareWeight, epicWeight};

    if (isCapped)
        devotion_weight[1] = 0;

    for (u32 menuNum=0; menuNum < GAUNTLET_MENU_OPTIONS; menuNum++)
    {
        enum GauntletRarity rarity = RandomWeightedIndex(rarity_weight, 4);// of max devotion
        u32 devotionNeeded = RandomWeightedIndex(devotion_weight, 4);// of max devotion
        u32 i=0;
        enum GauntletTypes deityChosen = TYPE_COLOURLESS;
        do
        {
            enum GauntletTypes deity = Random() % TYPE_DEVOTION_LENGTH;
            if (playerDevotions[deity] >= devotionNeeded)
            {
                deityChosen = deity;
                break;
            }
            i++;
        } while (i < 20); // 2% chance we miss it lmao.

        if (isCapped)
        {
        do
        {
            enum GauntletTypes deity = Random() % TYPE_DEVOTION_LENGTH;
            if (playerDevotions[deity] >= 1)
            {
                deityChosen = deity;
                break;
            }
            i++;
        } while (i < 5); // 2% chance we miss it lmao.
        }
 

        u32 id = GetGauntletBoon(deityChosen, rarity, MultichoiceOptions);//give up on that!
        dynmultipushFromGauntletVar(id);

        MultichoiceOptions[menuNum] = id;
    }
}


static u8 GetGauntletBoon(enum GauntletTypes type, enum GauntletRarity rarity, u8 MultichoiceOptions[4])
{
    u32 choice1 = VarGet(VAR_GAUNTLET_1);
    u32 choice2 = VarGet(VAR_GAUNTLET_2);
    u32 choice3 = VarGet(VAR_GAUNTLET_3);
    u32 choice4 = VarGet(VAR_GAUNTLET_4);
    u32 choice5 = VarGet(VAR_GAUNTLET_5);
    u32 choice6 = VarGet(VAR_GAUNTLET_6);
    u32 choice7 = VarGet(VAR_GAUNTLET_7);
    u32 choice8 = VarGet(VAR_GAUNTLET_8);
    u32 i = 0;
    do {
        switch (type)
        {
        case TYPE_SAPROTROPH:
            switch (rarity)
            {
            default:
            case RARITY_STAPLE:
                i = Random() % (NEREID_STAPLE); break;
            case RARITY_COMMON:
                i = SAPROTROPH_COMMON + Random() % (NEREID_COMMON - SAPROTROPH_COMMON); break;
            case RARITY_RARE:
                i = SAPROTROPH_RARE + Random() % (NEREID_RARE - SAPROTROPH_RARE); break;
            case RARITY_EPIC:
                i = SAPROTROPH_EPIC + Random() % (NEREID_EPIC - SAPROTROPH_EPIC); break;
            }
            break;

        case TYPE_NEREID:
            switch (rarity)
            {
            default:
            case RARITY_STAPLE:
                i = NEREID_STAPLE + Random() % (ELDWYRM_STAPLE - NEREID_STAPLE); break;
            case RARITY_COMMON:
                i = NEREID_COMMON + Random() % (ELDWYRM_COMMON - NEREID_COMMON); break;
            case RARITY_RARE:
                i = NEREID_RARE + Random() % (ELDWYRM_RARE - NEREID_RARE); break;
            case RARITY_EPIC:
                i = NEREID_EPIC + Random() % (ELDWYRM_EPIC - NEREID_EPIC); break;
            }
            break;

        case TYPE_ELDWYRM:
            switch (rarity)
            {
            default:
            case RARITY_STAPLE:
                i = ELDWYRM_STAPLE + Random() % (DSOTM_STAPLE - ELDWYRM_STAPLE); break;
            case RARITY_COMMON:
                i = ELDWYRM_COMMON + Random() % (DSOTM_COMMON - ELDWYRM_COMMON); break;
            case RARITY_RARE:
                i = ELDWYRM_RARE + Random() % (DSOTM_RARE - ELDWYRM_RARE); break;
            case RARITY_EPIC:
                i = ELDWYRM_EPIC + Random() % (DSOTM_EPIC - ELDWYRM_EPIC); break;
            }
            break;
        case TYPE_DSOTM:
            switch (rarity)
            {
            default:
            case RARITY_STAPLE:
                i = DSOTM_STAPLE + Random() % (MONOLITH_STAPLE - DSOTM_STAPLE); break;
            case RARITY_COMMON:
                i = DSOTM_COMMON + Random() % (MONOLITH_COMMON - DSOTM_COMMON); break;
            case RARITY_RARE:
                i = DSOTM_RARE + Random() % (MONOLITH_RARE - DSOTM_RARE); break;
            case RARITY_EPIC:
                i = DSOTM_EPIC + Random() % (MONOLITH_EPIC - DSOTM_EPIC); break;
            }
            break;
        case TYPE_MONOLITH:
            switch (rarity)
            {
            default:
            case RARITY_STAPLE:
                i = MONOLITH_STAPLE + Random() % (WINGED_LION_STAPLE - MONOLITH_STAPLE); break;
            case RARITY_COMMON:
                i = MONOLITH_COMMON + Random() % (WINGED_LION_COMMON - MONOLITH_COMMON); break;
            case RARITY_RARE:
                i = MONOLITH_RARE + Random() % (WINGED_LION_RARE - MONOLITH_RARE); break;
            case RARITY_EPIC:
                i = MONOLITH_EPIC + Random() % (WINGED_LION_EPIC - MONOLITH_EPIC); break;
            }
            break;
        case TYPE_WINGED_LION:
            switch (rarity)
            {
            default:
            case RARITY_STAPLE:
                i = WINGED_LION_STAPLE + Random() % (SAPROTROPH_COMMON - WINGED_LION_STAPLE); break;
            case RARITY_COMMON:
                i = WINGED_LION_COMMON + Random() % (SAPROTROPH_RARE - WINGED_LION_COMMON); break;
            case RARITY_RARE:
                i = WINGED_LION_RARE + Random() % (SAPROTROPH_EPIC - WINGED_LION_RARE); break;
            case RARITY_EPIC:
                i = WINGED_LION_EPIC + Random() % (GB_LENGTH - WINGED_LION_EPIC); break;
            }
            break;
        default:
        case TYPE_COLOURLESS:
            switch (rarity)
            {
            default:
            case RARITY_STAPLE:
                i = Random() % (SAPROTROPH_COMMON - SAPROTROPH_STAPLE); break;
            case RARITY_COMMON:
                i = SAPROTROPH_COMMON + Random() % (SAPROTROPH_RARE - SAPROTROPH_COMMON); break;
            case RARITY_RARE:
                i = SAPROTROPH_RARE + Random() % (SAPROTROPH_EPIC - SAPROTROPH_RARE); break;
            case RARITY_EPIC:
                i = SAPROTROPH_EPIC + Random() % (GB_LENGTH - SAPROTROPH_EPIC); break;
            }
            break;
        }
    } while (i == choice1 || i == choice2 || i == choice3 || i == choice4 || i == choice5 || i == choice6 || i == choice7 || i == choice8 
|| i == MultichoiceOptions[1] || i == MultichoiceOptions[2] || i == MultichoiceOptions[3]|| i == MultichoiceOptions[0] 
|| BoonList[i].special == 0); 
    return i;
}





