#include "global.h"
#include "scrcmd.c"
#include "constants/vars.h"

static const u8 *name GetGauntletBoonName(id);
{
}

static const u8 *name GetGauntletBoonDevotion(id);
{
}

static const u8 *name GetGauntletBoonType(id);
{
}



static bool8 dynmultipushFromGauntletVar(u32 id)
{
    const u8 *name = GetGauntletBoonName(id);

    Script_RequestEffects(SCREFF_V1 | SCREFF_HARDWARE);

    u8 *nameBuffer = Alloc(100);
    struct ListMenuItem item;
    StringExpandPlaceholders(nameBuffer, name);
    item.name = nameBuffer;
    item.id = id;
    MultichoiceDynamic_PushElement(item);
    return FALSE;
}

#define NUM_GAUNTLET_DEITIES 6
#define NUM_GAUNTLET_OPTION_COLOURS 7

enum GauntletTypes
{
    TYPE_SAPHROTROPH = 0,
    TYPE_NEREID = 1,
    TYPE_ELDWYRM = 2,
    TYPE_DSOTM = 3,
    TYPE_MONOLITH =4,
    TYPE_WINGED_LION =5,
    TYPE_COLOURLESS = 6,
    TYPE_DEVOTION_LENGTH = TYPE_COLOURLESS,
    TYPE_GAUNTLET_LENGTH,
};

enum GauntletRarity
{
    RARITY_STAPLE = 0,
    RARITY_COMMON = 1,
    RARITY_RARE = 2,
    RARITY_EPIC = 3,
    RARITY_LENGTH,
};

static void ScrCmd_DoGauntletBoonList(struct ScriptContext *ctx)
{
}

static void DoGauntletBoonList(u8 stapleWeight, u8 commonWeight, u8 rareWeight, u8 epicWeight)
{
    u32 devotions1 = VarGet(VAR_GAUNTLET_BITFIELD_1);
    u32 devotions2 = VarGet(VAR_GAUNTLET_BITFIELD_2);

    u8 playerDevotions[TYPE_DEVOTION_LENGTH] =
    {
        [TYPE_SAPHROTROPH] = devotions1 & 0b11;
        [TYPE_NEREID] = devotions1 & 0b1100;
        [TYPE_ELDWYRM] = devotions1 & 0b110000;
        [TYPE_DSOTM] = devotions1 & 0b11000000;
        [TYPE_MONOLITH] = devotions2 & 0b11;
        [TYPE_WINGED_LION] = devotions2 & 0b11100,
    };
    bool32 isCapped = devotions2 & 0b100000;
    u8 MultichoiceOptions[4] = {0, 0, 0, 0};
    u8 devotion_weight[4] = {20, 20, 20, 20};
    u8 rarity_weight[4] = {stapleWeight, commonWeight, rareWeight, epicWeight};

    if (isCapped)
        devotion_weight[1] = 0;
    for (u32 menuNum=0; menuNum < 4; menuNum++)
    {
        enum GauntletRarity rarity = u8 RandomWeightedIndex(rarity_weight, RARITY_LENGTH)// of max devotion
        u32 devotionNeeded = u8 RandomWeightedIndex(devotion_weight, 4)// of max devotion
        s32 startpoint = -5 + Random() % (10)
        bool32 shouldAddRandom = TRUE;
        for (u32 i=0; i < TYPE_DEVOTION_LENGTH; i++)
        {
            u32 deity = abs((startpoint + i) % TYPE_DEVOTION_LENGTH) - 1 // a random number between 0 and 5 ascending or descending with i.
            if (playerDevotions[deity] >= devotionNeeded)
            {
                id = GetGauntletBoon(deity, rarity, MultichoiceOptions);
                dynmultipushFromGauntletVar(id);
                shouldAddRandom = FALSE;
                break;
            }
            else
            {
                continue;
            }
        }
        if (shouldAddRandom)
        {
            id = GetGauntletBoon(TYPE_COLOURLESS, rarity, MultichoiceOptions);
            dynmultipushFromGauntletVar(id);
        }
        MultichoiceOptions[menuNum] = id;
    }
}


