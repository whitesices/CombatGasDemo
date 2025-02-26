// WSL All Rights Reserved


#include "AI/BTService_OrientToTargetActor.h"
//#include "BTService_OrientToTargetActor.h"
//引入BB组件头文件
#include "BehaviorTree/BlackboardComponent.h"
//引入AIController的头文件
#include "AIController.h"
//引入工具蓝图函数库
#include "Kismet/KismetMathLibrary.h"

UBTService_OrientToTargetActor::UBTService_OrientToTargetActor()
{
	//修改NodeName
	NodeName = TEXT("Native Orient Rotation Tpo Target Actor");

	//通知给本地服务器
	INIT_SERVICE_NODE_NOTIFY_FLAGS();

	//初始化目标值
	RotationInterpSpeed = 5.f;
	Interval = 0.f;
	RandomDeviation = 0.f;

	//初始化目标值
	InTargetActorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, InTargetActorKey), AActor::StaticClass());
}

void UBTService_OrientToTargetActor::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	//获取BB数据
	if (UBlackboardData* BBAsset = GetBlackboardAsset())
	{
		InTargetActorKey.ResolveSelectedKey( *BBAsset );
	}
}

FString UBTService_OrientToTargetActor::GetStaticDescription() const
{
	Super::GetStaticDescription();
	const FString KeyDescription = InTargetActorKey.SelectedKeyName.ToString();

	return FString::Printf( TEXT("Orient rotation to %s key %s"),*KeyDescription , *GetStaticServiceDescription() );

}

void UBTService_OrientToTargetActor::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	//获取黑板组件
	UObject* ActorObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject( InTargetActorKey.SelectedKeyName );
	//获取目标对象
	AActor* TargetActor = Cast<AActor>(ActorObject);

	APawn* OwningPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (OwningPawn && TargetActor)
	{
		const FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation( OwningPawn->GetActorLocation() , TargetActor->GetActorLocation() );
		const FRotator TargetRot = FMath::RInterpTo( OwningPawn->GetActorRotation() , LookAtRot, DeltaSeconds , RotationInterpSpeed );

		OwningPawn->SetActorRotation(TargetRot);
	}
}
