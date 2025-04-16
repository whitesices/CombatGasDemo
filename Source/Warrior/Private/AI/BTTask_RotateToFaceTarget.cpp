// WSL All Rights Reserved


#include "AI/BTTask_RotateToFaceTarget.h"
//引入BalckBorad的头文件
#include "BehaviorTree/BlackboardComponent.h"
//引入AIController
#include "AIController.h"
//引入数学头文件
#include "Kismet/KismetMathLibrary.h"

UBTTask_RotateToFaceTarget::UBTTask_RotateToFaceTarget()
{
	NodeName = TEXT("NativeRotateToFaceTargetActor");
	AnglePrecision = 10.f;
	RotationInterpSpeed = 5.f;

	//Tick为true
	bNotifyTick = true;
	bNotifyTaskFinished = true;
	bCreateNodeInstance = false;

	//添加Task的初始化逻辑
	INIT_TASK_NODE_NOTIFY_FLAGS();
	InTargetToFaceKey.AddObjectFilter( this , GET_MEMBER_NAME_CHECKED(ThisClass,InTargetToFaceKey) , AActor::StaticClass() );
}

void UBTTask_RotateToFaceTarget::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	//获取黑暗资源判断是否有效
	if (UBlackboardData* BBAsset = GetBlackboardAsset())
	{
		InTargetToFaceKey.ResolveSelectedKey(*BBAsset);
	}
}

uint16 UBTTask_RotateToFaceTarget::GetInstanceMemorySize() const
{
	return sizeof(FRotateToFaceTargetTaskMemory);
}

FString UBTTask_RotateToFaceTarget::GetStaticDescription() const
{
	//获取键名
	const FString KeyDescription = InTargetToFaceKey.SelectedKeyName.ToString();

	//声明相应的信息并最终返回
	FString str = FString::Printf(TEXT("Smoothly rotates to face %s Key until the angle precision: %s is reached"), *KeyDescription , *FString::SanitizeFloat(AnglePrecision) );

	return str;
}

EBTNodeResult::Type UBTTask_RotateToFaceTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Super::ExecuteTask(OwnerComp,NodeMemory);
	//获取黑板数据,声明一个临时变量进行存储
	UObject* ActorObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(InTargetToFaceKey.SelectedKeyName);
	//获取目标对象
	AActor* TargetActor = Cast<AActor>(ActorObject);
	APawn* OwningPawn = OwnerComp.GetAIOwner()->GetPawn();
	//获取内存获取的数据
	FRotateToFaceTargetTaskMemory* memory = CastInstanceNodeMemory<FRotateToFaceTargetTaskMemory>(NodeMemory);
	//检查获取的数据是否有效
	check(memory);
	//传递相应的值
	memory->OwningPawn = OwningPawn;
	memory->TargetActor = TargetActor;

	if (!memory->IsValid())
	{
		return EBTNodeResult::Failed;
	}

	if (HasReachedAnglePercision( OwningPawn ,TargetActor) )
	{
		memory->Reset();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::InProgress;
}

void UBTTask_RotateToFaceTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	//获取内存获取的数据
	FRotateToFaceTargetTaskMemory* memory = CastInstanceNodeMemory<FRotateToFaceTargetTaskMemory>(NodeMemory);
	//判断memory的有效性
	if (!memory->IsValid())
	{
		//完成任务返回失败
		FinishLatentTask( OwnerComp , EBTNodeResult::Failed );
	}

	if (HasReachedAnglePercision( memory->OwningPawn.Get(),memory->TargetActor.Get() ) )
	{
		//完成任务返回成功
		memory->Reset();
		FinishLatentTask(OwnerComp,EBTNodeResult::Succeeded);
	}
	else
	{
		//设置朝向目标
		const FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation( memory->OwningPawn->GetActorLocation() , memory->TargetActor->GetActorLocation() );
		const FRotator TargetRot = FMath::RInterpTo( memory->OwningPawn->GetActorRotation() , LookAtRot, DeltaSeconds , RotationInterpSpeed);
		//设置角色自己的旋转变量
		memory->OwningPawn->SetActorRotation(TargetRot);
	}
}

bool UBTTask_RotateToFaceTarget::HasReachedAnglePercision(APawn* QueryPAwn, AActor* TargetActor) const
{
	const FVector OwnerForward = QueryPAwn->GetActorLocation();
	//归一化处理得到相应的距离
	const FVector OwnerToTargetNormalized = ( TargetActor->GetActorLocation() - QueryPAwn->GetActorLocation() ).GetSafeNormal() ;
	//向量乘积得到角度
	const float DotResult = FVector::DotProduct( OwnerForward , OwnerToTargetNormalized );
	//将角度转化为度数
	const float AngleDiff = UKismetMathLibrary::DegAcos( DotResult );
	//返回相应判断是否在对应精度值内
	return AngleDiff <= AnglePrecision ;
}
