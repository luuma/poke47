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
static void FieldCallback_FadeMove(void);
static void StartFadeMoveFieldEffect(void);

// text
bool32 SetUpFieldMove_FadeMove(void)
{
    if (Overworld_MapTypeAllowsTeleportAndFly(gMapHeader.mapType) == TRUE)
    {
        gFieldCallback2 = FieldCallback_PrepareFadeInFromMenu;
        gPostMenuFieldCallback = FieldCallback_FadeMove;
        return TRUE;
    }
    return FALSE;
}


static void FieldCallback_FadeMove(void)
{
    gFieldEffectArguments[0] = GetCursorSelectionMonId();
    ScriptContext_SetupScript(EventScript_UseFade);
}

bool8 FldEff_UseFadeMove(void)
{
    u8 taskId = CreateFieldMoveTask();

    gTasks[taskId].data[8] = (u32)StartFadeMoveFieldEffect >> 16;
    gTasks[taskId].data[9] = (u32)StartFadeMoveFieldEffect;
    return FALSE;
}

static void StartFadeMoveFieldEffect(void)
{
    FieldEffectActiveListRemove(FLDEFF_USE_FADE);
    ScriptContext_Enable();
}

