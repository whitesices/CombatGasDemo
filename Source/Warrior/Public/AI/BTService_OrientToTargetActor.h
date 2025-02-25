// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_OrientToTargetActor.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API UBTService_OrientToTargetActor : public UBTService_BlackboardBase
{
	GENERATED_BODY()

//public:
	//新增一个构造函数
	UBTService_OrientToTargetActor();

	//重写初始化BTNode节点的函数
	//~Begin UBTNode Interface
	virtual void InitializeFromAsset( UBehaviorTree& Asset) override;
	virtual FString GetStaticDescription() const override;
	//~end UBTNode INterface
	//重写TickNode逻辑
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;



	//新增一个BB的目标对象键值
	UPROPERTY( EditAnywhere , Category = "Target")
	FBlackboardKeySelector InTargetActorKey;
	
	UPROPERTY( EditAnywhere , Category = "Target")
	float RotationInterpSpeed;
};
