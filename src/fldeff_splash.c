#include "global.h"
#include "event_scripts.h"
#include "field_effect.h"
#include "field_player_avatar.h"
#include "fldeff.h"
#include "item_use.h"
#include "overworld.h"
#include "party_menu.h"
#include "script.h"
#include "sprite.h"
#include "constants/field_effects.h"

// static functions
static void FieldCallback_Splash(void);
static void StartSplashFieldEffect(void);

// text
bool32 SetUpFieldMove_Splash(void)
{
    gFieldCallback2 = FieldCallback_PrepareFadeInFromMenu;
    gPostMenuFieldCallback = FieldCallback_Splash;
    return TRUE;
}


static void FieldCallback_Splash(void)
{
    gFieldEffectArguments[0] = GetCursorSelectionMonId();
    ScriptContext_SetupScript(EventScript_UseSplash);
}

bool8 FldEff_UseSplash(void)
{
    u8 taskId = CreateFieldMoveTask();

    gTasks[taskId].data[8] = (u32)StartSplashFieldEffect >> 16;
    gTasks[taskId].data[9] = (u32)StartSplashFieldEffect;
    return FALSE;
}

static void StartSplashFieldEffect(void)
{
    FieldEffectActiveListRemove(FLDEFF_USE_SPLASH);
    ScriptContext_Enable();
}

