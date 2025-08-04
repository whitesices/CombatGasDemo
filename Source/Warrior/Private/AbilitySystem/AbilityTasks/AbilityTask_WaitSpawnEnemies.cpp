// WSL All Rights Reserved


#include "AbilitySystem/AbilityTasks/AbilityTask_WaitSpawnEnemies.h"
#include "AbilitySystemComponent.h"//引入游戏系统组件
#include "Characters/WarriorEnemyCharacter.h"//引入自定义的敌人类
#include "Engine/AssetManager.h"
#include "NavigationSystem.h"

#include "WarriorDebugHelper.h"//引入辅助函数

UAbilityTask_WaitSpawnEnemies* UAbilityTask_WaitSpawnEnemies::WaitSpawnEnemies(UGameplayAbility* OwningAbility, FGameplayTag EventTag, TSoftClassPtr<AWarriorEnemyCharacter> SoftEnemyClassToSpawn, 
    int32 NumToSpawn, const FVector& SpawnOrigin, float RandomSpawnRadius/*, const FRotator& SpawnRotation*/)
{
    //Node变量
    UAbilityTask_WaitSpawnEnemies* Node = NewAbilityTask<UAbilityTask_WaitSpawnEnemies>( OwningAbility );

    Node->CachedGameplayTag = EventTag;
    Node->CachedSoftEnemyClass = SoftEnemyClassToSpawn;
    Node->CachedNumToSpawn = NumToSpawn;
    Node->CachedSpawnOrigin = SpawnOrigin;
    Node->CachedRandomSpawnRadius = RandomSpawnRadius;
   /* Node->CachedSpawnRotation = SpawnRotation;*/
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
    //检查存储的敌人类是否为空
    if ( ensure( !CachedSoftEnemyClass.IsNull() ) )//通过ensure来报告敌人类的存在
    {
        UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
            CachedSoftEnemyClass.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &ThisClass::OnEnemyClassLoaded)
        );
    }
    else
    {
        if (ShouldBroadcastAbilityTaskDelegates())
        {
            DidNotSpawn.Broadcast( TArray<AWarriorEnemyCharacter*>() );
        }

        EndTask();//结束任务
    }


    
}

void UAbilityTask_WaitSpawnEnemies::OnEnemyClassLoaded()
{
    UClass* LoadedClass = CachedSoftEnemyClass.Get();
    UWorld* CurrentWorld = GetWorld();//获取当前的世界

    if ( !LoadedClass || !CurrentWorld)//检查当前的世界和或敌人类是否有效
    {
        if (ShouldBroadcastAbilityTaskDelegates())
        {
            DidNotSpawn.Broadcast( TArray<AWarriorEnemyCharacter*>() );
        }

        EndTask();//结束任务
        return;
    }

    TArray<AWarriorEnemyCharacter*> SpawnedEnemies;

    FActorSpawnParameters SpawnParam;
    SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

    //循环生成数
    for (int32 i = 0 ; i < CachedNumToSpawn ; i++ )
    {
        FVector RandomLocation;
        UNavigationSystemV1::K2_GetRandomReachablePointInRadius( this , 
            CachedSpawnOrigin , RandomLocation , CachedRandomSpawnRadius);

        RandomLocation += FVector( 0.f , 0.f , 150.f);
        //获取新的Rotation
        const FRotator SpawnFacingRotation = AbilitySystemComponent->GetAvatarActor()->GetActorForwardVector().ToOrientationRotator();

        AWarriorEnemyCharacter* SpawnEnemy = CurrentWorld->SpawnActor<AWarriorEnemyCharacter>(LoadedClass, 
            RandomLocation , SpawnFacingRotation, SpawnParam );

        if (SpawnEnemy)
        {
            SpawnedEnemies.Emplace(SpawnEnemy);//存储记录SpawnEnemy
        }
    }

    if ( ShouldBroadcastAbilityTaskDelegates() )
    {
        if (!(SpawnedEnemies.Num() == 0))
        {
            OnSpawnFinished.Broadcast(SpawnedEnemies);
        }
        else
        {
            DidNotSpawn.Broadcast( TArray<AWarriorEnemyCharacter*>() );
        }
    }

    EndTask();
}
