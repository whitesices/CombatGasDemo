// WSL All Rights Reserved


#include "AbilitySystem/Abilities/WarriorEnemyGameplayAbility.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "Characters/WarriorEnemyCharacter.h"
//引入自定义的GameplayAbility
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "WarriorGameplayTags.h"

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

FGameplayEffectSpecHandle UWarriorEnemyGameplayAbility::MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat)
{
	//检查Effect类是否有效
	check(EffectClass);

	//声明临时的ContextHandle存储相应信息
	FGameplayEffectContextHandle ContextHandle = GetWarriorAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject( GetAvatarActorFromActorInfo() );
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());
	//获取技能系统组件,并声明一个GameplayEffectSpecHandle局部变量存储
	FGameplayEffectSpecHandle  EffectSpecHandle = GetWarriorAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
		EffectClass,
		GetAbilityLevel(),
		ContextHandle
	);

	//设置按调用方设置的值的大小,set-by-caller是指在运行时传递到Gameplay效果或Gameplay技能的值，旨在用于以某种方式修改效果，通常修改伤害、治疗或受技能影响的任何其他属性。
	EffectSpecHandle.Data->SetSetByCallerMagnitude(WarriorGameplayTags::Shared_SetByCaller_BaseDamage, InDamageScalableFloat.GetValueAtLevel( GetAbilityLevel() ) );

	return EffectSpecHandle;
}
