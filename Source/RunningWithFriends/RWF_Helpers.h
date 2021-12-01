#pragma once

#define RWF_GET_GAME_INSTANCE URWF_GameInstance* GameInst = Cast<URWF_GameInstance>(GetGameInstance())
#define RWF_LOG UE_LOG()

DECLARE_LOG_CATEGORY_EXTERN(LogRWF, Display, All)
