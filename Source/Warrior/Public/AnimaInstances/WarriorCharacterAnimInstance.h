// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AnimaInstances/WarriorBaseAnimInstance.h"
#include "WarriorCharacterAnimInstance.generated.h"

class AWarriorBaseCharacter;
class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorCharacterAnimInstance : public UWarriorBaseAnimInstance
{
	GENERATED_BODY()

public:
	//重载动画初始化函数
	virtual void NativeInitializeAnimation() override;
	//在工作线程上运行,不占用主线程
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	//引入角色类变量
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly,Category="Character")
	AWarriorBaseCharacter* OwningCharacter;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Character")
	UCharacterMovementComponent* OwningCharacterMovement;

	//自定义的float变量存储速度
	UPROPERTY(VisibleDefaultsOnly , BlueprintReadOnly,Category="AnimData|Locomotion")
	float GroundSpeed;
	
	//获取加速度
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly,Category="AnimData|Locomation")
	bool bHasAcceleration;
};
