// WSL All Rights Reserved


#include "AnimaInstances/WarriorCharacterAnimInstance.h"
//引入角色类基类的头文件
#include "Characters/WarriorBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UWarriorCharacterAnimInstance::NativeInitializeAnimation()
{
	//获取角色变量
	OwningCharacter = Cast<AWarriorBaseCharacter>(TryGetPawnOwner());
	//判断OwningCharacter的有效性
	if (OwningCharacter)
	{
		OwningCharacterMovement = OwningCharacter->GetCharacterMovement();
	}
}

void UWarriorCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	//移动组件和角色的有效性
	if (!OwningCharacter || !OwningCharacterMovement)
	{
		return;
	}

	//获取速度
	GroundSpeed=OwningCharacter->GetVelocity().Size2D();
	//获取加速度是否大于零
	bHasAcceleration = OwningCharacterMovement->GetCurrentAcceleration().SizeSquared2D() > 0.f;
}
