// WSL All Rights Reserved


#include "Components/UI/EnemyUIComponent.h"
#include "Widgets/WarriorWidgetBase.h"//引入自定义的UI基类

void UEnemyUIComponent::RegisterEnemyDrawnWidget(UWarriorWidgetBase* InWidgetToRegister)
{
	InWidgetToRegister->SetVisibility(ESlateVisibility::SelfHitTestInvisible);//注册的UI设置可见
	EnemyDrawnWidgets.Emplace(InWidgetToRegister);//存储注册的UI
}

void UEnemyUIComponent::HiddenEnemyDrawnWidgetsIfAny()
{
	//判断是否已经有注册的UI
	if ( EnemyDrawnWidgets.Num() == 0)
	{
		return;
	}
	//遍历移除
	for ( UWarriorWidgetBase* DrawWidget : EnemyDrawnWidgets )
	{
		if (DrawWidget)
		{
			DrawWidget->SetVisibility(ESlateVisibility::Collapsed);//隐藏该UI 不使用销毁的方式避免频繁的创建销毁
		}
	}
	EnemyDrawnWidgets.Empty();//将存储的UI置空
}
