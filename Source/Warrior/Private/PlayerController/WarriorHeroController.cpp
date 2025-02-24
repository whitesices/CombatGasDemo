// WSL All Rights Reserved


#include "PlayerController/WarriorHeroController.h"

AWarriorHeroController::AWarriorHeroController()
{
	//设置player的ID值
	HeroTeamID = FGenericTeamId(0);
}

FGenericTeamId AWarriorHeroController::GetGenericTeamId() const
{
	return HeroTeamID;
}
