// WSL All Rights Reserved

#pragma once
//使用gameplaytag先引入NativegamePlayTags
#include "NativeGameplayTags.h"

//声明一个命名空间
namespace WarriorGameplayTags
{
	//Inputtags
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move)
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look)

	//Player tags
	WARRIOR_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Axe)
}