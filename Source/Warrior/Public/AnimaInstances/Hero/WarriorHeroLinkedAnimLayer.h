// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AnimaInstances/WarriorBaseAnimInstance.h"
#include "WarriorHeroLinkedAnimLayer.generated.h"

//添加HeroAnimIUnstance的前置声明
class UWarriorHeroAnimInstance;

/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorHeroLinkedAnimLayer : public UWarriorBaseAnimInstance
{
	GENERATED_BODY()

public:
	//创建一个可供蓝图调用的函数
	UFUNCTION( BlueprintPure , meta = (BlueprintThreadSafe) )
	UWarriorHeroAnimInstance* GetHeroAnimInstance() const;
	
};
