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
//引入生成团队ID接口代理头文件
#include "GenericTeamAgentInterface.h"
//引入数学库函数头文件
#include "Kismet/KismetMathLibrary.h"
//引入GameplayTag头文件
#include "WarriorGameplayTags.h"
#include "WarriorDebugHelper.h"

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

bool UWFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	//检查检索的Pawn与目标的Pawn
	check( QueryPawn && TargetPawn );
	IGenericTeamAgentInterface*  QueryTeamAgent = Cast<IGenericTeamAgentInterface>( QueryPawn->GetController() );
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if (QueryTeamAgent && TargetTeamAgent)
	{
		return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}

	return false;
}

float UWFunctionLibrary::GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel)
{
	return InScalableFloat.GetValueAtLevel( InLevel );
}

FGameplayTag UWFunctionLibrary::ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference)
{
	//判断攻击者和受攻击者是否有效
	check( InAttacker && InVictim );

	//朝向
	const FVector VictimForward = InVictim->GetActorForwardVector();
	//攻击者朝向的归一化
	const FVector VictimToAttackerNormalized = ( InAttacker->GetActorLocation() - InVictim->GetActorLocation() ).GetSafeNormal();

	const float DotResult = FVector::DotProduct( VictimForward , VictimToAttackerNormalized );

	//得到弧值
	OutAngleDifference = UKismetMathLibrary::DegAcos(DotResult);
	//获取两个向量插积结果
	const FVector CrossResult = FVector::CrossProduct( VictimForward , VictimToAttackerNormalized );

	//判断角度的正负
	if (CrossResult.Z < 0.f)
	{
		OutAngleDifference *= -1.f;
	}

	//通过夹角判断返回的Tag标签
	if (OutAngleDifference >= -45.f && OutAngleDifference <=45.f)
	{
		return WarriorGameplayTags::Shared_Status_HitReact_Front;
	}
	else if (OutAngleDifference >= -135.f && OutAngleDifference < -45.f)
	{
		return WarriorGameplayTags::Shared_Status_HitReact_Left;
	}
	else if (OutAngleDifference >45.f && OutAngleDifference <=135.f)
	{
		return WarriorGameplayTags::Shared_Status_HitReact_Right;
	}
	else if(OutAngleDifference < -135.f || OutAngleDifference > 135.f )
	{
		return WarriorGameplayTags::Shared_Status_HitReact_Back;
	}

	return WarriorGameplayTags::Shared_Status_HitReact_Front;
}

bool UWFunctionLibrary::IsValidBlock(AActor* InAttacker, AActor* InDefender)
{
	check(InAttacker && InDefender);
	const float DotResult = FVector::DotProduct( InAttacker->GetActorForwardVector() , InDefender->GetActorForwardVector() );

	//const FString DebugString = FString::Printf( TEXT("Dot Result: %f %s "),DotResult , DotResult < -0.1f ? TEXT("Valid Block") : TEXT("Not Valid"));
	////打印调试信息
	//Debug::print( DebugString , DotResult < -0.1f ? FColor::Green : FColor::Red );
	//返回bool值
	return DotResult<-0.1f;
}

bool UWFunctionLibrary::ApplyGameplayEffectSpecHandleToTarget(AActor* InInstigator, AActor* InTargetActor, const FGameplayEffectSpecHandle InEffectHandle)
{
	//Instigator
	UWarriorAbilitySystemComponent* SourceASC = NativeGetWarriorASCFromActor(InInstigator);
	//TargetActor
	UWarriorAbilitySystemComponent* TargetASC = NativeGetWarriorASCFromActor(InTargetActor);

	//应用GameplayEffect到目标对象上
	FActiveGameplayEffectHandle  ActiveEffecHandle = SourceASC->ApplyGameplayEffectSpecToTarget(*InEffectHandle.Data ,  TargetASC);

	return ActiveEffecHandle.WasSuccessfullyApplied();
}

