// WSL All Rights Reserved


#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"
#include "Characters/WarriorHeroCharacter.h"
#include "PlayerController/WarriorHeroController.h"
#include "Components/Combat/HeroCombatComponent.h"

//引入技能系统组件头文件
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "WarriorGameplayTags.h"

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

FGameplayEffectSpecHandle UWarriorHeroGameplayAbility::MakeHeroDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount)
{
	//检查UGameplayEffect的有效性
	check(EffectClass);

	//填充需要传递的上下文内容句柄
	FGameplayEffectContextHandle  ContextHandle = GetWarriorAbilitySystemComponentFromActorInfo()->MakeEffectContext();

	//设置技能
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(  GetAvatarActorFromActorInfo() );
	ContextHandle.AddInstigator( GetAvatarActorFromActorInfo() , GetAvatarActorFromActorInfo() );

	//获取技能系统组件,并声明一个GameplayEffectSpecHandle局部变量存储
	FGameplayEffectSpecHandle  EffectSpecHandle = GetWarriorAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
		EffectClass,
		GetAbilityLevel(),
		ContextHandle
	);

	//设置按调用方设置的值的大小,set-by-caller是指在运行时传递到Gameplay效果或Gameplay技能的值，旨在用于以某种方式修改效果，通常修改伤害、治疗或受技能影响的任何其他属性。
	EffectSpecHandle.Data->SetSetByCallerMagnitude(WarriorGameplayTags::Shared_SetByCaller_BaseDamage, InWeaponBaseDamage);

	//检查当前武器类型Tag是否有效
	if (InCurrentAttackTypeTag.IsValid())
	{
		//存储当前攻击类型的Tag以及攻击动作索引值
		EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InUsedComboCount);
	}

	return EffectSpecHandle;
}
