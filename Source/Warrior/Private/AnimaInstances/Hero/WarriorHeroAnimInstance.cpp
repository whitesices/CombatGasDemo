// WSL All Rights Reserved


#include "AnimaInstances/Hero/WarriorHeroAnimInstance.h"
//引入角色类基类的头文件
#include "Characters/WarriorHeroCharacter.h"

void UWarriorHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	//判断所属对象是否有效
	if (OwningCharacter)
	{
		OwningHeroCharacter = Cast<AWarriorHeroCharacter>(OwningCharacter);
	}

}

void UWarriorHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	//检查加速度是否有效
	if (bHasAcceleration)
	{
		IdleElpasedTime = 0.f;
		bShouldEnterRelaxState = false;
	}
	else
	{
		IdleElpasedTime += DeltaSeconds;
		//判断是否进入放松状态
		bShouldEnterRelaxState = (IdleElpasedTime >= EnterRelaxStateThreshold);
	}

}
