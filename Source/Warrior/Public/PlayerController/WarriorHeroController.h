// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
//引入生成团队ID接口代理头文件
#include "GenericTeamAgentInterface.h"
#include "WarriorHeroController.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API AWarriorHeroController : public APlayerController,public IGenericTeamAgentInterface
{
	GENERATED_BODY()
public:
	AWarriorHeroController();

	//复写获取团队Id的函数
	//begin IGenericTeamAgentInterface
	virtual FGenericTeamId GetGenericTeamId() const override;
	//end IGenericTeamAgentInterface

private:
	//定义player的团队ID
	FGenericTeamId HeroTeamID;
	
};
