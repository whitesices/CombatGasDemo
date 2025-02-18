// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Characters/WarriorBaseCharacter.h"
#include "WarriorEnemyCharacter.generated.h"

//引入敌人Combat
class UEnemyCombatComponent;
//引入敌人UI
class UEnemyUIComponent;

/**
 * 
 */
UCLASS()
class WARRIOR_API AWarriorEnemyCharacter : public AWarriorBaseCharacter
{
	GENERATED_BODY()

public:
	//定义构造函数
	AWarriorEnemyCharacter();

	//重写GetPawnCombatComponent ~ Begin IPawnCombatInterface 
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	//end IPawnCombatInterface

	//重写GetPawnUIComponent ~Begin IPawnUIInterface
	virtual UPawnUIComponent* GetPawnUIComponent() const override;
	//end IPawnUIInterface

protected:
	//重写begin Play函数
	virtual void BeginPlay() override;

	//重写PossessdBy函数
	//~Begin APawn Interface
	virtual void PossessedBy(AController* NewController) override;
	//~End APawn Inetrface

private:
#pragma region Componenets

	//声明敌人战斗组件
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Combat" , meta = (AllowPrivateAccess="true") )
	UEnemyCombatComponent* EnemyCombatComponent;

	//声明敌人UI组件
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "UI" , meta = ( AllowPrivateAccess="true") )
	UEnemyUIComponent* EnemyUIComonent;
#pragma endregion

public:
	//内联函数获取comBatComponent 
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const
	{
		return EnemyCombatComponent;
	}

	//内联函数获取UIComponent
	FORCEINLINE UEnemyUIComponent* GetEnemyUIComponent() const
	{
		return EnemyUIComonent;
	}
	
private:
	//声明初始化敌人初始资产的私有方法
	void InitEnemyStartUpData();
};
