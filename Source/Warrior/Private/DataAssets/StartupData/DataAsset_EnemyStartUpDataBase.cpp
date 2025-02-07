// WSL All Rights Reserved


#include "DataAssets/StartupData/DataAsset_EnemyStartUpDataBase.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"

#include "AbilitySystem/Abilities/WarriorEnemyGameplayAbility.h"

void UDataAsset_EnemyStartUpDataBase::GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InWarriorASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InWarriorASCToGive, ApplyLevel);
	if (EnemyCombatAbilitySets.IsEmpty()) return;

	//激活绑定GA 
	for ( const TSubclassOf<UWarriorEnemyGameplayAbility>& AbilityClass : EnemyCombatAbilitySets)
	{
		//判断技能属性集是否有效
		if (!AbilityClass) continue;

		FGameplayAbilitySpec AbilitySpec( AbilityClass );
		AbilitySpec.SourceObject = InWarriorASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		//AbilitySpec.DynamicAbilityTags.AddTag(AbilityClass.InputTag);

		InWarriorASCToGive->GiveAbility(AbilitySpec);
	}
}
