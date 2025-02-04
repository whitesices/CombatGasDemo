// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartupData/DataAsset_StartUpDataBase.h"
//引入GameplayTagContainer
#include "GameplayTagContainer.h"
#include "DataAsset_HeroStartUpData.generated.h"

USTRUCT(BlueprintType)
struct FWarriorHeroAbilitySet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag;

	//声明自定义的AbilitySystemComponent
	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly)
	TSubclassOf<UWarriorGameplayAbility> AbilityToGrant;

	//创建有效性函数
	bool IsValid() const;
};
/**
 * 
 */
UCLASS()
class WARRIOR_API UDataAsset_HeroStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:
	//重写相应的函数
	virtual void GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InWarriorASCToGive, int32 ApplyLevel = 1) override;

private:
	//声明数组
	UPROPERTY( EditDefaultsOnly , Category = "StartUpData" , meta = (TitleProperty = "InputTag"))
	TArray<FWarriorHeroAbilitySet> HeroStartUpAbilitySets;
	
};
