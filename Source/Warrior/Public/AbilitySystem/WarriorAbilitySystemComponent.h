// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
//引入通用的结构体类型头文件
#include "WarriorTypes/WarriorStructTypes.h"
#include "WarriorAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	//定义技能按下释放的function
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);

	void OnAbilityInputRelease(const FGameplayTag& InInputTag);

	//声明管理武器技能的函数方法
	UFUNCTION( BlueprintCallable , Category = "Warrior|Abilitity" , meta = (ApplyLevel = "1") )
	void GrantHeroWEaponAbilities( const TArray<FWarriorHeroAbilitySet>& InDefaultWeaponAbilities , int32 ApplyLevel , TArray<FGameplayAbilitySpecHandle>&  OutGrantedAbilitySpecHandles );

	//定义移除管理能力的方法
	UFUNCTION( BlueprintCallable , Category = "Warrior|Ability" , meta = (ApplyLevel = "1"))
	void RemoveHeroWEaponAbilities( UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& InSpecHandleToRemove );
	
};
