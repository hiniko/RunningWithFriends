#pragma once

#define RWF_GET_GAME_INSTANCE URWF_GameInstance* GameInst = Cast<URWF_GameInstance>(GetGameInstance())
#define LOCAL_ROLE_STR *UEnum::GetValueAsName(GetLocalRole()).ToString()
#define REMOTE_ROLE_STR *UEnum::GetValueAsName(GetRemoteRole()).ToString()

DECLARE_LOG_CATEGORY_EXTERN(LogRWF, Display, All)
