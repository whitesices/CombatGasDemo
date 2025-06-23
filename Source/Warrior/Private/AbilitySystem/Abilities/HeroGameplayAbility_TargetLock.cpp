// WSL All Rights Reserved


#include "AbilitySystem/Abilities/HeroGameplayAbility_TargetLock.h"
//引入通用系统工具函数库
#include "Kismet/KismetSystemLibrary.h"
//引入MainPlayer
#include "Characters/WarriorHeroCharacter.h"
//引入通用GameplayStatics.h
#include "Kismet/GameplayStatics.h"
//引入UI基类
#include "Widgets/WarriorWidgetBase.h"
////引入英雄角色头文件
#include "Characters/WarriorHeroCharacter.h"
//引入玩家控制类
#include "PlayerController/WarriorHeroController.h"
//引入UI层级头文件
#include "Blueprint/WidgetLayoutLibrary.h"
//引入WidgetTree头文件
#include "Blueprint/WidgetTree.h"
//引入SizeBox头文件
#include "Components/SizeBox.h"
//引入蓝图函数库
#include "WFunctionLibrary.h"
//引入自定义的GameplayTag
#include "WarriorGameplayTags.h"
//引入数学函数库
#include "Kismet/KismetMathLibrary.h"
//引入移动组件头文件
#include "GameFramework/CharacterMovementComponent.h"

//引入DebugHelper头文件
#include "WarriorDebugHelper.h"


void UHeroGameplayAbility_TargetLock::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	//在回调父类方法之前执行锁定目标方法
	TryLockOnTarget();
	InitTargetLockMovement();
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo , TriggerEventData);
}

void UHeroGameplayAbility_TargetLock::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	ResetTargetLockMovement();
	//清除函数调用
	CleanUp();
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

}

void UHeroGameplayAbility_TargetLock::OnTargetLockTick(float DeltaTime)
{
	//判断当前获取的对象是否有效
	if ( !CurrentLockedActor || UWFunctionLibrary::NativeDoesActorHaveTag( CurrentLockedActor , WarriorGameplayTags::Shared_Status_Dead)||
		UWFunctionLibrary::NativeDoesActorHaveTag(GetHeroCharacterFromActorInfo(), WarriorGameplayTags::Shared_Status_Dead))
	{
		CancelTargetLockAbility();
		return;
	}

	//调用设置UI位置的参数
	SetTargetLockWidgetLocation();
	//判断是否需要定向旋转
	const bool bShouldOverrideRotation = 
		!UWFunctionLibrary::NativeDoesActorHaveTag( GetHeroCharacterFromActorInfo() , WarriorGameplayTags::Player_Status_Rolling)
	&&  !UWFunctionLibrary::NativeDoesActorHaveTag(GetHeroCharacterFromActorInfo(), WarriorGameplayTags::Player_Status_Blocking);

	if (bShouldOverrideRotation)
	{
		const FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(GetHeroCharacterFromActorInfo()->GetActorLocation()
			, CurrentLockedActor->GetActorLocation());
		//更新player的旋转
		const FRotator CurrentControlRot = GetHeroControllerFromActorInfo()->GetControlRotation();
		const FRotator TargetRot = FMath::RInterpTo(CurrentControlRot , LookAtRot , DeltaTime , TargetLockRotationInterpSpeed);
		//GetHeroCharacterFromActorInfo()->SetActorRotation(LookAtRot);
		GetHeroControllerFromActorInfo()->SetControlRotation( FRotator(TargetRot.Pitch , TargetRot.Yaw , 0.f));
		GetHeroCharacterFromActorInfo()->SetActorRotation( FRotator(0.f, TargetRot.Yaw, 0.f) );
	}
}

void UHeroGameplayAbility_TargetLock::TryLockOnTarget()
{
	//调用获取有效对象进行锁定的方法
	GetAvailableActorsToLock();

	//判断获取的追踪对象是否为空
	if (AvailableActorsToLock.IsEmpty())
	{
		CancelTargetLockAbility();
		return;
	}

	//获取当前的锁定对象
	CurrentLockedActor = GetNearestTargetFromAvailableActors( AvailableActorsToLock );
	//检查当前最近锁定的对象是否有效
	if (CurrentLockedActor)
	{
		//调用绘制UI的方法
		DrawTargetLockWidget();
		SetTargetLockWidgetLocation();
		
		Debug::print( CurrentLockedActor->GetActorNameOrLabel() );
	}
	else
	{
		//取消目标锁定技能
		CancelTargetLockAbility();
	}
}

void UHeroGameplayAbility_TargetLock::CleanUp()
{
	//将锁定对象置空
	AvailableActorsToLock.Empty();
	//将当前对象置空
	CurrentLockedActor = nullptr;
	//将当前UI移除并置空
	if (DrawnTargetLockWidget)
	{
		DrawnTargetLockWidget->RemoveFromParent();
	}
	DrawnTargetLockWidget = nullptr;
	TargetLockWidgetSize = FVector2D::ZeroVector;
	CacehdDefaultMaxWalkSpeed = 0.f;
	
	
}

