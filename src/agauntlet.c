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
#include "constants/weather.h"

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
    const u8 name[33];
    enum GauntletTypes altar;
    enum BoonType boonType;
    u32 special;
};


const struct BoonGauntlet BoonList[GB_LENGTH] = {
[GB_NULL] =      {         .name =_("   ?!?!?!  "),         .altar = 0,         .boonType = 0,         .special = 0,     },
[GB_30_RANDOM_BERRIES] =      {         .name =_("{HIGHLIGHT LIGHT_GREEN} 30 RANDOM BERRIES "),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_30_BERRIES,         .special = 0,     },
[GB_BIG_ROOT] =      {         .name =_("{HIGHLIGHT LIGHT_GREEN} BIG ROOT "),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_ITEM,         .special = ITEM_BIG_ROOT,     },
[GB_INFESTATION] =      {         .name =_("{HIGHLIGHT LIGHT_GREEN} TUTOR INFESTATION "),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TUTOR,         .special = MOVE_INFESTATION,     },
[GB_POISON_POWDER] =      {         .name =_("{HIGHLIGHT LIGHT_GREEN} TUTOR POISON POWDER "),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TUTOR,         .special = MOVE_POISON_POWDER,     },
[GB_AQUA_RING] =      {         .name =_("{HIGHLIGHT LIGHT_BLUE} TM AQUA RING "),         .altar = TYPE_NEREID,         .boonType = BOON_TM,         .special = ITEM_TM_AQUA_RING,     },
[GB_AROMATIC_MIST] =      {         .name =_("{HIGHLIGHT LIGHT_BLUE} TUTOR AROMATIC MIST "),         .altar = TYPE_NEREID,         .boonType = BOON_TUTOR,         .special = MOVE_AROMATIC_MIST,     },
[GB_LIFE_DEW] =      {         .name =_("{HIGHLIGHT LIGHT_BLUE} TM LIFE DEW "),         .altar = TYPE_NEREID,         .boonType = BOON_TM,         .special = ITEM_TM_LIFE_DEW,     },
[GB_LASER_FOCUS] =      {         .name =_("{HIGHLIGHT BLUE}{COLOR WHITE} TUTOR LASER FOCUS "),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TUTOR,         .special = MOVE_LASER_FOCUS,     },
[GB_LIFE_ORB] =      {         .name =_("{HIGHLIGHT BLUE}{COLOR WHITE} LIFE ORB "),         .altar = TYPE_ELDWYRM,         .boonType = BOON_ITEM,         .special = ITEM_LIFE_ORB,     },
[GB_MUSCLE_BAND] =      {         .name =_("{HIGHLIGHT BLUE}{COLOR WHITE} MUSCLE BAND "),         .altar = TYPE_ELDWYRM,         .boonType = BOON_ITEM,         .special = ITEM_MUSCLE_BAND,     },
[GB_WISE_GLASSES] =      {         .name =_("{HIGHLIGHT BLUE}{COLOR WHITE} WISE GLASSES "),         .altar = TYPE_ELDWYRM,         .boonType = BOON_ITEM,         .special = ITEM_WISE_GLASSES,     },
[GB_FOLLOW_ME] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TUTOR FOLLOW ME "),         .altar = TYPE_DSOTM,         .boonType = BOON_TUTOR,         .special = MOVE_FOLLOW_ME,     },
[GB_HELPING_HAND] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TUTOR HELPING HAND "),         .altar = TYPE_DSOTM,         .boonType = BOON_TUTOR,         .special = ITEM_DAMAGE_BOUNCEABLES,     },
[GB_HYPNOSIS] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TUTOR HYPNOSIS "),         .altar = TYPE_DSOTM,         .boonType = BOON_TUTOR,         .special = MOVE_HYPNOSIS,     },
[GB_EVIOLITE] =      {         .name =_("{HIGHLIGHT LIGHT_RED} EVIOLITE "),         .altar = TYPE_MONOLITH,         .boonType = BOON_ITEM,         .special = ITEM_EVIOLITE,     },
[GB_SHOCK_SHIELD] =      {         .name =_("{HIGHLIGHT LIGHT_RED} SHOCK SHIELD "),         .altar = TYPE_MONOLITH,         .boonType = BOON_ITEM,         .special = ITEM_SHOCK_SHIELD,     },
[GB_STOCKPILE] =      {         .name =_("{HIGHLIGHT LIGHT_RED} TUTOR STOCKPILE "),         .altar = TYPE_MONOLITH,         .boonType = BOON_TUTOR,         .special = MOVE_STOCKPILE,     },
[GB_AIR_CUTTER] =      {         .name =_("{HIGHLIGHT RED}{COLOR WHITE} TUTOR AIR CUTTER "),         .altar = TYPE_WINGED_LION,         .boonType = BOON_TUTOR,         .special = MOVE_AIR_CUTTER,     },
[GB_FOCUS_SASH] =      {         .name =_("{HIGHLIGHT RED}{COLOR WHITE} FOCUS SASH "),         .altar = TYPE_WINGED_LION,         .boonType = BOON_ITEM,         .special = ITEM_FOCUS_SASH,     },
[GB_REROLL_OPTIONS] =      {         .name =_("{HIGHLIGHT RED}{COLOR WHITE} REROLL OPTIONS "),         .altar = TYPE_WINGED_LION,         .boonType = BOON_REROLL,         .special = 0,     },
[GB_20_TERRAIN_SEEDS] =      {         .name =_("{HIGHLIGHT LIGHT_GREEN} 20 TERRAIN SEEDS "),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TERRAIN_SEEDS,         .special = 0,     },
[GB_BLACK_SLUDGE] =      {         .name =_("{HIGHLIGHT LIGHT_GREEN} BLACK SLUDGE "),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_ITEM,         .special = ITEM_BLACK_SLUDGE,     },
[GB_FIRST_IMPRESSION] =      {         .name =_("{HIGHLIGHT LIGHT_GREEN} TUTOR FIRST IMPRESSION "),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TUTOR,         .special = MOVE_FIRST_IMPRESSION,     },
[GB_LEECH_SEED] =      {         .name =_("{HIGHLIGHT LIGHT_GREEN} TM LEECH SEED "),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TM,         .special = ITEM_TM_LEECH_SEED,     },
[GB_NATURAL_GIFT] =      {         .name =_("{HIGHLIGHT LIGHT_GREEN} TUTOR NATURAL GIFT "),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TUTOR,         .special = MOVE_NATURAL_GIFT,     },
[GB_SHED_SHELL] =      {         .name =_("{HIGHLIGHT LIGHT_GREEN} SHED SHELL "),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_ITEM,         .special = ITEM_SHED_SHELL,     },
[GB_STICKY_BARB] =      {         .name =_("{HIGHLIGHT LIGHT_GREEN} STICKY BARB "),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_ITEM,         .special = ITEM_STICKY_BARB,     },
[GB_STRING_SHOT] =      {         .name =_("{HIGHLIGHT LIGHT_GREEN} TUTOR STRING SHOT "),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TUTOR,         .special = MOVE_STRING_SHOT,     },
[GB_TOXIC_ORB_AND_FLAME_ORB] =      {         .name =_("{HIGHLIGHT LIGHT_GREEN} TOXIC ORB AND FLAME ORB "),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TOXICANDFLAMEORB,         .special = 0,     },
[GB_U_TURN] =      {         .name =_("{HIGHLIGHT LIGHT_GREEN} TM U TURN "),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TM,         .special = ITEM_TM_U_TURN,     },
[GB_VENOM_DRENCH] =      {         .name =_("{HIGHLIGHT LIGHT_GREEN} TM VENOM DRENCH "),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TM,         .special = ITEM_TM_VENOM_DRENCH,     },
[GB_VENOSHOCK] =      {         .name =_("{HIGHLIGHT LIGHT_GREEN} TM VENOSHOCK "),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TM,         .special = ITEM_TM_VENOSHOCK,     },
[GB_WORRY_SEED] =      {         .name =_("{HIGHLIGHT LIGHT_GREEN} TM WORRY SEED "),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TM,         .special = ITEM_TM_WORRY_SEED,     },
[GB_AURORA_VEIL] =      {         .name =_("{HIGHLIGHT LIGHT_BLUE} TM AURORA VEIL "),         .altar = TYPE_NEREID,         .boonType = BOON_TM,         .special = ITEM_TM_AURORA_VEIL,     },
[GB_COVERT_CLOAK] =      {         .name =_("{HIGHLIGHT LIGHT_BLUE} COVERT CLOAK "),         .altar = TYPE_NEREID,         .boonType = BOON_ITEM,         .special = ITEM_COVERT_CLOAK,     },
[GB_DRAINING_KISS] =      {         .name =_("{HIGHLIGHT LIGHT_BLUE} TM DRAINING KISS "),         .altar = TYPE_NEREID,         .boonType = BOON_TM,         .special = ITEM_TM_DRAINING_KISS,     },
[GB_EXP_SHARE] =      {         .name =_("{HIGHLIGHT LIGHT_BLUE} EXP SHARE "),         .altar = TYPE_NEREID,         .boonType = BOON_ITEM,         .special = ITEM_EXP_SHARE,     },
[GB_HAIL] =      {         .name =_("{HIGHLIGHT LIGHT_BLUE} TM HAIL "),         .altar = TYPE_NEREID,         .boonType = BOON_TM,         .special = ITEM_TM_HAIL,     },
[GB_HAZE] =      {         .name =_("{HIGHLIGHT LIGHT_BLUE} TUTOR HAZE "),         .altar = TYPE_NEREID,         .boonType = BOON_TUTOR,         .special = MOVE_HAZE,     },
[GB_MISTY] =      {         .name =_("{HIGHLIGHT LIGHT_BLUE} MISTY "),         .altar = TYPE_NEREID,         .boonType = BOON_WEATHER,         .special = WEATHER_FOG_HORIZONTAL,     },
[GB_MONEY] =      {         .name =_("{HIGHLIGHT LIGHT_BLUE} MONEY "),         .altar = TYPE_NEREID,         .boonType = BOON_MONEY,         .special = 5000,     },
[GB_RAIN_DANCE] =      {         .name =_("{HIGHLIGHT LIGHT_BLUE} TM RAIN DANCE "),         .altar = TYPE_NEREID,         .boonType = BOON_TM,         .special = ITEM_TM_RAIN_DANCE,     },
[GB_SNOW] =      {         .name =_("{HIGHLIGHT LIGHT_BLUE} SNOW "),         .altar = TYPE_NEREID,         .boonType = BOON_WEATHER,         .special = WEATHER_SNOW,     },
[GB_SOAK] =      {         .name =_("{HIGHLIGHT LIGHT_BLUE} TM SOAK "),         .altar = TYPE_NEREID,         .boonType = BOON_TM,         .special = ITEM_TM_SOAK,     },
[GB_CHARCOAL] =      {         .name =_("{HIGHLIGHT BLUE}{COLOR WHITE} CHARCOAL "),         .altar = TYPE_ELDWYRM,         .boonType = BOON_ITEM,         .special = ITEM_CHARCOAL,     },
[GB_CHOICE_BAND] =      {         .name =_("{HIGHLIGHT BLUE}{COLOR WHITE} CHOICE BAND "),         .altar = TYPE_ELDWYRM,         .boonType = BOON_ITEM,         .special = ITEM_CHOICE_BAND,     },
[GB_CHOICE_SCARF] =      {         .name =_("{HIGHLIGHT BLUE}{COLOR WHITE} CHOICE SCARF "),         .altar = TYPE_ELDWYRM,         .boonType = BOON_ITEM,         .special = ITEM_CHOICE_SCARF,     },
[GB_DRAGON_CHEER] =      {         .name =_("{HIGHLIGHT BLUE}{COLOR WHITE} TM DRAGON CHEER "),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TM,         .special = ITEM_TM_DRAGON_CHEER,     },
[GB_DRAGON_FANG] =      {         .name =_("{HIGHLIGHT BLUE}{COLOR WHITE} DRAGON FANG "),         .altar = TYPE_ELDWYRM,         .boonType = BOON_ITEM,         .special = ITEM_DRAGON_FANG,     },
[GB_EXPERT_BELT] =      {         .name =_("{HIGHLIGHT BLUE}{COLOR WHITE} EXPERT BELT "),         .altar = TYPE_ELDWYRM,         .boonType = BOON_ITEM,         .special = ITEM_EXPERT_BELT,     },
[GB_EXPLOSION] =      {         .name =_("{HIGHLIGHT BLUE}{COLOR WHITE} TUTOR EXPLOSION "),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TUTOR,         .special = MOVE_EXPLOSION,     },
[GB_FIRE_PUNCH] =      {         .name =_("{HIGHLIGHT BLUE}{COLOR WHITE} TUTOR FIRE PUNCH "),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TUTOR,         .special = MOVE_FIRE_PUNCH,     },
[GB_INFERNO] =      {         .name =_("{HIGHLIGHT BLUE}{COLOR WHITE} TUTOR INFERNO "),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TUTOR,         .special = MOVE_INFERNO,     },
[GB_MAGNET] =      {         .name =_("{HIGHLIGHT BLUE}{COLOR WHITE} MAGNET "),         .altar = TYPE_ELDWYRM,         .boonType = BOON_ITEM,         .special = ITEM_MAGNET,     },
[GB_SUNNY_DAY] =      {         .name =_("{HIGHLIGHT BLUE}{COLOR WHITE} TM SUNNY DAY "),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TM,         .special = ITEM_TM_SUNNY_DAY,     },
[GB_THUNDER_PUNCH] =      {         .name =_("{HIGHLIGHT BLUE}{COLOR WHITE} TUTOR THUNDER PUNCH "),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TUTOR,         .special = MOVE_THUNDER_PUNCH,     },
[GB_THUNDER_WAVE] =      {         .name =_("{HIGHLIGHT BLUE}{COLOR WHITE} TM THUNDER WAVE "),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TM,         .special = ITEM_TM_THUNDER_WAVE,     },
[GB_WILL_O_WISP] =      {         .name =_("{HIGHLIGHT BLUE}{COLOR WHITE} TM WILL O WISP "),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TM,         .special = ITEM_TM_WILL_O_WISP,     },
[GB_ZAP_CANNON] =      {         .name =_("{HIGHLIGHT BLUE}{COLOR WHITE} TUTOR ZAP CANNON "),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TUTOR,         .special = MOVE_ZAP_CANNON,     },
[GB_BATON_PASS] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TM BATON PASS "),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_BATON_PASS,     },
[GB_CALM_MIND] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TM CALM MIND "),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_CALM_MIND,     },
[GB_DARK_PULSE] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TM DARK PULSE "),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_DARK_PULSE,     },
[GB_DREAM_EATER] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TUTOR DREAM EATER "),         .altar = TYPE_DSOTM,         .boonType = BOON_TUTOR,         .special = MOVE_DREAM_EATER,     },
[GB_HEX] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TUTOR HEX "),         .altar = TYPE_DSOTM,         .boonType = BOON_TUTOR,         .special = MOVE_HEX,     },
[GB_HONE_CLAWS] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TM HONE CLAWS "),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_HONE_CLAWS,     },
[GB_LIGHT_CLAY] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} LIGHT CLAY "),         .altar = TYPE_DSOTM,         .boonType = BOON_ITEM,         .special = 0,     },
[GB_LIGHT_SCREEN] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TM LIGHT SCREEN "),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_LIGHT_SCREEN,     },
[GB_NASTY_PLOT] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} NASTY PLOT "),         .altar = TYPE_DSOTM,         .boonType = BOON_TUTOR,         .special = 0,     },
[GB_PHANTOM_FORCE] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TM PHANTOM FORCE "),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_PHANTOM_FORCE,     },
[GB_POWER_HERB] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} POWER HERB "),         .altar = TYPE_DSOTM,         .boonType = BOON_ITEM,         .special = 0,     },
[GB_PROTECT] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TM PROTECT "),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_PROTECT,     },
[GB_PSYCHO_CUT] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TM PSYCHO CUT "),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_PSYCHO_CUT,     },
[GB_REFLECT] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TM REFLECT "),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_REFLECT,     },
[GB_SWORDS_DANCE_TUT] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} SWORDS DANCE "),         .altar = TYPE_DSOTM,         .boonType = BOON_TUTOR,         .special = 0,     },
[GB_TRICK] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TM TRICK "),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_TRICK,     },
[GB_TRICK_ROOM] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TM TRICK ROOM "),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_TRICK_ROOM,     },
[GB_WEATHER_BALL] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TM WEATHER BALL "),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_WEATHER_BALL,     },
[GB_WISH] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TM WISH "),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_WISH,     },
[GB_10_FULL_RESTORES] =      {         .name =_("{HIGHLIGHT LIGHT_RED} 10 FULL RESTORES "),         .altar = TYPE_MONOLITH,         .boonType = BOON_10XITEM,         .special = ITEM_FULL_RESTORE,     },
[GB_10_HYPER_POTIONS] =      {         .name =_("{HIGHLIGHT LIGHT_RED} 10 HYPER POTIONS "),         .altar = TYPE_MONOLITH,         .boonType = BOON_10XITEM,         .special = ITEM_HYPER_POTION,     },
[GB_10_X_DEFEND_10_X_SP_DEF] =      {         .name =_("{HIGHLIGHT LIGHT_RED} 10 X DEFEND, 10 X SP.DEF "),         .altar = TYPE_MONOLITH,         .boonType = BOON_XDEFXSPDEF,         .special = 0,     },
[GB_ANCIENT_POWER] =      {         .name =_("{HIGHLIGHT LIGHT_RED} TM ANCIENT POWER "),         .altar = TYPE_MONOLITH,         .boonType = BOON_TM,         .special = ITEM_TM_ANCIENT_POWER,     },
[GB_ASSAULT_VEST] =      {         .name =_("{HIGHLIGHT LIGHT_RED} ASSAULT VEST "),         .altar = TYPE_MONOLITH,         .boonType = BOON_ITEM,         .special = ITEM_ASSAULT_VEST,     },
[GB_DIG] =      {         .name =_("{HIGHLIGHT LIGHT_RED} TM DIG "),         .altar = TYPE_MONOLITH,         .boonType = BOON_TM,         .special = ITEM_TM_DIG,     },
[GB_HEAVY_DUTY_BOOTS] =      {         .name =_("{HIGHLIGHT LIGHT_RED} HEAVY DUTY BOOTS "),         .altar = TYPE_MONOLITH,         .boonType = BOON_ITEM,         .special = ITEM_HEAVY_DUTY_BOOTS,     },
[GB_IRON_DEFENSE] =      {         .name =_("{HIGHLIGHT LIGHT_RED} TM IRON DEFENSE "),         .altar = TYPE_MONOLITH,         .boonType = BOON_TM,         .special = ITEM_TM_IRON_DEFENSE,     },
[GB_ROCK_SLIDE] =      {         .name =_("{HIGHLIGHT LIGHT_RED} TM ROCK SLIDE "),         .altar = TYPE_MONOLITH,         .boonType = BOON_TM,         .special = ITEM_TM_ROCK_SLIDE,     },
[GB_ROCK_SLIDE_TUTOR] =      {         .name =_("{HIGHLIGHT LIGHT_RED} HM STRENGTH "),         .altar = TYPE_MONOLITH,         .boonType = BOON_HM,         .special = ITEM_HM_STRENGTH,     },
[GB_ROCK_SMASH] =      {         .name =_("{HIGHLIGHT LIGHT_RED} HM ROCK SMASH "),         .altar = TYPE_MONOLITH,         .boonType = BOON_HM,         .special = ITEM_HM_ROCK_SMASH,     },
[GB_ROCKY_HELMET] =      {         .name =_("{HIGHLIGHT LIGHT_RED} ROCKY HELMET "),         .altar = TYPE_MONOLITH,         .boonType = BOON_ITEM,         .special = ITEM_ROCKY_HELMET,     },
[GB_ROLLOUT] =      {         .name =_("{HIGHLIGHT LIGHT_RED} TUTOR ROLLOUT "),         .altar = TYPE_MONOLITH,         .boonType = BOON_TUTOR,         .special = MOVE_ROLLOUT,     },
[GB_ROTOTILLER] =      {         .name =_("{HIGHLIGHT LIGHT_RED} TUTOR ROTOTILLER "),         .altar = TYPE_MONOLITH,         .boonType = BOON_TUTOR,         .special = MOVE_ROTOTILLER,     },
[GB_SAFETY_GOGGLES] =      {         .name =_("{HIGHLIGHT LIGHT_RED} SAFETY GOGGLES "),         .altar = TYPE_MONOLITH,         .boonType = BOON_ITEM,         .special = ITEM_SAFETY_GOGGLES,     },
[GB_SANDSTORM] =      {         .name =_("{HIGHLIGHT LIGHT_RED} TM SANDSTORM "),         .altar = TYPE_MONOLITH,         .boonType = BOON_TM,         .special = ITEM_TM_SANDSTORM,     },
[GB_SHORE_UP] =      {         .name =_("{HIGHLIGHT LIGHT_RED} TUTOR SHORE UP "),         .altar = TYPE_MONOLITH,         .boonType = BOON_TUTOR,         .special = MOVE_SHORE_UP,     },
[GB_WIDE_GUARD] =      {         .name =_("{HIGHLIGHT LIGHT_RED} TUTOR WIDE GUARD "),         .altar = TYPE_MONOLITH,         .boonType = BOON_TUTOR,         .special = MOVE_WIDE_GUARD,     },
[GB_10_X_SPEEDS] =      {         .name =_("{HIGHLIGHT RED}{COLOR WHITE} 10 X SPEEDS "),         .altar = TYPE_WINGED_LION,         .boonType = BOON_10XITEM,         .special = ITEM_X_SPEED,     },
[GB_AIR_BALLOON] =      {         .name =_("{HIGHLIGHT RED}{COLOR WHITE} AIR BALLOON "),         .altar = TYPE_WINGED_LION,         .boonType = BOON_ITEM,         .special = ITEM_AIR_BALLOON,     },
[GB_EJECT_BUTTON] =      {         .name =_("{HIGHLIGHT RED}{COLOR WHITE} EJECT BUTTON "),         .altar = TYPE_WINGED_LION,         .boonType = BOON_ITEM,         .special = ITEM_EJECT_BUTTON,     },
[GB_EJECT_PACK] =      {         .name =_("{HIGHLIGHT RED}{COLOR WHITE} EJECT PACK "),         .altar = TYPE_WINGED_LION,         .boonType = BOON_ITEM,         .special = ITEM_EJECT_PACK,     },
[GB_FLAIL] =      {         .name =_("{HIGHLIGHT RED}{COLOR WHITE} TUTOR FLAIL "),         .altar = TYPE_WINGED_LION,         .boonType = BOON_TUTOR,         .special = MOVE_FLAIL,     },
[GB_FLYING_GEM] =      {         .name =_("{HIGHLIGHT RED}{COLOR WHITE} FLYING GEM "),         .altar = TYPE_WINGED_LION,         .boonType = BOON_ITEM,         .special = ITEM_FLYING_GEM,     },
[GB_FOCUS_BAND] =      {         .name =_("{HIGHLIGHT RED}{COLOR WHITE} FOCUS BAND "),         .altar = TYPE_WINGED_LION,         .boonType = BOON_ITEM,         .special = ITEM_FOCUS_BAND,     },
[GB_FOCUS_ENERGY] =      {         .name =_("{HIGHLIGHT RED}{COLOR WHITE} TUTOR FOCUS ENERGY "),         .altar = TYPE_WINGED_LION,         .boonType = BOON_TUTOR,         .special = MOVE_FOCUS_ENERGY,     },
[GB_PUNCHING_GLOVE] =      {         .name =_("{HIGHLIGHT RED}{COLOR WHITE} PUNCHING GLOVE "),         .altar = TYPE_WINGED_LION,         .boonType = BOON_ITEM,         .special = ITEM_PUNCHING_GLOVE,     },
[GB_RAPID_SPIN] =      {         .name =_("{HIGHLIGHT RED}{COLOR WHITE} TUTOR RAPID SPIN "),         .altar = TYPE_WINGED_LION,         .boonType = BOON_TUTOR,         .special = MOVE_RAPID_SPIN,     },
[GB_REVERSAL] =      {         .name =_("{HIGHLIGHT RED}{COLOR WHITE} TUTOR REVERSAL "),         .altar = TYPE_WINGED_LION,         .boonType = BOON_TUTOR,         .special = MOVE_REVERSAL,     },
[GB_SCOPE_LENS] =      {         .name =_("{HIGHLIGHT RED}{COLOR WHITE} SCOPE LENS "),         .altar = TYPE_WINGED_LION,         .boonType = BOON_ITEM,         .special = ITEM_SCOPE_LENS,     },
[GB_SEISMIC_TOSS] =      {         .name =_("{HIGHLIGHT RED}{COLOR WHITE} TUTOR SEISMIC TOSS "),         .altar = TYPE_WINGED_LION,         .boonType = BOON_TUTOR,         .special = MOVE_SEISMIC_TOSS,     },
[GB_TAILWIND] =      {         .name =_("{HIGHLIGHT RED}{COLOR WHITE} TM TAILWIND "),         .altar = TYPE_WINGED_LION,         .boonType = BOON_TM,         .special = ITEM_TM_TAILWIND,     },
[GB_TUTOR_ENDURE_REROLL] =      {         .name =_("{HIGHLIGHT RED}{COLOR WHITE} TUTOR ENDURE & REROLL "),         .altar = TYPE_WINGED_LION,         .boonType = BOON_REROLLPLUSTUTOR,         .special = MOVE_ENDURE,     },
[GB_TUTOR_METRONOME_REROLL] =      {         .name =_("{HIGHLIGHT RED}{COLOR WHITE} TUTOR METRONOME & REROLL "),         .altar = TYPE_WINGED_LION,         .boonType = BOON_REROLLPLUSTUTOR,         .special = MOVE_METRONOME,     },
[GB_KINGS_ROCK] =      {         .name =_("{HIGHLIGHT RED}{COLOR WHITE} KINGS ROCK "),         .altar = TYPE_WINGED_LION,         .boonType = BOON_ITEM,         .special = ITEM_KINGS_ROCK,     },
[GB_UPPER_HAND] =      {         .name =_("{COLOR DARK_GRAY} TM UPPER HAND "),         .altar = TYPE_WINGED_LION,         .boonType = BOON_TM,         .special = ITEM_TM_UPPER_HAND,     },
[GB_FALSE_SWIPE] =      {         .name =_("{COLOR DARK_GRAY} TUTOR FALSE SWIPE "),         .altar = TYPE_COLOURLESS,         .boonType = BOON_TUTOR,         .special = MOVE_FALSE_SWIPE,     },
[GB_FLASH] =      {         .name =_("{COLOR DARK_GRAY} HM FLASH "),         .altar = TYPE_COLOURLESS,         .boonType = BOON_HM,         .special = ITEM_HM_FLASH,     },
[GB_MEGA_KICK] =      {         .name =_("{COLOR DARK_GRAY} TUTOR MEGA KICK "),         .altar = TYPE_COLOURLESS,         .boonType = BOON_TUTOR,         .special = MOVE_MEGA_KICK,     },
[GB_MEGA_PUNCH] =      {         .name =_("{COLOR DARK_GRAY} TUTOR MEGA PUNCH "),         .altar = TYPE_COLOURLESS,         .boonType = BOON_TUTOR,         .special = MOVE_MEGA_PUNCH,     },
[GB_PSYCH_UP] =      {         .name =_("{COLOR DARK_GRAY} TUTOR PSYCH UP "),         .altar = TYPE_COLOURLESS,         .boonType = BOON_TUTOR,         .special = MOVE_PSYCH_UP,     },
[GB_SNORE] =      {         .name =_("{COLOR DARK_GRAY} TUTOR SNORE "),         .altar = TYPE_COLOURLESS,         .boonType = BOON_TUTOR,         .special = MOVE_SNORE,     },
[GB_SWAGGER] =      {         .name =_("{COLOR DARK_GRAY} TUTOR SWAGGER "),         .altar = TYPE_COLOURLESS,         .boonType = BOON_TUTOR,         .special = MOVE_SWAGGER,     },
[GB_SWIFT] =      {         .name =_("{COLOR DARK_GRAY} TUTOR SWIFT "),         .altar = TYPE_COLOURLESS,         .boonType = BOON_TUTOR,         .special = MOVE_SWIFT,     },
[GB_WONDER_ROOM_WEATHER] =      {         .name =_("{COLOR DARK_GRAY} WONDER ROOM WEATHER "),         .altar = TYPE_COLOURLESS,         .boonType = BOON_STARTINGSTATUS,         .special = 4,     },
[GB_GIGA_DRAIN] =      {         .name =_("{HIGHLIGHT LIGHT_GREEN} TM GIGA DRAIN "),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TM,         .special = ITEM_TM_GIGA_DRAIN,     },
[GB_GRASSY_TERRAIN] =      {         .name =_("{HIGHLIGHT LIGHT_GREEN} GRASSY TERRAIN "),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_STARTINGSTATUS,         .special = 1,     },
[GB_LEECH_LIFE] =      {         .name =_("{HIGHLIGHT LIGHT_GREEN} TUTOR LEECH LIFE "),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TUTOR,         .special = MOVE_LEECH_LIFE,     },
[GB_LEFTOVERS] =      {         .name =_("{HIGHLIGHT LIGHT_GREEN} LEFTOVERS "),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_ITEM,         .special = ITEM_LEFTOVERS,     },
[GB_LUNGE] =      {         .name =_("{HIGHLIGHT LIGHT_GREEN} TM LUNGE "),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TM,         .special = ITEM_TM_LUNGE,     },
[GB_NATURE_POWER] =      {         .name =_("{HIGHLIGHT LIGHT_GREEN} HM NATURE POWER "),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_HM,         .special = ITEM_HM_NATURE_POWER,     },
[GB_SLUDGE_BOMB] =      {         .name =_("{HIGHLIGHT LIGHT_GREEN} TM SLUDGE BOMB "),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TM,         .special = ITEM_TM_SLUDGE_BOMB,     },
[GB_SOLAR_BEAM] =      {         .name =_("{HIGHLIGHT LIGHT_GREEN} TM SOLAR BEAM "),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TM,         .special = ITEM_TM_SOLAR_BEAM,     },
[GB_STUFF_CHEEKS] =      {         .name =_("{HIGHLIGHT LIGHT_GREEN} TUTOR STUFF CHEEKS "),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TUTOR,         .special = MOVE_STUFF_CHEEKS,     },
[GB_BLIZZARD] =      {         .name =_("{HIGHLIGHT LIGHT_BLUE} TM BLIZZARD "),         .altar = TYPE_NEREID,         .boonType = BOON_TM,         .special = ITEM_TM_BLIZZARD,     },
[GB_DAZZLING_GLEAM] =      {         .name =_("{HIGHLIGHT LIGHT_BLUE} TM DAZZLING GLEAM "),         .altar = TYPE_NEREID,         .boonType = BOON_TM,         .special = ITEM_TM_DAZZLING_GLEAM,     },
[GB_DECORATE] =      {         .name =_("{HIGHLIGHT LIGHT_BLUE} TUTOR DECORATE "),         .altar = TYPE_NEREID,         .boonType = BOON_TUTOR,         .special = MOVE_DECORATE,     },
[GB_DIVE] =      {         .name =_("{HIGHLIGHT LIGHT_BLUE} HM DIVE "),         .altar = TYPE_NEREID,         .boonType = BOON_HM,         .special = ITEM_HM_DIVE,     },
[GB_HEAL_BELL] =      {         .name =_("{HIGHLIGHT LIGHT_BLUE} TUTOR HEAL BELL "),         .altar = TYPE_NEREID,         .boonType = BOON_TUTOR,         .special = MOVE_HEAL_BELL,     },
[GB_LUCKY_EGG] =      {         .name =_("{HIGHLIGHT LIGHT_BLUE} LUCKY EGG "),         .altar = TYPE_NEREID,         .boonType = BOON_ITEM,         .special = ITEM_LUCKY_EGG,     },
[GB_MIRROR_HERB] =      {         .name =_("{HIGHLIGHT LIGHT_BLUE} MIRROR HERB "),         .altar = TYPE_NEREID,         .boonType = BOON_ITEM,         .special = ITEM_MIRROR_HERB,     },
[GB_PLAY_ROUGH] =      {         .name =_("{HIGHLIGHT LIGHT_BLUE} TM PLAY ROUGH "),         .altar = TYPE_NEREID,         .boonType = BOON_TM,         .special = ITEM_TM_PLAY_ROUGH,     },
[GB_SURF] =      {         .name =_("{HIGHLIGHT LIGHT_BLUE} HM SURF "),         .altar = TYPE_NEREID,         .boonType = BOON_HM,         .special = ITEM_HM_SURF,     },
[GB_TRIPLE_AXEL] =      {         .name =_("{HIGHLIGHT LIGHT_BLUE} TM TRIPLE AXEL "),         .altar = TYPE_NEREID,         .boonType = BOON_TM,         .special = ITEM_TM_TRIPLE_AXEL,     },
[GB_WATERFALL] =      {         .name =_("{HIGHLIGHT LIGHT_BLUE} HM WATERFALL "),         .altar = TYPE_NEREID,         .boonType = BOON_HM,         .special = ITEM_HM_WATERFALL,     },
[GB_BLAZE_KICK] =      {         .name =_("{HIGHLIGHT BLUE}{COLOR WHITE} TM BLAZE KICK "),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TM,         .special = ITEM_TM_BLAZE_KICK,     },
[GB_CHOICE_SPECS] =      {         .name =_("{HIGHLIGHT BLUE}{COLOR WHITE} CHOICE SPECS "),         .altar = TYPE_ELDWYRM,         .boonType = BOON_ITEM,         .special = ITEM_CHOICE_SPECS,     },
[GB_DRACO_METEOR] =      {         .name =_("{HIGHLIGHT BLUE}{COLOR WHITE} TM DRACO METEOR "),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TM,         .special = ITEM_TM_DRACO_METEOR,     },
[GB_DRAGON_CLAW] =      {         .name =_("{HIGHLIGHT BLUE}{COLOR WHITE} TM DRAGON CLAW "),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TM,         .special = ITEM_TM_DRAGON_CLAW,     },
[GB_DRAGON_RAGE] =      {         .name =_("{HIGHLIGHT BLUE}{COLOR WHITE} TUTOR DRAGON RAGE "),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TUTOR,         .special = MOVE_DRAGON_RAGE,     },
[GB_FLAMETHROWER] =      {         .name =_("{HIGHLIGHT BLUE}{COLOR WHITE} TM FLAMETHROWER "),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TM,         .special = ITEM_TM_FLAMETHROWER,     },
[GB_THUNDERBOLT] =      {         .name =_("{HIGHLIGHT BLUE}{COLOR WHITE} TM THUNDERBOLT "),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TM,         .special = ITEM_TM_THUNDERBOLT,     },
[GB_VOLT_SWITCH] =      {         .name =_("{HIGHLIGHT BLUE}{COLOR WHITE} TM VOLT SWITCH "),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TM,         .special = ITEM_TM_VOLT_SWITCH,     },
[GB_WHITE_HERB] =      {         .name =_("{HIGHLIGHT BLUE}{COLOR WHITE} WHITE HERB "),         .altar = TYPE_ELDWYRM,         .boonType = BOON_ITEM,         .special = ITEM_WHITE_HERB,     },
[GB_ZING_ZAP] =      {         .name =_("{HIGHLIGHT BLUE}{COLOR WHITE} TM ZING ZAP "),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TM,         .special = ITEM_TM_ZING_ZAP,     },
[GB_GRAVITY] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TUTOR GRAVITY "),         .altar = TYPE_DSOTM,         .boonType = BOON_TUTOR,         .special = MOVE_GRAVITY,     },
[GB_HYPER_BEAM] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TM HYPER BEAM "),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_HYPER_BEAM,     },
[GB_KNOCK_OFF] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TM KNOCK OFF "),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_KNOCK_OFF,     },
[GB_NASTY_PLOT_TUT] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TM NASTY PLOT "),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_NASTY_PLOT,     },
[GB_NIGHTMARE] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TUTOR NIGHTMARE "),         .altar = TYPE_DSOTM,         .boonType = BOON_TUTOR,         .special = MOVE_NIGHTMARE,     },
[GB_POWER_SPLIT] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TUTOR POWER SPLIT "),         .altar = TYPE_DSOTM,         .boonType = BOON_TUTOR,         .special = MOVE_POWER_SPLIT,     },
[GB_PSYCHIC] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TM PSYCHIC "),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_PSYCHIC,     },
[GB_REST] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TM REST "),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_REST,     },
[GB_RETURN] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TM RETURN "),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_RETURN,     },
[GB_SHADOW_BALL] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TM SHADOW BALL "),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_SHADOW_BALL,     },
[GB_SLEEP_TALK] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TM SLEEP TALK "),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_SLEEP_TALK,     },
[GB_SPEED_SWAP] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TUTOR SPEED SWAP "),         .altar = TYPE_DSOTM,         .boonType = BOON_TUTOR,         .special = MOVE_SPEED_SWAP,     },
[GB_SUCKER_PUNCH] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TM SUCKER PUNCH "),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_SUCKER_PUNCH,     },
[GB_SWORDS_DANCE] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TM SWORDS DANCE "),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_SWORDS_DANCE,     },
[GB_10_IRON_HP_UP_ZINC] =      {         .name =_("{HIGHLIGHT LIGHT_RED} 10 IRONs, HP UPs & ZINCs "),         .altar = TYPE_MONOLITH,         .boonType = BOON_10IRON10HPUP10ZINC,         .special = 0,     },
[GB_10X_PP_UP] =      {         .name =_("{HIGHLIGHT LIGHT_RED} 10X PP UP "),         .altar = TYPE_MONOLITH,         .boonType = BOON_10XITEM,         .special = ITEM_PP_UP,     },
[GB_EARTHQUAKE] =      {         .name =_("{HIGHLIGHT LIGHT_RED} TM EARTHQUAKE "),         .altar = TYPE_MONOLITH,         .boonType = BOON_TM,         .special = ITEM_TM_EARTHQUAKE,     },
[GB_METEOR_BEAM] =      {         .name =_("{HIGHLIGHT LIGHT_RED} TM METEOR BEAM "),         .altar = TYPE_MONOLITH,         .boonType = BOON_TM,         .special = ITEM_TM_METEOR_BEAM,     },
[GB_SCORCHING_SANDS] =      {         .name =_("{HIGHLIGHT LIGHT_RED} TM SCORCHING SANDS "),         .altar = TYPE_MONOLITH,         .boonType = BOON_TM,         .special = ITEM_TM_SCORCHING_SANDS,     },
[GB_STEEL_BEAM] =      {         .name =_("{HIGHLIGHT LIGHT_RED} TM STEEL BEAM "),         .altar = TYPE_MONOLITH,         .boonType = BOON_TM,         .special = ITEM_TM_STEEL_BEAM,     },
[GB_STONE_EDGE] =      {         .name =_("{HIGHLIGHT LIGHT_RED} TM STONE EDGE "),         .altar = TYPE_MONOLITH,         .boonType = BOON_TM,         .special = ITEM_TM_STONE_EDGE,     },
[GB_ACROBATICS] =      {         .name =_("{HIGHLIGHT RED}{COLOR WHITE} TM ACROBATICS "),         .altar = TYPE_WINGED_LION,         .boonType = BOON_TM,         .special = ITEM_TM_ACROBATICS,     },
[GB_COUNTER] =      {         .name =_("{HIGHLIGHT RED}{COLOR WHITE} TUTOR COUNTER "),         .altar = TYPE_WINGED_LION,         .boonType = BOON_TUTOR,         .special = MOVE_COUNTER,     },
[GB_DRAIN_PUNCH] =      {         .name =_("{HIGHLIGHT RED}{COLOR WHITE} TM DRAIN PUNCH "),         .altar = TYPE_WINGED_LION,         .boonType = BOON_TM,         .special = ITEM_TM_DRAIN_PUNCH,     },
[GB_QUASH] =      {         .name =_("{HIGHLIGHT RED}{COLOR WHITE} TUTOR QUASH "),         .altar = TYPE_WINGED_LION,         .boonType = BOON_TUTOR,         .special = MOVE_QUASH,     },
[GB_TUTOR_FLING_REROLL] =      {         .name =_("{HIGHLIGHT RED}{COLOR WHITE} TUTOR FLING & REROLL "),         .altar = TYPE_WINGED_LION,         .boonType = BOON_REROLLPLUSTUTOR,         .special = MOVE_FLING,     },
[GB_DOUBLE_EDGE] =      {         .name =_("{COLOR DARK_GRAY} TUTOR DOUBLE EDGE "),         .altar = TYPE_COLOURLESS,         .boonType = BOON_TUTOR,         .special = MOVE_DOUBLE_EDGE,     },
[GB_INVERSE_WEATHER] =      {         .name =_("{COLOR DARK_GRAY} INVERSE WEATHER "),         .altar = TYPE_COLOURLESS,         .boonType = BOON_STARTINGSTATUS,         .special = 7,     },
[GB_SPORE] =      {         .name =_("{HIGHLIGHT LIGHT_GREEN} TUTOR SPORE "),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TUTOR,         .special = MOVE_SPORE,     },
[GB_TOXIC_THREAD] =      {         .name =_("{HIGHLIGHT LIGHT_GREEN} TUTOR TOXIC THREAD "),         .altar = TYPE_SAPROTROPH,         .boonType = BOON_TUTOR,         .special = MOVE_TOXIC_THREAD,     },
[GB_HAILSTORM_WEATHER] =      {         .name =_("{HIGHLIGHT LIGHT_BLUE} HAILSTORM WEATHER "),         .altar = TYPE_NEREID,         .boonType = BOON_WEATHER,         .special = WEATHER_SNOW_HAIL,     },
[GB_MORE_MONEY] =      {         .name =_("{HIGHLIGHT LIGHT_BLUE} MORE MONEY "),         .altar = TYPE_NEREID,         .boonType = BOON_MONEY,         .special = 50000,     },
[GB_RAINY_WEATHER] =      {         .name =_("{HIGHLIGHT LIGHT_BLUE} RAINY WEATHER "),         .altar = TYPE_NEREID,         .boonType = BOON_WEATHER,         .special = WEATHER_RAIN,     },
[GB_OUTRAGE] =      {         .name =_("{HIGHLIGHT BLUE}{COLOR WHITE} TUTOR OUTRAGE "),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TUTOR,         .special = MOVE_OUTRAGE,     },
[GB_RUINATION] =      {         .name =_("{HIGHLIGHT BLUE}{COLOR WHITE} TUTOR RUINATION "),         .altar = TYPE_ELDWYRM,         .boonType = BOON_TUTOR,         .special = MOVE_RUINATION,     },
[GB_CURSE] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TM CURSE "),         .altar = TYPE_DSOTM,         .boonType = BOON_TM,         .special = ITEM_TM_CURSE,     },
[GB_DARK_VOID] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TUTOR DARK VOID "),         .altar = TYPE_DSOTM,         .boonType = BOON_TUTOR,         .special = MOVE_DARK_VOID,     },
[GB_EXPANDING_FORCE] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TUTOR EXPANDING FORCE "),         .altar = TYPE_DSOTM,         .boonType = BOON_TUTOR,         .special = MOVE_EXPANDING_FORCE,     },
[GB_MAGIC_ROOM_WEATHER] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} MAGIC ROOM WEATHER "),         .altar = TYPE_DSOTM,         .boonType = BOON_STARTINGSTATUS,         .special = 3,     },
[GB_PHOTON_GEYSER] =      {         .name =_("{HIGHLIGHT DARK_GRAY}{COLOR WHITE} TUTOR PHOTON GEYSER "),         .altar = TYPE_DSOTM,         .boonType = BOON_TUTOR,         .special = MOVE_PHOTON_GEYSER,     },
[GB_10X_REVIVE] =      {         .name =_("{HIGHLIGHT LIGHT_RED} 10X REVIVE "),         .altar = TYPE_MONOLITH,         .boonType = BOON_10XITEM,         .special = ITEM_REVIVE,     },
[GB_BODY_PRESS] =      {         .name =_("{HIGHLIGHT LIGHT_RED} TUTOR BODY PRESS "),         .altar = TYPE_MONOLITH,         .boonType = BOON_TUTOR,         .special = MOVE_BODY_PRESS,     },
[GB_CANNONADE] =      {         .name =_("{HIGHLIGHT LIGHT_RED} TUTOR CANNONADE "),         .altar = TYPE_MONOLITH,         .boonType = BOON_TUTOR,         .special = MOVE_BASTION_WALLS,     },
[GB_EXTREME_SPEED] =      {         .name =_("{HIGHLIGHT RED}{COLOR WHITE} TUTOR EXTREME SPEED "),         .altar = TYPE_WINGED_LION,         .boonType = BOON_TUTOR,         .special = MOVE_EXTREME_SPEED,     },
[GB_TAILWIND_WEATHER] =      {         .name =_("{HIGHLIGHT RED}{COLOR WHITE} TAILWIND WEATHER "),         .altar = TYPE_WINGED_LION,         .boonType = BOON_STARTINGSTATUS,         .special = 5,     },


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
   u32 itemPool = ScriptReadByte(ctx);
   switch (itemPool){
      default:
      case 0: DoGauntletBoonList(70, 24, 5, 1); return;
      case 1: DoGauntletBoonList(50, 40, 9, 1); return;
      case 2: DoGauntletBoonList(10, 80, 9, 1); return;
      case 3:  DoGauntletBoonList(10, 70, 15, 5); return;
      case 4:  DoGauntletBoonList(0, 70, 25, 5); return;
      case 5:  DoGauntletBoonList(0, 50, 35, 15); return;
   }
   return;
}

