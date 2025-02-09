// WSL All Rights Reserved


#include "Components/Combat/HeroCombatComponent.h"
//引入武器类的头文件
#include "Items/Weapons/WarriorHeroWeapon.h"

#include "WarriorDebugHelper.h"

AWarriorHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AWarriorHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
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
}

void UHeroCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
	Debug::print( GetOwningPawn()->GetActorNameOrLabel() + TEXT(" `s weapon pulled from  ") + InteractedActor->GetActorNameOrLabel(), FColor::Red);
}