static u8 GetGauntletBoon(Enum GauntletTypes type, enum GauntletRarity rarity, u8 MultichoiceOptions[4])
{
    u32 choice1 = VarGet(VAR_GAUNTLET_1);
    u32 choice2 = VarGet(VAR_GAUNTLET_2);
    u32 choice3 = VarGet(VAR_GAUNTLET_3);
    u32 choice4 = VarGet(VAR_GAUNTLET_4);
    u32 choice5 = VarGet(VAR_GAUNTLET_5);
    u32 choice6 = VarGet(VAR_GAUNTLET_6);
    u32 choice7 = VarGet(VAR_GAUNTLET_7);
    u32 choice8 = VarGet(VAR_GAUNTLET_8);
    u32 choice9 = VarGet(VAR_GAUNTLET_9);
    u32 i = 0
    do {
        switch (type)
        {
        case TYPE_SAPHROTROPH:
            switch (rarity)
            {
            case RARITY_STAPLE:
                i = Random() % (2)
            case RARITY_COMMON:
                i = SAPH_COMMON + Random() % (NEREID_COMMON - SAPH_COMMON)
            case RARITY_RARE:
                i = SAPH_RARE + Random() % (NEREID_RARE - SAPH_RARE)
            case RARITY_EPIC:
                i = SAPH_EPIC + Random() % (NEREID_EPIC - SAPH_EPIC)
            }
            break;

        case TYPE_NEREID:
            switch (rarity)
            {
            case RARITY_STAPLE:
                i = NEREID_STAPLE + Random() % (ELDWYRM_STAPLE - NEREID_STAPLE);
            case RARITY_COMMON:
                i = NEREID_COMMON + Random() % (ELDWYRM_COMMON - NEREID_COMMON)
            case RARITY_RARE:
                i = NEREID_RARE + Random() % (ELDWYRM_RARE - NEREID_RARE)
            case RARITY_EPIC:
                i = NEREID_EPIC + Random() % (ELDWYRM_EPIC - NEREID_EPIC)
            }
            break;

        case TYPE_ELDWYRM:
            switch (rarity)
            {
            case RARITY_STAPLE:
                i = ELDWYRM_STAPLE + Random() % (DSOTM_STAPLE - ELDWYRM_STAPLE);
            case RARITY_COMMON:
                i = ELDWYRM_COMMON + Random() % (DSOTM_COMMON - ELDWYRM_COMMON)
            case RARITY_RARE:
                i = ELDWYRM_RARE + Random() % (DSOTM_RARE - ELDWYRM_RARE)
            case RARITY_EPIC:
                i = ELDWYRM_EPIC + Random() % (DSOTM_EPIC - ELDWYRM_EPIC)
            }
            break;



        case TYPE_DSOTM:

        case TYPE_MONOLITH:

        case TYPE_WINGED_LION:

        case TYPE_COLOURLESS:
            switch (rarity)
            {
            case RARITY_STAPLE:
                i = Random() % (SAPH_COMMON - SAPH_STAPLE);
            case RARITY_COMMON:
                i = SAPH_COMMON + Random() % (SAPH_RARE - SAPH_COMMON)
            case RARITY_RARE:
                i = SAPH_RARE + Random() % (SAPH_EPIC - SAPH_RARE)
            case RARITY_EPIC:
                i = SAPH_EPIC + Random() % (BOON_LENGTH - SAPH_EPIC)
            }
            break;
        }
    } while (i == choice1 || i == choice2 || i == choice3 || i == choice4 || i == choice5 || i == choice6 || i == choice7 || i == choice8 || i == choice9 
    || i = MultichoiceOptions[1] || i = MultichoiceOptions[2] || i = MultichoiceOptions[3]|| i = MultichoiceOptions[4]); 
    return i;
}



