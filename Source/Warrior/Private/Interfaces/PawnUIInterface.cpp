// WSL All Rights Reserved


#include "Interfaces/PawnUIInterface.h"
//引入HeroUI的头文件
#include "Components/UI/HeroUIComponent.h"
//引入EnemyUI的头文件
#include "Components/UI/EnemyUIComponent.h"

// Add default functionality here for any IPawnUIInterface functions that are not pure virtual.

UHeroUIComponent* IPawnUIInterface::GetCurrentHeroUIComponent() const
{
    return nullptr;
}

UEnemyUIComponent* IPawnUIInterface::GetCurrentEnemyUIComponent() const
{
    return nullptr;
}
