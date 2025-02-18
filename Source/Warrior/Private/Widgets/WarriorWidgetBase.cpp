// WSL All Rights Reserved


#include "Widgets/WarriorWidgetBase.h"

//引入PawnUI的接口头文件
#include "Interfaces/PawnUIInterface.h"
//引入HeroUIComponent的组件头文件

void UWarriorWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	//声明一个局部变量的接口，并判断有效性
	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn())) 
	{
		if (UHeroUIComponent* HeroUIComponent = PawnUIInterface->GetCurrentHeroUIComponent())
		{

		}
	};
}
