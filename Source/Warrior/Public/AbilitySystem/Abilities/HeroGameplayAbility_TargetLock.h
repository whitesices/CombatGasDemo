// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"
#include "HeroGameplayAbility_TargetLock.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API UHeroGameplayAbility_TargetLock : public UWarriorHeroGameplayAbility
{
	GENERATED_BODY()

protected:
	//~Begin UGameplayAbility Interface
	//激活技能
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	//结束技能
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~End UGameplayAbility Interface

private:
	//定义一个内部调用的锁定目标方法
	void TryLockOnTarget();
	//定义一个获取有效对象去锁定的方法
	void GetAvailableActorsToLock();

	UPROPERTY(EditDefaultsOnly , Category="Target Lock")
	float BoxTraceDistance = 5000.f;

	UPROPERTY(EditDefaultsOnly,Category="Target Lock")
	FVector TraceBoxSize = FVector( 5000.f , 5000.f , 300.f );

	UPROPERTY(EditDefaultsOnly,Category="Target Lock")
	TArray< TEnumAsByte <EObjectTypeQuery> > BoxTraceChannel;

	UPROPERTY(EditDefaultsOnly,Category="Target Lock")
	bool bShowPersistentDebugShape = false;
};
