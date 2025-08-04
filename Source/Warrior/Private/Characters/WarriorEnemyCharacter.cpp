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
//引入WidgetComponent组件
#include "Components/WidgetComponent.h"
//引入自定义的WidgetBase头文件
#include "Widgets/WarriorWidgetBase.h"
//引入碰撞体组件头文件
#include "Components/BoxComponent.h"
//引入蓝图函数库
#include "WFunctionLibrary.h"

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
	//创建敌人健康UI组件
	EnemyHealthUIComponent = CreateDefaultSubobject<UWidgetComponent>( TEXT("EnemyHealthWidgetComponent") );
	//将健康组件添加的Mesh上
	EnemyHealthUIComponent->SetupAttachment( GetMesh() );

	//初始化左右手碰撞
	LeftHandCollisionBox = CreateDefaultSubobject<UBoxComponent>("LeftHandCollisionBox");
	LeftHandCollisionBox->SetupAttachment( GetMesh() );
	LeftHandCollisionBox->SetCollisionEnabled( ECollisionEnabled::NoCollision );
	LeftHandCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this , &AWarriorEnemyCharacter::OnBodyCollisionBoxBeginOverlap);

	RightHandCollsionBox = CreateDefaultSubobject<UBoxComponent>("RightHandCollisionBox");
	RightHandCollsionBox->SetupAttachment( GetMesh() );
	RightHandCollsionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightHandCollsionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &AWarriorEnemyCharacter::OnBodyCollisionBoxBeginOverlap);
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

UEnemyUIComponent* AWarriorEnemyCharacter::GetCurrentEnemyUIComponent() const
{
	return EnemyUIComonent;
}

void AWarriorEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	/*Debug::print( TEXT("Enemy is working") );*/

	//初始化HealthWidget组件,并判断其有效性
	if (UWarriorWidgetBase* EnemyHelathWidget = Cast<UWarriorWidgetBase>(EnemyHealthUIComponent->GetUserWidgetObject()))
	{
		//将Enemy本身传递进去
		EnemyHelathWidget->InitEnemyCreateWidget(this);
	}
}

void AWarriorEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	

	InitEnemyStartUpData();
}

#if WITH_EDITOR
void AWarriorEnemyCharacter::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	//判断获取的骨骼名称是否存在
	if ( PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass,LeftHandCollisionBoxAttachBoneName) )
	{
		LeftHandCollisionBox->AttachToComponent( GetMesh() , FAttachmentTransformRules::SnapToTargetIncludingScale , LeftHandCollisionBoxAttachBoneName );//将碰撞体添加到骨骼上
	}

	if ( PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass,RightHandCollisionBoxAttachBoneName) )
	{
		RightHandCollsionBox->AttachToComponent( GetMesh() , FAttachmentTransformRules::SnapToTargetIncludingScale, RightHandCollisionBoxAttachBoneName );
	}
}
#endif

void AWarriorEnemyCharacter::OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherCompIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//判断是否获取到Pawn
	if (APawn* HitPawn = Cast<APawn>(OtherActor) )
	{
		if (UWFunctionLibrary::IsTargetPawnHostile(this , HitPawn) )
		{
			EnemyCombatComponent->OnHitTargetActor(HitPawn);
		}
	}
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
