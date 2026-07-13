#include "global.h"

#include "event_data.h"
#include "field_specials.h"
#include "item.h"
#include "pokemon_storage_system.h"
#include "pokemon.h"
#include "random.h"
#include "script.h"

#include "constants/agauntlet.h"
#include "constants/vars.h"

static void InitGauntletBagItems(void);
static void RespawnAbout24RandomGauntletItemBalls(void);
static bool32 GauntletPartySetup(void);
static bool32 SquashEarthRibbonInfo(void);


static void RespawnAbout24RandomGauntletItemBalls(void)
{
    u32 i;
    for (i = FLAG_GAUNTLET_3; i <= FLAG_GAUNTLET_BOSS_ALTAR; i++)
        FlagClear(i);
    assertf(FALSE, "RespawnAbout24RandomGauntletItemBalls i=%d", i);
    for (i = 0; i < 34; i++)
        FlagSet(FLAG_GAUNTLET_3 + ((Random()+i) % FLAGS_GAUNTLET));

    return;//Roll 34 random sets in the 48 flags. Giving roughly 48*(1-(47/48)^34) item balls, or 24.04 item balls. But could be anywhere from 1 to 34 removed!
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

static rng_value_t seedBoons;

static void GauntletSeedRng(void)
{
    u32 setup = Random32();
    seedBoss = LocalRandomSeed(setup);
    seedItems = LocalRandomSeed(setup);
    seedItemsmed = LocalRandomSeed(setup);
    seedItemshigh = LocalRandomSeed(setup);
    seedItemsend = LocalRandomSeed(setup);
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

void TryUpdateRocksReveal(void)
{
    if (!FlagGet(FLAG_GAUNTLET_CHALLENGE))
    {
        VarSet(VAR_RESULT, FALSE);
        return;
    }
    if (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(MAP_GAUNTLET_ISLAND_SOUTHWEST)
        && gSaveBlock1Ptr->location.mapNum == MAP_NUM(MAP_GAUNTLET_ISLAND_SOUTHWEST))
    {
        if (FlagGet(FLAG_TEMP_12) && !FlagGet(FLAG_TEMP_11) && FlagGet(FLAG_GAUNTLET_SHOWROCK_1))
            VarSet(VAR_RESULT, 1);

        if (FlagGet(FLAG_TEMP_14) && FlagGet(FLAG_TEMP_15) && !FlagGet(FLAG_TEMP_13) && !FlagGet(FLAG_TEMP_17) && FlagGet(FLAG_GAUNTLET_SHOWROCK_2))
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
        && FlagGet(FLAG_GAUNTLET_SHOWROCK_3))
            VarSet(VAR_RESULT, 3);

        else if (!FlagGet(FLAG_TEMP_11) 
         && !FlagGet(FLAG_TEMP_12)
         && FlagGet(FLAG_TEMP_13)
         && !FlagGet(FLAG_TEMP_14)
         && FlagGet(FLAG_TEMP_15)
         && FlagGet(FLAG_TEMP_16)
         && FlagGet(FLAG_TEMP_17)
         && FlagGet(FLAG_TEMP_18)
        && FlagGet(FLAG_GAUNTLET_SHOWROCK_4))
            VarSet(VAR_RESULT, 4);
    }
    return;
}

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
