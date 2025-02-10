// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
//引入公用的结构体头文件
#include "WarriorTypes/WarriorStructTypes.h"

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

	//获取当前武器
	UFUNCTION( BlueprintCallable , Category="Warrior|Combat")
	AWarriorHeroWeapon* GetHeroCurrentEquippedWeapon() const;

	//获取当前武器伤害和等级
	UFUNCTION( BlueprintCallable , Category = "Warrior|Combat")
	float GetHeroCurrentEquippWeaponDamageAtLevel( float InLevel ) const;

	// 重写父类的碰撞体单播绑定触发后的回调函数
	virtual void OnHitTargetActor(AActor* HitActor) override;

	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor) override;
};
