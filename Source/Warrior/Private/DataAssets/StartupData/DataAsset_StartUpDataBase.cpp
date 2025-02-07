// WSL All Rights Reserved


#include "DataAssets/StartupData/DataAsset_StartUpDataBase.h"

#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
////引入GameplayEffct 的头文件
//#include "GameplayEffect.h"

void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InWarriorASCToGive, int32 ApplyLevel)
{
	//检查传入GameplayAbilitySystem的有效性
	check(InWarriorASCToGive);
	//调用自定义的技能管理函数
	GrantAbilities( ActivateOnGivenAbilities , InWarriorASCToGive , ApplyLevel );
	GrantAbilities(ReactiveAbilities, InWarriorASCToGive, ApplyLevel);

	//判断GameplayEffect数组是否为空
	if ( !StartUpGameplayEffects.IsEmpty() )
	{
		for (const TSubclassOf<UGameplayEffect>& EffectClass : StartUpGameplayEffects)
		{
			//判断GameplayEffect有效性
			if (!EffectClass) continue;

			UGameplayEffect* EffectCDO = EffectClass->GetDefaultObject<UGameplayEffect>();
			//应用GameplayEffect
			InWarriorASCToGive->ApplyGameplayEffectToSelf(
				EffectCDO,
				ApplyLevel,
				InWarriorASCToGive->MakeEffectContext()
			);
		}

	}
}

void UDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UWarriorGameplayAbility>>& InAbilitiesToGive, UWarriorAbilitySystemComponent* InWarriorASCToGive, int32 ApplyLevel)
{
	if (InAbilitiesToGive.IsEmpty())
	{
		return;
	}

	for (const TSubclassOf<UWarriorGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if (!Ability) continue;

		//声明一个Spec变量
		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InWarriorASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;

		InWarriorASCToGive->GiveAbility(AbilitySpec);
	}
}
