// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WarriorHeroGameplayAbility.h"
#include "HeroGameplayAbility_TargetLock.generated.h"

//引入自定义的UI类
class UWarriorWidgetBase;
class UInputMappingContext;

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

	//自定义一个给蓝图调用的Update函数
	UFUNCTION(BlueprintCallable,Category="TargetToLock")
	void OnTargetLockTick(float DeltaTime);

	//自定义声明创建供给蓝图使用的目标选择函数
	UFUNCTION(BlueprintCallable,Category="TargetToLock")
	void SwitchTarget( const FGameplayTag& InSwitchDirectionTag);

private:
	//定义一个内部调用的锁定目标方法
	void TryLockOnTarget();
	//定义一个获取有效对象去锁定的方法
	void GetAvailableActorsToLock();
	//从有效对象获取
	AActor* GetNearestTargetFromAvailableActors( const TArray<AActor*>& InAvailableActors );

	//从有效的对象中获取周围的目标
	void GetAvailableActorsAroundTarget( TArray<AActor*>& OutActorsOnLeft , TArray<AActor*>& OutActorsOnRight );

	//绘制目标锁定UI
	void DrawTargetLockWidget();
	//设置锁定UI的位置
	void SetTargetLockWidgetLocation();

	//初始化锁定的移动速度
	void InitTargetLockMovement();
	//初始化键盘上下文
	void InitTargetLockMappingContext();
	//重置锁定速度
	void ResetTargetLockMovement();
	//重置键盘上下文
	void ResetTargetLockMappingContext();

	//定义取消目标技能的函数方法
	void CancelTargetLockAbility();
	//定义清除函数方法
	void CleanUp();

	UPROPERTY(EditDefaultsOnly , Category="Target Lock")
	float BoxTraceDistance = 5000.f;

	UPROPERTY(EditDefaultsOnly,Category="Target Lock")
	FVector TraceBoxSize = FVector( 5000.f , 5000.f , 300.f );

	UPROPERTY(EditDefaultsOnly,Category="Target Lock")
	TArray< TEnumAsByte <EObjectTypeQuery> > BoxTraceChannel;

	UPROPERTY(EditDefaultsOnly,Category="Target Lock")
	bool bShowPersistentDebugShape = false;

	//添加UI绑定
	UPROPERTY(EditDefaultsOnly,Category="Target Lock")
	TSubclassOf<UWarriorWidgetBase> TargetLockUIClass;

	//声明插值速度
	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	float TargetLockRotationInterpSpeed = 5.f;
	//声明可以设置移动速度的变量
	UPROPERTY(EditDefaultsOnly,Category = "Target Lock")
	float TargetLockMaxWalkSpeed = 150.f;
	//声明可以更换InputMappingContext的变量
	UPROPERTY(EditDefaultsOnly, Category = "Target Lock")
	UInputMappingContext* TargetLockMappingContext;


	//声明可以锁定的有效对象
	UPROPERTY()
	TArray<AActor*> AvailableActorsToLock;

	//声明当前锁定对象
	UPROPERTY()
	AActor* CurrentLockedActor;
	//声明绘制的UI变量
	UPROPERTY()
	UWarriorWidgetBase* DrawnTargetLockWidget;

	//定义TargetUI的Size
	UPROPERTY()
	FVector2D TargetLockWidgetSize = FVector2D::ZeroVector;
	//创建一个变量缓存最大移动速度
	UPROPERTY()
	float CacehdDefaultMaxWalkSpeed = 0.f;
};
