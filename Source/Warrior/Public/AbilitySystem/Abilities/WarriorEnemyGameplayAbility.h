// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "WarriorEnemyGameplayAbility.generated.h"

//增加前置声明
class AWarriorEnemyCharacter;
class UEnemyCombatComponent;
/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorEnemyGameplayAbility : public UWarriorGameplayAbility
{
	GENERATED_BODY()

public:
	//创建需要用的辅助函数
	//获取敌人角色类
	UFUNCTION( BlueprintPure , Category="Warrior|Ability")
	AWarriorEnemyCharacter* GetEnemyCharacterFromActorInfo();

	/*UFUNCTION()*/

	//获取EnemyCombat
	UFUNCTION( BlueprintPure , Category="Warrior|Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

private:
	//声明临时的EnemyCharacter变量
	TWeakObjectPtr<AWarriorEnemyCharacter> CachedWarriorEnemyCharacter;
	//声明临时的EnemyCombat变量
	TWeakObjectPtr<UEnemyCombatComponent> CachedEnemyCombatComponent;
	
};
