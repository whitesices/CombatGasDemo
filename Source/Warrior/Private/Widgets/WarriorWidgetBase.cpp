// WSL All Rights Reserved


#include "Widgets/WarriorWidgetBase.h"

//引入PawnUI的接口头文件
#include "Interfaces/PawnUIInterface.h"
//引入HeroUIComponent的组件头文件
#include "Components/UI/HeroUIComponent.h"
//引入EnemyUIComponent的组件头文件
#include "Components/UI/EnemyUIComponent.h"

void UWarriorWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	//声明一个局部变量的接口，并判断有效性
	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn())) 
	{
		if (UHeroUIComponent* HeroUIComponent = PawnUIInterface->GetCurrentHeroUIComponent())
		{
			BP_OnOwningHeroUIComponentInitialized(HeroUIComponent);
		}
	};
}


void UWarriorWidgetBase::InitEnemyCreateWidget(AActor* OwningEnemyActor)
{
	//声明一个局部变量的接口，并判断有效性
	if ( IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>( OwningEnemyActor ) )
	{
		UEnemyUIComponent* EnemyUIComponent = PawnUIInterface->GetCurrentEnemyUIComponent();
		
		//检查EnemyUICompoent的有效性
		checkf( EnemyUIComponent , TEXT("Failed to xtrac an EnemyUIComponent from %s"), *OwningEnemyActor->GetActorNameOrLabel() );

		BP_OnOwningEnemyUIComponentInitialized(EnemyUIComponent);
		
	}

}


