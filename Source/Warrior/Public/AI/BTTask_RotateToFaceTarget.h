// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_RotateToFaceTarget.generated.h"

//声明一个结构体保存相应数据
struct FRotateToFaceTargetTaskMemory
{
	TWeakObjectPtr<APawn> OwningPawn;
	TWeakObjectPtr<AActor> TargetActor;

};

/**
 * 
 */
UCLASS()
class WARRIOR_API UBTTask_RotateToFaceTarget : public UBTTaskNode
{
	GENERATED_BODY()
public:

	UBTTask_RotateToFaceTarget();
	//声明新建的类
	UPROPERTY( EditAnywhere , Category = "FaceTarget" )
	float AnglePrecision;
	//声明旋转速度插值
	UPROPERTY( EditAnywhere , Category = "FaceTarget" )
	float RotationInterpSpeed;

	UPROPERTY(EditAnywhere , Category = "FaceTarget")
	FBlackboardKeySelector InTargetToFaceKey;
	
	//~Begin BTNode Inetrface
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	//~end BTNode Interface
};
