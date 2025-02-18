// WSL All Rights Reserved


#include "Characters/WarriorEnemyCharacter.h"

#include "Components/Combat/EnemyCombatComponent.h"
//引入移动组件头文件
#include "GameFramework/CharacterMovementComponent.h"
//引入资产管理头文件
#include "Engine/AssetManager.h"
#include "DataAssets/StartupData/DataAsset_EnemyStartUpDataBase.h"
//引入UIComponent
#include "Components/UI/EnemyUIComponent.h"

#include "WarriorDebugHelper.h"


AWarriorEnemyCharacter::AWarriorEnemyCharacter()
{
	//定义相应的属性
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	//不受继承的控制
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//获取移动组件设置是否使用期望旋转
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	//是否限制朝向
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//设置旋转速率
	GetCharacterMovement()->RotationRate = FRotator(0.f, 180.f, 0.f);
	//设置最大移动速度
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	//设置制动减速
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

	//创建战斗组件
	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>(TEXT("EnemyCombatComponent"));

	//创建敌人UI组件
	EnemyUIComonent = CreateDefaultSubobject<UEnemyUIComponent>( TEXT("EnemyUIComponent"));
}

UPawnCombatComponent* AWarriorEnemyCharacter::GetPawnCombatComponent() const
{
	//返回EnemyCombat
	return EnemyCombatComponent;
}

UPawnUIComponent* AWarriorEnemyCharacter::GetPawnUIComponent() const
{
	return EnemyUIComonent;
}

void AWarriorEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	/*Debug::print( TEXT("Enemy is working") );*/
}

void AWarriorEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	

	InitEnemyStartUpData();
}

void AWarriorEnemyCharacter::InitEnemyStartUpData()
{
	//检查角色数据资产是否为空
	if ( CharcaterStartUpData.IsNull() )
	{
		return;
	}

	//异步加载资产
	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharcaterStartUpData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this]()
			{
				//判断数据资产是否加载
				if (UDataAsset_StartUpDataBase* LoadedData = CharcaterStartUpData.Get())
				{
					LoadedData->GiveToAbilitySystemComponent(WAbilitySystemComponent);
					/*Debug::print(TEXT("DataEnemiesAsset is loaded!"));*/
				}
			}
		)
	);
}
