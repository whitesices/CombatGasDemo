// WSL All Rights Reserved


#include "AnimaInstances/WarriorBaseAnimInstance.h"
#include "GameplayTagContainer.h"
#include "WFunctionLibrary.h"

bool UWarriorBaseAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
    //声明Pawn的局部变量
    if (APawn* OwningPawn = TryGetPawnOwner())
    {
        //引入库函数检查
        return UWFunctionLibrary::NativeDoesActorHaveTag( OwningPawn , TagToCheck );
    }

    return false;
}
