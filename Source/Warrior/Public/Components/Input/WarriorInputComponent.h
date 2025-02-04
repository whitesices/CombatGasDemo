// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
//引入自定义的数据资产
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "WarriorInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	//自定义一个模板函数
	template<class UserObject , typename CallbackFunc>
	void BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig , const FGameplayTag& InInputTag , ETriggerEvent TriggerEvent , UserObject* ContextObject , CallbackFunc callbackfunc);
	
	template<class UserObject , typename CallbackFunc>
	void BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc , CallbackFunc InputReleasedFunc);
};

template<class UserObject, typename CallbackFunc>
inline void UWarriorInputComponent::BindNativeInputAction(const UDataAsset_InputConfig* InInputConfig, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, UserObject* ContextObject, CallbackFunc callbackfunc)
{
	//用断言检查InInputConfig是否有效|
	//Check(InInputConfig);
	//checkf检查有效性的同时，并抛出异常
	checkf( InInputConfig, TEXT("Input config data asset is null , can not processed binding"));

	//若InputAction有效
	if (UInputAction* FoundAction = InInputConfig->FindNativeInputActionByTag(InInputTag))
	{
		//调用绑定函数
		BindAction(FoundAction,TriggerEvent,ContextObject,callbackfunc);
	}


}

template<class UserObject, typename CallbackFunc>
inline void UWarriorInputComponent::BindAbilityInputAction(const UDataAsset_InputConfig* InInputConfig, UserObject* ContextObject, CallbackFunc InputPressedFunc, CallbackFunc InputReleasedFunc)
{
	//用断言检查InInputConfig是否有效|
	//Check(InInputConfig);
	//checkf检查有效性的同时，并抛出异常
	checkf(InInputConfig, TEXT("Input config data asset is null , can not processed binding"));

	for (const FWarriorInputActionConfig& AbilityInputActionConfig : InInputConfig->AbilityInputActions)
	{
		if ( !AbilityInputActionConfig.IsValid() ) continue;
		BindAction( AbilityInputActionConfig.InputAction , ETriggerEvent::Started , ContextObject, InputPressedFunc, AbilityInputActionConfig.InputTag);
		BindAction(AbilityInputActionConfig.InputAction, ETriggerEvent::Completed, ContextObject, InputReleasedFunc, AbilityInputActionConfig.InputTag);
	}
}
