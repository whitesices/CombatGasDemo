// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "WarriorHeroGameplayAbility.generated.h"

class AWarriorHeroCharacter;
class AWarriorHeroController;
class UHeroCombatComponent;
/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorHeroGameplayAbility : public UWarriorGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION( BlueprintPure , Category = "Warrior|Ability")
	AWarriorHeroCharacter* GetHeroCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	AWarriorHeroController* GetHeroControllerFromActorInfo();

	UFUNCTION(Blueprintpure , Category = "Warrior|Ability")
	UHeroCombatComponent* GetHeroCombatComponentFromActorInfo();

	//创建定义存储获取GameplayEffectSpecHandele的方法,传入EffectClass,基础伤害值，当前武器类型 ,当前战斗动作索引
	UFUNCTION( BlueprintPure , Category = "Warrior|Ability")
	FGameplayEffectSpecHandle MakeHeroDamageEffectSpecHandle( TSubclassOf<UGameplayEffect> EffectClass , float InWeaponBaseDamage , FGameplayTag InCurrentAttackTypeTag ,int32 InUsedComboCount );

private:
	TWeakObjectPtr<AWarriorHeroCharacter> CachedWarriorHeroCharcater;

	//声明一个Contoller变量
	TWeakObjectPtr<AWarriorHeroController> CachedWarriorHeroController;

	////声明HeroCombatComponent变量
	//TWeakObjectPtr<UHeroCombatComponent> CachedHeroCombatComponent;
};
