// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
#include "PawnUIComponent.generated.h"

//声明一个动态多播来传递参数
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnPercentChangedDelegate ,float ,NewPercent );

/**
 * 
 */
UCLASS()
class WARRIOR_API UPawnUIComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
	//声明百分比变化的委托变量
	UPROPERTY( BlueprintAssignable )
	FOnPercentChangedDelegate OnCurrentHealthChanged;

	
};