const struct FieldMoveInfo gFieldMoveInfo[FIELD_MOVES_COUNT] =
{
    [FIELD_MOVE_CUT] =
    {
        .fieldMoveFunc = SetUpFieldMove_Cut,
        .isUnlockedFunc = IsFieldMoveUnlocked_Cut,
        .moveID = MOVE_CUT,
        .partyMsgID = PARTY_MSG_NOTHING_TO_CUT,
    },

    [FIELD_MOVE_FLASH] =
    {
        .fieldMoveFunc = SetUpFieldMove_Flash,
        .isUnlockedFunc = IsFieldMoveUnlocked_Flash,
        .moveID = MOVE_FLASH,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
    },

    [FIELD_MOVE_ROCK_SMASH] =
    {
        .fieldMoveFunc = SetUpFieldMove_RockSmash,
        .isUnlockedFunc = IsFieldMoveUnlocked_RockSmash,
        .moveID = MOVE_ROCK_SMASH,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
    },

    [FIELD_MOVE_STRENGTH] =
    {
        .fieldMoveFunc = SetUpFieldMove_Strength,
        .isUnlockedFunc = IsFieldMoveUnlocked_Strength,
        .moveID = MOVE_STRENGTH,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
    },

    [FIELD_MOVE_SURF] =
    {
        .fieldMoveFunc = SetUpFieldMove_Surf,
        .isUnlockedFunc = IsFieldMoveUnlocked_Surf,
        .moveID = MOVE_SURF,
        .partyMsgID = PARTY_MSG_CANT_SURF_HERE,
    },

    [FIELD_MOVE_FLY] =
    {
        .fieldMoveFunc = SetUpFieldMove_Fly,
        .isUnlockedFunc = IsFieldMoveUnlocked_Fly,
        .moveID = MOVE_FLY,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
    },

    [FIELD_MOVE_DIVE] =
    {
        .fieldMoveFunc = SetUpFieldMove_Dive,
        .isUnlockedFunc = IsFieldMoveUnlocked_Dive,
        .moveID = MOVE_DIVE,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
    },

    [FIELD_MOVE_WATERFALL] =
    {
        .fieldMoveFunc = SetUpFieldMove_Waterfall,
        .isUnlockedFunc = IsFieldMoveUnlocked_Waterfall,
        .moveID = MOVE_WATERFALL,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
    },

    [FIELD_MOVE_TELEPORT] =
    {
        .fieldMoveFunc = SetUpFieldMove_Teleport,
        .isUnlockedFunc = IsFieldMoveUnlocked_Teleport,
        .moveID = MOVE_TELEPORT,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
    },

    [FIELD_MOVE_DIG] =
    {
        .fieldMoveFunc = SetUpFieldMove_Dig,
        .isUnlockedFunc = IsFieldMoveUnlocked_Dig,
        .moveID = MOVE_DIG,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
    },

    [FIELD_MOVE_SECRET_POWER] =
    {
        .fieldMoveFunc = SetUpFieldMove_SecretPower,
        .isUnlockedFunc = IsFieldMoveUnlocked_SecretPower,
        .moveID = MOVE_SECRET_POWER,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
    },

    [FIELD_MOVE_NATURE_POWER] =
    {
        .fieldMoveFunc = SetUpFieldMove_SecretPower,
        .isUnlockedFunc = IsFieldMoveUnlocked_SecretPower,
        .moveID = MOVE_NATURE_POWER,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
    },

    [FIELD_MOVE_MILK_DRINK] =
    {
        .fieldMoveFunc = SetUpFieldMove_SoftBoiled,
        .isUnlockedFunc = IsFieldMoveUnlocked_MilkDrink,
        .moveID = MOVE_MILK_DRINK,
        .partyMsgID = PARTY_MSG_NOT_ENOUGH_HP,
    },

    [FIELD_MOVE_SOFT_BOILED] =
    {
        .fieldMoveFunc = SetUpFieldMove_SoftBoiled,
        .isUnlockedFunc = IsFieldMoveUnlocked_SoftBoiled,
        .moveID = MOVE_SOFT_BOILED,
        .partyMsgID = PARTY_MSG_NOT_ENOUGH_HP,
    },

    [FIELD_MOVE_SWEET_SCENT] =
    {
        .fieldMoveFunc = SetUpFieldMove_SweetScent,
        .isUnlockedFunc = IsFieldMoveUnlocked_SweetScent,
        .moveID = MOVE_SWEET_SCENT,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
    },
    [FIELD_MOVE_ROCK_CLIMB] =
    {
        .fieldMoveFunc = SetUpFieldMove_RockClimb,
        .isUnlockedFunc = IsFieldMoveUnlocked_RockClimb,
        .moveID = MOVE_ROCK_CLIMB,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
    },
    [FIELD_MOVE_DEFOG] =
    {
        .fieldMoveFunc = SetUpFieldMove_Defog,
        .isUnlockedFunc = IsFieldMoveUnlocked_Defog,
        .moveID = MOVE_DEFOG,
        .partyMsgID = PARTY_MSG_CANT_USE_HERE,
    },
};
