// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
//引入公用的Enum头文件
#include "WarriorTypes/WarriorEnumTypes.h"

#include "WFunctionLibrary.generated.h"

//引入AbilitySystemComponent的前置声明
class UWarriorAbilitySystemComponent;
struct FGameplayTag;
//引入Combat前置声明
class UPawnCombatComponent;



/**
 * 
 */
UCLASS()
class WARRIOR_API UWFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	//定义获取技能系统组件的方法
	static UWarriorAbilitySystemComponent* NativeGetWarriorASCFromActor(AActor* InActor);

	//创建提供蓝图使用添加GameplayTag的方法
	UFUNCTION(BlueprintCallable , Category = "Warrior|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor , FGameplayTag TagToAdd);

	//创建暴露给蓝图移除GameplayTag的方法
	UFUNCTION( BlueprintCallable , Category = "Warrior|FunctionLibrary")
	static void RemoveGameplayFromActorIfFound( AActor* InActor , FGameplayTag TagToRemove);

	//创建一个方法判断actor是否拥有Tag
	static bool NativeDoesActorHaveTag( AActor* InActor , FGameplayTag TagCheck);

	//创建一个暴露给蓝图使用的方法
	UFUNCTION( BlueprintCallable , Category = "Warrior|FunctionLibrary" , meta = ( DisplayName = "Does Actor Have Tag" , ExpandEnumAsExecs = "OutConfirmType") )
	static void BP_DoesActorHaveTag( AActor* InActor , FGameplayTag TagToCheck , EWarriorConfirmType& OutConfirmType);

	//创建返回PawnCombatCompoennet的函数方法
	static UPawnCombatComponent* NativeGetPawnCombatComponentFromActor( AActor* InActor);

	//定义创建一个暴露给蓝图使用获取PawnCombat的函数方法
	UFUNCTION( BlueprintCallable , Category = "Warrior|FunctionLibrary" , meta = (DisplayName = "GetPawnCombat" , ExpandEnumAsExecs = "OutValidType") )
	static UPawnCombatComponent* BP_GetPawnCombatComponentFromActor( AActor* InActor , EWarriorValidType& OutValidType );

};
