// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PawnUIInterface.generated.h"

//引入PawnUI的前置声明
class UPawnUIComponent;
class UHeroUIComponent;
class UEnemyUIComponent;
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPawnUIInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WARRIOR_API IPawnUIInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	//声明获取PawnUI的接口函数
	virtual UPawnUIComponent* GetPawnUIComponent() const = 0;

	//声明获取heroUI的接口函数
	virtual UHeroUIComponent* GetCurrentHeroUIComponent() const ;

	//声明创建获取EnemyUI的接口函数
	virtual UEnemyUIComponent* GetCurrentEnemyUIComponent() const;

};
