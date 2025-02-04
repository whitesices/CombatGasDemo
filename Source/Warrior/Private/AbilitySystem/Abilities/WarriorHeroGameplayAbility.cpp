// WSL All Rights Reserved


#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"
#include "Characters/WarriorHeroCharacter.h"
#include "PlayerController/WarriorHeroController.h"
#include "Components/Combat/HeroCombatComponent.h"

AWarriorHeroCharacter* UWarriorHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
	//检查角色变量的有效性
	if (!CachedWarriorHeroCharcater.IsValid())
	{
		CachedWarriorHeroCharcater = Cast<AWarriorHeroCharacter>(CurrentActorInfo->AvatarActor);
	}
	
	return CachedWarriorHeroCharcater.IsValid() ? CachedWarriorHeroCharcater.Get() : nullptr;
}

AWarriorHeroController* UWarriorHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
	//判断缓存的Controller是否有效
	if (!CachedWarriorHeroController.IsValid())
	{
		CachedWarriorHeroController = Cast<AWarriorHeroController>( CurrentActorInfo->PlayerController);
	}
	return CachedWarriorHeroController.IsValid() ? CachedWarriorHeroController.Get() : nullptr;
}

UHeroCombatComponent* UWarriorHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
	return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}
