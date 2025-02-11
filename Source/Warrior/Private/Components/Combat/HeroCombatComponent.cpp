// WSL All Rights Reserved


#include "Components/Combat/HeroCombatComponent.h"
//引入武器类的头文件
#include "Items/Weapons/WarriorHeroWeapon.h"
//引入AbilitySystemBlueprintFunction
#include "AbilitySystemBlueprintLibrary.h"
//引入GamePlayTag头文件
#include "WarriorGameplayTags.h"

#include "WarriorDebugHelper.h"

AWarriorHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AWarriorHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

AWarriorHeroWeapon* UHeroCombatComponent::GetHeroCurrentEquippedWeapon() const
{
	//调用父类的获取当前角色武器装备
	return Cast<AWarriorHeroWeapon>( GetCharacterCurrentEquippedWeapon() );
}

float UHeroCombatComponent::GetHeroCurrentEquippWeaponDamageAtLevel(float InLevel) const
{
	//获取当前武器的基础伤害值,并返回值和等级
	return GetHeroCurrentEquippedWeapon()->HeroWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
}

void UHeroCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	Debug::print( GetOwningPawn()->GetActorNameOrLabel() + TEXT(" hit ") + HitActor->GetActorNameOrLabel(), FColor::Green);

	//从发生碰撞的数组Actor找到发生碰撞对应的Actor类型
	if ( OverlappedActors.Contains(HitActor) )
	{
		return;
	}

	//将HitActor 加入OverlappedActors
	OverlappedActors.AddUnique(HitActor);

	//声明局部变量gameplayEventData
	FGameplayEventData Data;
	//设置Insigator
	Data.Instigator = GetOwningPawn();
	//设置目标
	Data.Target = HitActor;

	//调用SendGamePlayEvent函数
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
	GetOwningPawn(),
	WarriorGameplayTags::Shared_Event_MeleeHit,
	Data
	);

	//调用SendGameplayEvent函数去触发HitPuase
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		WarriorGameplayTags::Player_Event_HitPause,
		FGameplayEventData()
	);
}

void UHeroCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
	//Debug::print( GetOwningPawn()->GetActorNameOrLabel() + TEXT(" `s weapon pulled from  ") + InteractedActor->GetActorNameOrLabel(), FColor::Red);
	//调用SendGameplayEvent函数去触发HitPuase
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		WarriorGameplayTags::Player_Event_HitPause,
		FGameplayEventData()
	);
}
