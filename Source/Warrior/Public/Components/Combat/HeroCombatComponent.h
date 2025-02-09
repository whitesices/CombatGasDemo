// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "HeroCombatComponent.generated.h"

class AWarriorHeroWeapon;

/**
 * 
 */
UCLASS()
class WARRIOR_API UHeroCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()
public:
	UFUNCTION( BlueprintCallable , Category="Warrior|Combat")
	AWarriorHeroWeapon* GetHeroCarriedWeaponByTag( FGameplayTag InWeaponTag) const;

	// 重写父类的碰撞体单播绑定触发后的回调函数
	virtual void OnHitTargetActor(AActor* HitActor) override;

	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor) override;
};
