#include "global.h"
#include "event_data.h"
#include "field_message_box.h"
#include "pokedex.h"
#include "strings.h"

bool16 ScriptGetPokedexInfo(void)
{
    if (gSpecialVar_0x8004 == 0) // is national dex not present?
    {
        gSpecialVar_0x8005 = GetRegionalPokedexCount(FLAG_GET_SEEN);
        gSpecialVar_0x8006 = GetRegionalPokedexCount(FLAG_GET_CAUGHT);
    }
    else
    {
        gSpecialVar_0x8005 = GetNationalPokedexCount(FLAG_GET_SEEN);
        gSpecialVar_0x8006 = GetNationalPokedexCount(FLAG_GET_CAUGHT);
    }

    return IsNationalPokedexEnabled();
}

bool16 CheckFishVsRod(void)
{
    gSpecialVar_0x8005 = 0;
    if (gSpecialVar_0x8004 > 0) // old rod
    {
	gSpecialVar_0x8006 = 5;
	if (GetSetPokedexFlag(NATIONAL_DEX_FINNEON, FLAG_GET_CAUGHT))
	        gSpecialVar_0x8005++;
	if (GetSetPokedexFlag(NATIONAL_DEX_BASCULIN, FLAG_GET_CAUGHT))
	        gSpecialVar_0x8005++;
	if (GetSetPokedexFlag(NATIONAL_DEX_FROAKIE, FLAG_GET_CAUGHT))
	        gSpecialVar_0x8005++;
	if (GetSetPokedexFlag(NATIONAL_DEX_TYMPOLE, FLAG_GET_CAUGHT))
	        gSpecialVar_0x8005++;
	if (GetSetPokedexFlag(NATIONAL_DEX_DHELMISE, FLAG_GET_CAUGHT))
	        gSpecialVar_0x8005++;
    }
    if (gSpecialVar_0x8004 >= 2) // GOOD rod
    {
	gSpecialVar_0x8006 = 10;
	if (GetSetPokedexFlag(NATIONAL_DEX_CLAUNCHER, FLAG_GET_CAUGHT))
	        gSpecialVar_0x8005++;
	if (GetSetPokedexFlag(NATIONAL_DEX_WISHIWASHI, FLAG_GET_CAUGHT))
	        gSpecialVar_0x8005++;
	if (GetSetPokedexFlag(NATIONAL_DEX_ALOMOMOLA, FLAG_GET_CAUGHT))
	        gSpecialVar_0x8005++;
	if (GetSetPokedexFlag(NATIONAL_DEX_STUNFISK, FLAG_GET_CAUGHT))
	        gSpecialVar_0x8005++;
	if (GetSetPokedexFlag(NATIONAL_DEX_WIMPOD, FLAG_GET_CAUGHT))
	        gSpecialVar_0x8005++;
    }
    if (gSpecialVar_0x8004 >= 3) // SUPER rod
    {
	gSpecialVar_0x8006 = 15;
	if (GetSetPokedexFlag(NATIONAL_DEX_PALPITOAD, FLAG_GET_CAUGHT))
	        gSpecialVar_0x8005++;
	if (GetSetPokedexFlag(NATIONAL_DEX_FROGADIER, FLAG_GET_CAUGHT))
	        gSpecialVar_0x8005++;
	if (GetSetPokedexFlag(NATIONAL_DEX_LUMINEON, FLAG_GET_CAUGHT))
	        gSpecialVar_0x8005++;
	if (GetSetPokedexFlag(NATIONAL_DEX_BRUXISH, FLAG_GET_CAUGHT))
	        gSpecialVar_0x8005++;
	if (GetSetPokedexFlag(NATIONAL_DEX_SKRELP, FLAG_GET_CAUGHT))
	        gSpecialVar_0x8005++;
    }
    return (gSpecialVar_0x8006 == gSpecialVar_0x8005);
}



#define BIRCH_DEX_STRINGS 21

static const u8 *const sBirchDexRatingTexts[BIRCH_DEX_STRINGS] =
{
    gBirchDexRatingText_LessThan10,
    gBirchDexRatingText_LessThan20,
    gBirchDexRatingText_LessThan30,
    gBirchDexRatingText_LessThan40,
    gBirchDexRatingText_LessThan50,
    gBirchDexRatingText_LessThan60,
    gBirchDexRatingText_LessThan70,
    gBirchDexRatingText_LessThan80,
    gBirchDexRatingText_LessThan90,
    gBirchDexRatingText_LessThan100,
    gBirchDexRatingText_LessThan110,
    gBirchDexRatingText_LessThan120,
    gBirchDexRatingText_LessThan130,
    gBirchDexRatingText_LessThan140,
    gBirchDexRatingText_LessThan150,
    gBirchDexRatingText_LessThan160,
    gBirchDexRatingText_LessThan170,
    gBirchDexRatingText_LessThan180,
    gBirchDexRatingText_LessThan190,
    gBirchDexRatingText_LessThan200,
    gBirchDexRatingText_DexCompleted,
};

