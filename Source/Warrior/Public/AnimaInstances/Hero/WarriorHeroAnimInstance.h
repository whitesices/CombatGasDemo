// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "AnimaInstances/WarriorCharacterAnimInstance.h"
#include "WarriorHeroAnimInstance.generated.h"


class AWarriorHeroCharacter;
/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorHeroAnimInstance : public UWarriorCharacterAnimInstance
{
	GENERATED_BODY()

public:
	//重载动画初始化函数
	virtual void NativeInitializeAnimation() override;
	//在工作线程上运行,不占用主线程
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	//引入角色类变量
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Character")
	AWarriorHeroCharacter* OwningHeroCharacter;

	/*UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Character")
	UCharacterMovementComponent* OwningCharacterMovement;*/

	//自定义是否应该放松的变量
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|Locomotion")
	bool bShouldEnterRelaxState;

	//进入放松的时间
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AnimData|Locomotion")
	float EnterRelaxStateThreshold = 5.f;
	
	//记录闲逛的时间
	float IdleElpasedTime;
};
