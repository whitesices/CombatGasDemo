// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBase.generated.h"

class UWarriorGameplayAbility;
class UWarriorAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class WARRIOR_API UDataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()

public:
	//重写相应的函数
	virtual void GiveToAbilitySystemComponent( UWarriorAbilitySystemComponent* InWarriorASCToGive , int32 ApplyLevel = 1);
	
protected:
	UPROPERTY( EditDefaultsOnly , Category = "StartUpData")
	TArray<TSubclassOf<UWarriorGameplayAbility> > ActivateOnGivenAbilities;

	UPROPERTY( EditDefaultsOnly , Category = "StartUpData")
	TArray<TSubclassOf<UWarriorGameplayAbility> > ReactiveAbilities;

	void GrantAbilities( const TArray< TSubclassOf<UWarriorGameplayAbility> >& InAbilitiesToGive , UWarriorAbilitySystemComponent* InWarriorASCToGive, int32 ApplyLevel = 1);
};