/// need update to jumps of 20 ish.

// This shows your Hoenn Pokédex rating and not your National Dex.
const u8 *GetPokedexRatingText(u32 count)
{
    u32 i, j;
    u16 maxDex = REGIONAL_DEX_COUNT - 1;
    // doesNotCountForRegionalPokedex
    for (i = 0; i < REGIONAL_DEX_COUNT; i++)
    {
        j = NationalPokedexNumToSpecies(RegionalToNationalOrder(i + 1));
        if (gSpeciesInfo[j].isMythical && !gSpeciesInfo[j].dexForceRequired)
        {
            if (GetSetPokedexFlag(j, FLAG_GET_CAUGHT))
                count--;
            maxDex--;
        }
    }
    return sBirchDexRatingTexts[(count * (BIRCH_DEX_STRINGS - 1)) / maxDex];
}

void ShowPokedexRatingMessage(void)
{
    ShowFieldMessage(GetPokedexRatingText(gSpecialVar_0x8004));
}

// FRLG
extern const u8 PokedexRating_Text_LessThan10[];
extern const u8 PokedexRating_Text_LessThan20[];
extern const u8 PokedexRating_Text_LessThan30[];
extern const u8 PokedexRating_Text_LessThan40[];
extern const u8 PokedexRating_Text_LessThan50[];
extern const u8 PokedexRating_Text_LessThan60[];
extern const u8 PokedexRating_Text_LessThan70[];
extern const u8 PokedexRating_Text_LessThan80[];
extern const u8 PokedexRating_Text_LessThan90[];
extern const u8 PokedexRating_Text_LessThan100[];
extern const u8 PokedexRating_Text_LessThan110[];
extern const u8 PokedexRating_Text_LessThan120[];
extern const u8 PokedexRating_Text_LessThan130[];
extern const u8 PokedexRating_Text_LessThan140[];
extern const u8 PokedexRating_Text_LessThan150[];
extern const u8 PokedexRating_Text_Complete[];

u16 GetFrlgPokedexCount(void)
{
    if (gSpecialVar_0x8004 == 0)
    {
        gSpecialVar_0x8005 = GetKantoPokedexCount(FLAG_GET_SEEN);
        gSpecialVar_0x8006 = GetKantoPokedexCount(FLAG_GET_CAUGHT);
    }
    else
    {
        gSpecialVar_0x8005 = GetNationalPokedexCount(FLAG_GET_SEEN);
        gSpecialVar_0x8006 = GetNationalPokedexCount(FLAG_GET_CAUGHT);
    }
    return IsNationalPokedexEnabled();
}

static const u8 *GetProfOaksRatingMessageByCount(u16 count)
{
    gSpecialVar_Result = FALSE;

    if (count > 0 && GetSetPokedexFlag(NATIONAL_DEX_MEW, FLAG_GET_CAUGHT))
        count--;

    if (count < 10)
        return PokedexRating_Text_LessThan10;

    if (count < 20)
        return PokedexRating_Text_LessThan20;

    if (count < 30)
        return PokedexRating_Text_LessThan30;

    if (count < 40)
        return PokedexRating_Text_LessThan40;

    if (count < 50)
        return PokedexRating_Text_LessThan50;

    if (count < 60)
        return PokedexRating_Text_LessThan60;

    if (count < 70)
        return PokedexRating_Text_LessThan70;

    if (count < 80)
        return PokedexRating_Text_LessThan80;

    if (count < 90)
        return PokedexRating_Text_LessThan90;

    if (count < 100)
        return PokedexRating_Text_LessThan100;

    if (count < 110)
        return PokedexRating_Text_LessThan110;

    if (count < 120)
        return PokedexRating_Text_LessThan120;

    if (count < 130)
        return PokedexRating_Text_LessThan130;

    if (count < 140)
        return PokedexRating_Text_LessThan140;

    if (count < KANTO_DEX_COUNT - 1)
        return PokedexRating_Text_LessThan150;

    gSpecialVar_Result = TRUE;
    return PokedexRating_Text_Complete;
}

void GetProfOaksRatingMessage(void)
{
    ShowFieldMessage(GetProfOaksRatingMessageByCount(gSpecialVar_0x8004));
}

