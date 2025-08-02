// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/PawnUIComponent.h"
#include "EnemyUIComponent.generated.h"

class UWarriorWidgetBase;

/**
 * 
 */
UCLASS()
class WARRIOR_API UEnemyUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()

public:
	//记录创建BossBarUI
	UFUNCTION(BlueprintCallable , Category="EnemyUI")
	void RegisterEnemyDrawnWidget( UWarriorWidgetBase* InWidgetToRegister );

	//创建隐藏UI的可供蓝图调用的方法
	UFUNCTION(BlueprintCallable , Category="EnemyUI")
	void HiddenEnemyDrawnWidgetsIfAny();

private:
	//声明一个变量存储注册的UI
	TArray<UWarriorWidgetBase*> EnemyDrawnWidgets;
};
