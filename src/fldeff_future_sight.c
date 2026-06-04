#include "global.h"
#include "decompress.h"
#include "event_data.h"
#include "event_scripts.h"
#include "field_effect.h"
#include "field_player_avatar.h"
#include "field_screen_effect.h"
#include "field_weather.h"
#include "fldeff.h"
#include "malloc.h"
#include "mirage_tower.h"
#include "palette.h"
#include "party_menu.h"
#include "script.h"
#include "sound.h"
#include "sprite.h"
#include "task.h"
#include "wild_encounter.h"
#include "util.h"
#include "constants/field_effects.h"
#include "constants/rgb.h"
#include "constants/songs.h"


// static functions
static void FieldCallback_FutureSight(void);
static void StartRototillerFieldEffect(void);
static void Rototiller2Blend(u8 taskId);
static void Rototiller3Blend(u8 taskId);

// text
bool32 SetUpFieldMove_FutureSight(void)
{
    gFieldCallback2 = FieldCallback_PrepareFadeInFromMenu;
    gPostMenuFieldCallback = FieldCallback_FutureSight;
    return TRUE;
}


static void FieldCallback_FutureSight(void)
{
    gFieldEffectArguments[0] = GetCursorSelectionMonId();
    ScriptContext_SetupScript(EventScript_UseFutureSight);
}

bool8 FldEff_UseFutureSight(void)
{
    u8 taskId;

    SetWeatherScreenFadeOut();
    taskId = CreateFieldMoveTask();
    gTasks[taskId].data[8] = (u32)StartRototillerFieldEffect >> 16;
    gTasks[taskId].data[9] = (u32)StartRototillerFieldEffect;
    return FALSE;
}

#define tPalBuffer1 data[1]
#define tPalBuffer2 data[2]

void StartRototillerFieldEffect(void)
{
    void *palBuffer;
    u32 taskId;
    u32 palettes = ~(1 << (gSprites[GetPlayerAvatarSpriteId()].oam.paletteNum + 16) | (1 << 13) | (1 << 14) | (1 << 15));

    PlaySE(SE_M_EARTHQUAKE);
    palBuffer = Alloc(PLTT_SIZE);
    CpuFastCopy(gPlttBufferUnfaded, palBuffer, PLTT_SIZE);
    CpuFastCopy(gPlttBufferFaded, gPlttBufferUnfaded, PLTT_SIZE);
    BeginNormalPaletteFade(palettes, 4, 0, 8, RGB(18,20,6));
    taskId = CreateTask(Rototiller2Blend, 0);
    gTasks[taskId].data[0] = 0;
    StoreWordInTwoHalfwords((u16 *)&gTasks[taskId].tPalBuffer1, (u32) palBuffer);
    FieldEffectActiveListRemove(FLDEFF_USE_FUTURE_SIGHT);
}

static void *GetPalBufferPtr(u32 taskId)
{
    u32 palBuffer;

    LoadWordFromTwoHalfwords((u16 *)&gTasks[taskId].tPalBuffer1, &palBuffer);
    return (void *) palBuffer;
}

static void FreeDestroyTask(u32 taskId)
{
    Free(GetPalBufferPtr(taskId));
    DestroyTask(taskId);
}

static void Rototiller2Blend(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        ClearMirageTowerPulseBlendEffect();
        BlendPalettes(0x00000040, 8, RGB(18,20,6));
        if (gTasks[taskId].data[0] == 64)
        {
            gTasks[taskId].data[0] = 0;
            gTasks[taskId].func = Rototiller3Blend;
            BeginNormalPaletteFade(~(1 << (gSprites[GetPlayerAvatarSpriteId()].oam.paletteNum + 16)), 4, 8, 0, RGB_GREEN);
            TryStartMirageTowerPulseBlendEffect();
        }
        else
        {
            gTasks[taskId].data[0]++;
        }
    }
}

static void Rototiller3Blend(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        CpuFastCopy(GetPalBufferPtr(taskId), gPlttBufferUnfaded, PLTT_SIZE);
        SetWeatherPalStateIdle();
        ScriptContext_SetupScript(EventScript_RototillerDone);
        FreeDestroyTask(taskId);
    }
}

#undef tPalBuffer1
#undef tPalBuffer2