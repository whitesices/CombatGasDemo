// WSL All Rights Reserved


#include "AbilitySystem/Abilities/WarriorEnemyGameplayAbility.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "Characters/WarriorEnemyCharacter.h"

AWarriorEnemyCharacter* UWarriorEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	//检查缓存的敌人角色变量是否有效
	if (!CachedWarriorEnemyCharacter.IsValid())
	{
		//获取敌人角色类
		CachedWarriorEnemyCharacter = Cast<AWarriorEnemyCharacter>( CurrentActorInfo->AvatarActor );
	}

	return CachedWarriorEnemyCharacter.IsValid() ? CachedWarriorEnemyCharacter.Get() : nullptr ;
}

UEnemyCombatComponent* UWarriorEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	//获取敌人战斗组件
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}
