// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_ExecuteTaskOnTick.generated.h"

//声明多播委托
//DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnAbilityTaskTickDelegate , float , DeltaTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAbilityTaskTickDelegate, float, DeltaTime);

/**
 * 
 */
UCLASS()
class WARRIOR_API UAbilityTask_ExecuteTaskOnTick : public UAbilityTask
{
	GENERATED_BODY()
public:
	//创建委托变量
	UPROPERTY(BlueprintAssignable)
	FOnAbilityTaskTickDelegate OnAbilityTaskTick;
public:
	//声明构造函数
	UAbilityTask_ExecuteTaskOnTick();
	//定义一个函数供外部调用
	UFUNCTION( BlueprintCallable , Category="Warrior|AbilityTasks" , meta = (HidePin="OwningAbility",DefaultToSelf="OwningAbility",BlueprintInternalUseOnly="true") )
	static UAbilityTask_ExecuteTaskOnTick* ExecuteTaskOnTick( UGameplayAbility* OwningAbility );

	//重写该函数 Begin UGameplayTask 
	virtual void TickTask(float DeltaTime) override;
	//end GameplayTask
};
