// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/PawnUIComponent.h"
#include "HeroUIComponent.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API UHeroUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()

public:
	//声明愤怒百分比变化值
	UPROPERTY( BlueprintAssignable )
	FOnPercentChangedDelegate OnCurrentRageChanged;
	
};
