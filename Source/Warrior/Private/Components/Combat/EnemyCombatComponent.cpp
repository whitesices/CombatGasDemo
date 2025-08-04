// WSL All Rights Reserved


#include "Components/Combat/EnemyCombatComponent.h"
//引入能力系统蓝图头文件
#include "AbilitySystemBlueprintLibrary.h"
//引入管理gameplayTag的头文件
#include "WarriorGameplayTags.h"
//引入通用蓝图函数库
#include "WFunctionLibrary.h"
//引入自定义的敌人头文件
#include "Characters/WarriorEnemyCharacter.h"
#include "Components/BoxComponent.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	//若击中对象有效
	if (HitActor)
	{
		UE_LOG( LogTemp , Warning , TEXT("Hitactor is right %s "), *HitActor->GetActorNameOrLabel() );
	}

	//检查碰撞对象是否有效
	if (OverlappedActors.Contains(HitActor))
	{
		return;
	}
	//将碰撞收集到的actor存入数组中 父类碰撞离开清除了
	OverlappedActors.AddUnique( HitActor );

	//定义临时变量 检查碰撞
	bool bIsValidBlock = false;
	const bool bIsPlayerBlocking = UWFunctionLibrary::NativeDoesActorHaveTag( HitActor ,WarriorGameplayTags::Player_Status_Blocking );
	/*const bool bIsMyAttackUnblockable = false;*/
	const bool bIsMyAttackUnblockable = UWFunctionLibrary::NativeDoesActorHaveTag( GetOwningPawn() , WarriorGameplayTags::Enemy_Status_Unbloackable );

	if (bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		//检查碰撞是否有效
		bIsValidBlock = UWFunctionLibrary::IsValidBlock( GetOwningPawn() , HitActor );
	}

	//声明游戏事件数据的临时变量
	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;
	
	//判断碰撞是否有效
	if( bIsValidBlock)
	{
		//处理成功的技能阻挡
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			HitActor,
			WarriorGameplayTags::Player_Event_SuccessfullBlock,
			EventData
		);
	}
	else
	{
		//调用SendGameplayEventToActor 发送gameplaytag进行通信
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			GetOwningPawn(),
			WarriorGameplayTags::Shared_Event_MeleeHit,
			EventData
		);
	}

}

void UEnemyCombatComponent::ToggleBodyCollisionBoxCollision(bool bShouldEnbale, EToggleDamageType ToggleDamageType)
{
	AWarriorEnemyCharacter* OwningEnemyCharacter = GetOwningPawn<AWarriorEnemyCharacter>();//获取所属的Pawn
	check(OwningEnemyCharacter);//判断有效性
	UBoxComponent* LeftHandCollisionBox = OwningEnemyCharacter->GetLeftHandCollisionBox();
	UBoxComponent* RightHandCollisionBox = OwningEnemyCharacter->GetRightHandCollisionBox();

	//检查碰撞体的有效性
	check(LeftHandCollisionBox && RightHandCollisionBox);

	switch (ToggleDamageType)
	{
	case EToggleDamageType::LeftHand:
		LeftHandCollisionBox->SetCollisionEnabled( bShouldEnbale ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
	case EToggleDamageType::RightHand:
		RightHandCollisionBox->SetCollisionEnabled(bShouldEnbale ? ECollisionEnabled::QueryOnly : ECollisionEnabled::NoCollision);
		break;
	default:
		break;

	}

	//判断shouldenable
	if (!bShouldEnbale)
	{
		OverlappedActors.Empty();
	}
}