void UHeroGameplayAbility_TargetLock::GetAvailableActorsToLock()
{
	TArray<FHitResult> BoxTraceHits;

	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetHeroCharacterFromActorInfo(),
		GetHeroCharacterFromActorInfo()->GetActorLocation(),
		GetHeroCharacterFromActorInfo()->GetActorLocation() + GetHeroCharacterFromActorInfo()->GetActorForwardVector() * BoxTraceDistance,
		TraceBoxSize / 2.f,
		GetHeroCharacterFromActorInfo()->GetActorForwardVector().ToOrientationRotator(),
		BoxTraceChannel,
		false,
		TArray<AActor*>(),
		bShowPersistentDebugShape ? EDrawDebugTrace::Persistent : EDrawDebugTrace::None,
		BoxTraceHits,
		true
	);//合体追踪针对于多个对象

	//遍历追踪碰撞结果
	for (const FHitResult& TraceHit : BoxTraceHits )
	{
		//判断是否获取到对应的对象
		if (AActor* HitActor = TraceHit.GetActor())
		{
			//发生碰撞的对象不是Player本身
			if (HitActor != GetHeroCharacterFromActorInfo())
			{
				//发生碰撞的对象加入定义好的数组变量中
				AvailableActorsToLock.AddUnique(HitActor);
				//打印相应的调试信息
				/*Debug::print(HitActor->GetActorNameOrLabel() );*/
			}
		}
	}
}

AActor* UHeroGameplayAbility_TargetLock::GetNearestTargetFromAvailableActors(const TArray<AActor*>& InAvailableActors)
{
	float ClosestDistance = 0.f;
	/*return nullptr;*/
	return UGameplayStatics::FindNearestActor( GetHeroCharacterFromActorInfo()->GetActorLocation() , InAvailableActors , ClosestDistance );
}

void UHeroGameplayAbility_TargetLock::DrawTargetLockWidget()
{
	//UI赋值为空才创建
	if (!DrawnTargetLockWidget)
	{
		//检查UI类是否有效
		if (!TargetLockUIClass)
			return;
		//创建UI
		DrawnTargetLockWidget = CreateWidget<UWarriorWidgetBase>(GetHeroControllerFromActorInfo(), TargetLockUIClass);

		//判断UI是否有效
		if (!DrawnTargetLockWidget)
			return;

		//将UI添加到视口上
		DrawnTargetLockWidget->AddToViewport();
	}
	
}

void UHeroGameplayAbility_TargetLock::SetTargetLockWidgetLocation()
{
	//判断绘制的UI和获取的对象是否有效
	if (!DrawnTargetLockWidget || !CurrentLockedActor)
	{
		CancelTargetLockAbility();
		return;
	}
	//声明局部的屏幕坐标变量
	FVector2D ScreenPosition;
	//设置UI的位置
	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition( GetHeroControllerFromActorInfo(), CurrentLockedActor->GetActorLocation() , ScreenPosition ,true);

	//检查UI的尺寸是否为零
	if ( TargetLockWidgetSize == FVector2D::ZeroVector )
	{
		DrawnTargetLockWidget->WidgetTree->ForEachWidget(
			[this](UWidget* FoundWidget)
			{
				//检查sizeBox
				if (USizeBox* FoundSizeBox = Cast<USizeBox>(FoundWidget))
				{
					//获取UI的尺寸
					TargetLockWidgetSize.X = FoundSizeBox->GetWidthOverride();
					TargetLockWidgetSize.Y = FoundSizeBox->GetHeightOverride();
				}
			}
		);
	}

	ScreenPosition -= ( TargetLockWidgetSize / 2.f );
	
	DrawnTargetLockWidget->SetPositionInViewport(ScreenPosition,false);
}

void UHeroGameplayAbility_TargetLock::InitTargetLockMovement()
{
	//获取移动组件并得到最大移动速度
	CacehdDefaultMaxWalkSpeed = GetHeroCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed;
	//设置最大移动速度
	GetHeroCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = TargetLockMaxWalkSpeed;
}

void UHeroGameplayAbility_TargetLock::ResetTargetLockMovement()
{
	if (CacehdDefaultMaxWalkSpeed > 0.f)
	{
		GetHeroCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = CacehdDefaultMaxWalkSpeed;
	}
	
}

void UHeroGameplayAbility_TargetLock::CancelTargetLockAbility()
{
	//调用取消技能方法
	CancelAbility( GetCurrentAbilitySpecHandle() , GetCurrentActorInfo() , GetCurrentActivationInfo() , true );
}
