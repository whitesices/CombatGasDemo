// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartupData/DataAsset_StartUpDataBase.h"
//引入公共的结构体类型
#include "WarriorTypes/WarriorStructTypes.h"

#include "DataAsset_EnemyStartUpDataBase.generated.h"

class UWarriorGameplayAbility;
class UWarriorAbilitySystemComponent;
class UWarriorEnemyGameplayAbility;

/**
 * 
 */
UCLASS()
class WARRIOR_API UDataAsset_EnemyStartUpDataBase : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()
public:
	//重写技能赋予函数
	virtual void GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InWarriorASCToGive, int32 ApplyLevel = 1) override;
	
private:
	//声明敌人属性集数组
	UPROPERTY( EditDefaultsOnly , Category = "StartUpData" , meta = ( TitleProperty = "InputTag"))
	TArray< TSubclassOf<UWarriorEnemyGameplayAbility> > EnemyCombatAbilitySets;
};
