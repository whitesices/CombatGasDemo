// WSL All Rights Reserved


#include "Characters/WarriorBaseCharacter.h"
//引入自定义的AbilitySystemComponent
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
//引入自定义的AttributeSet
#include "AbilitySystem/WarriorAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "DataAssets/StartupData/DataAsset_StartUpDataBase.h"

// Sets default values
AWarriorBaseCharacter::AWarriorBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	//设置Body不获取贴花
	GetMesh()->bReceivesDecals = false;

	//添加AbilitySsytemComponent
	WAbilitySystemComponent = CreateDefaultSubobject<UWarriorAbilitySystemComponent>(TEXT("WarriorAbilitySystemComponent"));
	//添加属性集合
	WAttributeSet = CreateDefaultSubobject<UWarriorAttributeSet>(TEXT("WarriorAttributeSet"));
}

UAbilitySystemComponent* AWarriorBaseCharacter::GetAbilitySystemComponent() const
{
	return GetWarriorAbilitySystemComponent();
}

void AWarriorBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//判断技能系统组件的有效性
	if (WAbilitySystemComponent)
	{
		WAbilitySystemComponent->InitAbilityActorInfo(this , this);

		//判断启动数据的有效性
		//ensure(!CharcaterStartUpData.IsNull());
		ensureMsgf(!CharcaterStartUpData.IsNull() , TEXT("Forgot to assign start up data to %s "), *GetName() );

		/*if (ensure(!CharcaterStartUpData.IsNull()))
		{

		}*/
	}
}


