// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WarriorWidgetBase.generated.h"

//引入HeroUI组件
class UHeroUIComponent;
class UEnemyUIComponent;

/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorWidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	//重载初始化函数
	virtual void NativeOnInitialized() override;
	
	//创建在蓝图调用实现的C++方法
	UFUNCTION( BlueprintImplementableEvent , meta = ( DisplayName = "On Owning Hero UI Component Initialized"))
	void BP_OnOwningHeroUIComponentInitialized( UHeroUIComponent* OwningHeroUIComponent );

	//创建在蓝图中实现的C++ 方法
	UFUNCTION( BlueprintImplementableEvent , meta = (DisplayName = "On Owning Enemy UI Component Initialized"))
	void BP_OnOwningEnemyUIComponentInitialized(UEnemyUIComponent* OwningEnemyUIComponent);

public:
	//创建供蓝图函数可调用的初始化敌人UI的方法
	UFUNCTION( BlueprintCallable )
	void InitEnemyCreateWidget(AActor* OwningEnemyActor );
};
