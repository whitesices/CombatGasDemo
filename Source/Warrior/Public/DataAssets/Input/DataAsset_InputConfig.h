// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
//引入GameplayTagContainer
#include "GameplayTagContainer.h"
#include "DataAsset_InputConfig.generated.h"

//struct FGameplayTag;
class UInputAction;
class UInputMappingContext;

//声明一个新的结构体
USTRUCT(BlueprintType)
struct FWarriorInputActionConfig
{
	GENERATED_BODY()
public:
	//声明InputTag
	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly , meta=(Categories = "InputTag"))
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly )
	UInputAction* InputAction;
};

/**
 * 
 */
UCLASS()
class WARRIOR_API UDataAsset_InputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	//声明InputMappingContext
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly , BlueprintReadOnly , meta=(TitleProperty = "InputTag"))
	TArray<FWarriorInputActionConfig> NativeInputActions;

	//创建InputAction的函数定义
	UInputAction* FindNativeInputActionByTag(const FGameplayTag& InputTag) const;
	
};
