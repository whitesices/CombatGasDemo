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

	//定义一个方法获取是否有效
	bool IsValid() const
	{
		return OwningPawn.IsValid() && TargetActor.IsValid();
	}

	//设置重置
	void Reset()
	{
		OwningPawn.Reset();
		TargetActor.Reset();
	}

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
	virtual uint16 GetInstanceMemorySize() const override;
	virtual FString GetStaticDescription() const override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	//~end BTNode Interface

	//定义判断是否抵达相应的角度的方法
	bool HasReachedAnglePercision(APawn* QueryPAwn, AActor* TargetActor) const;
};