void ScrCmd_LoadGauntletBoonInVarResultToboosboog(struct ScriptContext *ctx)
{
    u8 id = VarGet(VAR_RESULT);

    enum BoonType boon = BoonList[id].boonType;
    VarSet(VAR_0x8005, BoonList[id].special);//item, flag, etc.
    VarSet(VAR_0x8007, boon); // Used by the switch we returnto after dynmultistack
    VarSet(VAR_0x8008, BoonList[id].altar);

    /*
    switch (boon)
    {
        case BOON_30_BERRIES:
        case BOON_TERRAIN_SEEDS:
        case BOON_10XITEM:
        case BOON_XATTACKXSPECIAL:
        case BOON_XDEFXSPDEF:
        case BOON_10IRON10HPUP10ZINC:
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
    */
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
    if (isCapped >= 3)
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
        devotion_weight[0] = 0;

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
    u32 j = 0;
    do {
        j++;
        switch (type)
        {
        case TYPE_SAPROTROPH:
            switch (rarity)
            {
            case RARITY_STAPLE:
                i = 1 + Random() % (NEREID_STAPLE); break;
            case RARITY_COMMON:
                i = SAPROTROPH_COMMON + Random() % (NEREID_COMMON - SAPROTROPH_COMMON); break;
            default:
            case RARITY_RARE:
                i = SAPROTROPH_RARE + Random() % (NEREID_RARE - SAPROTROPH_RARE); break;
            case RARITY_EPIC:
                i = SAPROTROPH_EPIC + Random() % (NEREID_EPIC - SAPROTROPH_EPIC); break;
            }
            break;

        case TYPE_NEREID:
            switch (rarity)
            {
            case RARITY_STAPLE:
                i = NEREID_STAPLE + Random() % (ELDWYRM_STAPLE - NEREID_STAPLE); break;
            case RARITY_COMMON:
                i = NEREID_COMMON + Random() % (ELDWYRM_COMMON - NEREID_COMMON); break;
            default:
            case RARITY_RARE:
                i = NEREID_RARE + Random() % (ELDWYRM_RARE - NEREID_RARE); break;
            case RARITY_EPIC:
                i = NEREID_EPIC + Random() % (ELDWYRM_EPIC - NEREID_EPIC); break;
            }
            break;

        case TYPE_ELDWYRM:
            switch (rarity)
            {
            case RARITY_STAPLE:
                i = ELDWYRM_STAPLE + Random() % (DSOTM_STAPLE - ELDWYRM_STAPLE); break;
            case RARITY_COMMON:
                i = ELDWYRM_COMMON + Random() % (DSOTM_COMMON - ELDWYRM_COMMON); break;
            default:
            case RARITY_RARE:
                i = ELDWYRM_RARE + Random() % (DSOTM_RARE - ELDWYRM_RARE); break;
            case RARITY_EPIC:
                i = ELDWYRM_EPIC + Random() % (DSOTM_EPIC - ELDWYRM_EPIC); break;
            }
            break;
        case TYPE_DSOTM:
            switch (rarity)
            {
            case RARITY_STAPLE:
                i = DSOTM_STAPLE + Random() % (MONOLITH_STAPLE - DSOTM_STAPLE); break;
            case RARITY_COMMON:
                i = DSOTM_COMMON + Random() % (MONOLITH_COMMON - DSOTM_COMMON); break;
            default:
            case RARITY_RARE:
                i = DSOTM_RARE + Random() % (MONOLITH_RARE - DSOTM_RARE); break;
            case RARITY_EPIC:
                i = DSOTM_EPIC + Random() % (MONOLITH_EPIC - DSOTM_EPIC); break;
            }
            break;
        case TYPE_MONOLITH:
            switch (rarity)
            {
            case RARITY_STAPLE:
                i = MONOLITH_STAPLE + Random() % (WINGED_LION_STAPLE - MONOLITH_STAPLE); break;
            case RARITY_COMMON:
                i = MONOLITH_COMMON + Random() % (WINGED_LION_COMMON - MONOLITH_COMMON); break;
            default:
            case RARITY_RARE:
                i = MONOLITH_RARE + Random() % (WINGED_LION_RARE - MONOLITH_RARE); break;
            case RARITY_EPIC:
                i = MONOLITH_EPIC + Random() % (WINGED_LION_EPIC - MONOLITH_EPIC); break;
            }
            break;
        case TYPE_WINGED_LION:
            switch (rarity)
            {
            case RARITY_STAPLE:
                i = WINGED_LION_STAPLE + Random() % (SAPROTROPH_COMMON - WINGED_LION_STAPLE); break;
            case RARITY_COMMON:
                i = WINGED_LION_COMMON + Random() % (SAPROTROPH_RARE - UNIVERSAL_COMMON); break;
            default:
            case RARITY_RARE:
                i = WINGED_LION_RARE + Random() % (SAPROTROPH_EPIC - UNIVERSAL_RARE); break;
            case RARITY_EPIC:
                i = WINGED_LION_EPIC + Random() % (GB_LENGTH - WINGED_LION_EPIC); break;
            }
            break;
        default:
        case TYPE_COLOURLESS:
            switch (rarity)
            {
            case RARITY_STAPLE:
                i = Random() % (SAPROTROPH_COMMON - SAPROTROPH_STAPLE); break;
            case RARITY_COMMON:
                i = SAPROTROPH_COMMON + Random() % (SAPROTROPH_RARE - SAPROTROPH_COMMON); break;
            default:
            case RARITY_RARE:
                i = SAPROTROPH_RARE + Random() % (SAPROTROPH_EPIC - SAPROTROPH_RARE); break;
            case RARITY_EPIC:
                i = SAPROTROPH_EPIC + Random() % (GB_LENGTH - SAPROTROPH_EPIC); break;
            }
            break;
        }
        if (j>20)
            rarity++;// hence we default rarity_rare.
    } while ((i == choice1 || i == choice2 || i == choice3 || i == choice4 || i == choice5 || i == choice6 || i == choice7 || i == choice8 
|| i == MultichoiceOptions[1] || i == MultichoiceOptions[2] || i == MultichoiceOptions[3]|| i == MultichoiceOptions[0] 
|| BoonList[i].boonType == BOON_NULL)); 
    return i;
}



void ScrCmd_SetGauntletVarStartingStatus(void)
{
    u32 NewStatus = VarGet(VAR_0x8005);
    u32 ExistingStatus = VarGet(VAR_GAUNTLET_STARTING_STATUS);
    NewStatus = (1 << NewStatus);// to bitshift
    if (NewStatus & 3)// if in the first 2 terrain bytes
    {
        ExistingStatus = (ExistingStatus & 65536 << 2);// clear those bytes on existingstatus. Only one terrain at a time
        u16 weather = VarGet(VAR_GAUNTLET_WEATHER);
        if (weather == WEATHER_FOG_HORIZONTAL)
            VarSet(VAR_GAUNTLET_WEATHER, WEATHER_SUNNY);
        else if (weather == WEATHER_RAIN_THUNDERSTORM)
            VarSet(VAR_GAUNTLET_WEATHER, WEATHER_RAIN);
    }
    NewStatus = (ExistingStatus | NewStatus);
    VarSet(VAR_GAUNTLET_STARTING_STATUS,  NewStatus);
}