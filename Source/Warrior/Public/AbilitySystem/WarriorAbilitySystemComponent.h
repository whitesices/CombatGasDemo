// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "WarriorAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	//定义技能按下释放的function
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);

	void OnAbilityInputRelease(const FGameplayTag& InInputTag);
	
};
