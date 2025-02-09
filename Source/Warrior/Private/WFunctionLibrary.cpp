// WSL All Rights Reserved


#include "WFunctionLibrary.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
//引入技能蓝图函数库头文件
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTagContainer.h"
//引入自定义的PawnCombatInterface（中介者模式)
#include "Interfaces/PawnCombatInterface.h"
////引入Combat头文件
#include "Components/Combat/PawnCombatComponent.h"

UWarriorAbilitySystemComponent* UWFunctionLibrary::NativeGetWarriorASCFromActor(AActor* InActor)
{
	//判断输入Actor的有效性
	check(InActor);

	//获取技能系统
	return CastChecked<UWarriorAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));

}

void UWFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{

	//创建局部变量存储abilitySystem
	UWarriorAbilitySystemComponent* ASC = NativeGetWarriorASCFromActor(InActor);

	//判断Gameplay tag是否匹配上
	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void UWFunctionLibrary::RemoveGameplayFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{

	//创建局部变量存储abilitySystem
	UWarriorAbilitySystemComponent* ASC = NativeGetWarriorASCFromActor(InActor);

	//判断Gameplay tag是否匹配上
	if (ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

bool UWFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagCheck)
{
	//判断输入Actor的有效性
	check(InActor);

	//创建局部变量存储abilitySystem
	UWarriorAbilitySystemComponent* ASC = NativeGetWarriorASCFromActor(InActor);

	return ASC->HasMatchingGameplayTag(TagCheck);
}

void UWFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck , EWarriorConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, TagToCheck) ? EWarriorConfirmType::Yes : EWarriorConfirmType::No;

}

UPawnCombatComponent* UWFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	//检查InActor是否有效
	check(InActor);

	//检查继承IPawnInterface的actor，触发并调用获取Combat的方法
	if ( IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor) )
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}

	return nullptr;
}

UPawnCombatComponent* UWFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor, EWarriorValidType& OutValidType)
{
	UPawnCombatComponent* CombatComponent = NativeGetPawnCombatComponentFromActor(InActor);

	OutValidType = CombatComponent ? EWarriorValidType::Valid : EWarriorValidType::InValid;
	return CombatComponent;
}

