// WSL All Rights Reserved


#include "AnimaInstances/Hero/WarriorHeroLinkedAnimLayer.h"
//引入角色动画接口
#include "AnimaInstances/Hero/WarriorHeroAnimInstance.h"
//引入角色类基类的头文件
#include "Characters/WarriorHeroCharacter.h"

UWarriorHeroAnimInstance* UWarriorHeroLinkedAnimLayer::GetHeroAnimInstance() const
{
	return Cast<UWarriorHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
