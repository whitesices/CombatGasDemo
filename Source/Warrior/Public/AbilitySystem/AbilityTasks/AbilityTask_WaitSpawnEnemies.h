// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_WaitSpawnEnemies.generated.h"

//前置声明敌人角色
class AWarriorEnemyCharacter;

//声明一个动态多播
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FWaitSpawnEnemiesDelegate , const TArray<AWarriorEnemyCharacter*>& , SpawnedEnemies);
/**
 * 
 */
UCLASS()
class WARRIOR_API UAbilityTask_WaitSpawnEnemies : public UAbilityTask
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Warrior|AbilityTask", meta = (DisplayName = "Wait Gameplay Event And Spawn Enemies", HidePin = "OwningAbility",DefaultToSelf="OwningAbility"
		,BlueprintInternalUseOnly = "true" , NumToSpawn = "1" , RandomSpawnRadius = "200"))
	static UAbilityTask_WaitSpawnEnemies* WaitSpawnEnemies( UGameplayAbility* OwningAbility, FGameplayTag EventTag, TSoftClassPtr<AWarriorEnemyCharacter> SoftEnemyClassToSpawn , 
		int32 NumToSpawn , const FVector& SpawnOrigin , float RandomSpawnRadius /*, const FRotator& SpawnRotation*/);

	//创建委托变量
	UPROPERTY(BlueprintAssignable)
	FWaitSpawnEnemiesDelegate OnSpawnFinished;
	UPROPERTY(BlueprintAssignable)
	FWaitSpawnEnemiesDelegate DidNotSpawn;

	//~Beginplay UGameplayTask Interface
	virtual void Activate() override;//重写激活函数
	virtual void OnDestroy(bool bInOwnerFinished) override;//重写销毁函数
	//~End UGameplayTask Interface

private:
	//缓存GameplayTag
	FGameplayTag CachedGameplayTag;
	//缓存敌人类
	TSoftClassPtr<AWarriorEnemyCharacter> CachedSoftEnemyClass;
	//缓存生成数
	int32 CachedNumToSpawn;
	//缓存原始点
	FVector CachedSpawnOrigin;
	//缓存生成随机半径
	float CachedRandomSpawnRadius;
	//缓存生成时旋转量
	/*FRotator CachedSpawnRotation;*/

	FDelegateHandle DelegateHandle;

	//定义游戏事件接受函数
	void OnGameplayEventReceived( const FGameplayEventData* InPayload );
	//定义敌人加载的函数方法
	void OnEnemyClassLoaded();
};
