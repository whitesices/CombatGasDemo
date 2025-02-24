// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/PawnUIComponent.h"
#include "HeroUIComponent.generated.h"

//声明一个多播委托来传递图片信息
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnEquippedWeaponChangedDelegate , TSoftObjectPtr<UTexture2D> , SoftWeapon );

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

	//声明武器Icon的委托
	UPROPERTY( BlueprintCallable,BlueprintAssignable )
	FOnEquippedWeaponChangedDelegate OnEquippedWeaponChanged;
	
};
