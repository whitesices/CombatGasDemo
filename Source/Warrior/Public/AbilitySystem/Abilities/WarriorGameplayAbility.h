// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
//引入公用的枚举类型头文件
#include "WarriorTypes/WarriorEnumTypes.h"

#include "WarriorGameplayAbility.generated.h"

class UPawnCombatComponent;
class UWarriorAbilitySystemComponent;

//声明一个枚举类型
UENUM(BlueprintType)
enum class EWarriorAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	//重载GiveAbility, Begin UGameplayAbility Interface
	virtual void OnGiveAbility( const FGameplayAbilityActorInfo* ActorInfo,const FGameplayAbilitySpec& Spec) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//end UGameplayAbility Interface

	UPROPERTY( EditDefaultsOnly , Category = "WarriorAbility" )
	EWarriorAbilityActivationPolicy AbilityActivationPolicy = EWarriorAbilityActivationPolicy::OnTriggered;
	
	UFUNCTION( BlueprintPure , Category = "Warrior|Ability" )
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	UFUNCTION( BlueprintPure , Category = "Warrior|Ability")
	UWarriorAbilitySystemComponent* GetWarriorAbilitySystemComponentFromActorInfo() const;

	//新声明创建一个新的辅助函数在角色和敌人都可以调用

	//先新建一个C++内部调用的激活GE句柄函数
	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget( AActor* TargetActor , const FGameplayEffectSpecHandle& InSpecHandle );

	//建立一个暴露给蓝图使用的函数
	UFUNCTION( BlueprintCallable , Category = "Warrior|Ability"  , meta = ( DisplayName = "Apply Gameplay Effect Spec Handle To Target Actor ", ExpandEnumAsExecs = "OutSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle , EWarriorSuccessType& OutSuccessType );

};
