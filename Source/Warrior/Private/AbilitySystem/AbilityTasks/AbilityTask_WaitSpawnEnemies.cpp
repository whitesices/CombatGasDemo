// WSL All Rights Reserved


#include "AbilitySystem/AbilityTasks/AbilityTask_WaitSpawnEnemies.h"
#include "AbilitySystemComponent.h"//引入游戏系统组件

#include "WarriorDebugHelper.h"//引入辅助函数

UAbilityTask_WaitSpawnEnemies* UAbilityTask_WaitSpawnEnemies::WaitSpawnEnemies(UGameplayAbility* OwningAbility, FGameplayTag EventTag, TSoftClassPtr<AWarriorEnemyCharacter> SoftEnemyClassToSpawn, 
    int32 NumToSpawn, const FVector& SpawnOrigin, float RandomSpawnRadius, const FRotator& SpawnRotation)
{
    //Node变量
    UAbilityTask_WaitSpawnEnemies* Node = NewAbilityTask<UAbilityTask_WaitSpawnEnemies>( OwningAbility );

    Node->CachedGameplayTag = EventTag;
    Node->CachedSoftEnemyClass = SoftEnemyClassToSpawn;
    Node->CachedNumToSpawn = NumToSpawn;
    Node->CachedSpawnOrigin = SpawnOrigin;
    Node->CachedRandomSpawnRadius = RandomSpawnRadius;
    Node->CachedSpawnRotation = SpawnRotation;
    return Node;
}

void UAbilityTask_WaitSpawnEnemies::Activate()
{
    FGameplayEventMulticastDelegate& Delegate = AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(CachedGameplayTag);
    DelegateHandle = Delegate.AddUObject( this , &ThisClass::OnGameplayEventReceived);
}

void UAbilityTask_WaitSpawnEnemies::OnDestroy(bool bInOwnerFinished)
{
    FGameplayEventMulticastDelegate& Delegate = AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(CachedGameplayTag);
    Delegate.Remove(DelegateHandle);
    Super::OnDestroy(bInOwnerFinished);
}

void UAbilityTask_WaitSpawnEnemies::OnGameplayEventReceived(const FGameplayEventData* InPayload)
{
    Debug::print(TEXT("Gameplay Event Received"));
    EndTask();//结束任务
}
