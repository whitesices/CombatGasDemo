// WSL All Rights Reserved


#include "Characters/WarriorHeroCharacter.h"
//添加帮助文件
#include "WarriorDebugHelper.h"
//引入弹簧臂组件头文件
#include "GameFramework/SpringArmComponent.h"
//引入碰撞胶囊体
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
//引入移动组件
#include "GameFramework/CharacterMovementComponent.h"
#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "EnhancedInputSubsystems.h"
#include "Components/Input/WarriorInputComponent.h"
//引入GamePlayTag
#include "WarriorGameplayTags.h"
//引入自定义的AbilitySystemComponent
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
//引入自定义的AttributeSet
#include "AbilitySystem/WarriorAttributeSet.h"
#include "DataAssets/StartupData/DataAsset_HeroStartUpData.h"
//引入战斗系统组件
#include "Components/Combat/HeroCombatComponent.h"

#include "InputActionValue.h"

AWarriorHeroCharacter::AWarriorHeroCharacter()
{
	//获取碰撞胶囊体
	GetCapsuleComponent()->InitCapsuleSize( 42.f , 96.f);

	//将P，Y， R设置为false
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//给CameraBoom赋值
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	//添加到根组件上
	CameraBoom->SetupAttachment( GetRootComponent() );
	//设置臂长
	CameraBoom->TargetArmLength = 200.f;
	//设置相机的偏向
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	//设置控制角色控制旋转
	CameraBoom->bUsePawnControlRotation = true;

	//给FllowCamera赋值
	FllowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FllowCamera"));
	//将跟随相机添加到弹簧臂上
	FllowCamera->SetupAttachment( CameraBoom , USpringArmComponent::SocketName);
	//设置控制相机旋转为false
	FllowCamera->bUsePawnControlRotation = false;

	//设置角色移动组件,朝向跟随移动
	GetCharacterMovement()->bOrientRotationToMovement = true;
	//设置旋转速率
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	//设置最大移动速度
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	//设置制动减速
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	//创建初始化战斗系统组件
	HeroCombatComponent = CreateDefaultSubobject<UHeroCombatComponent>(TEXT("HeroCombat"));
}

void AWarriorHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//判断abilitySystemComponent与AttributeSet是否有效
	/*if (WAbilitySystemComponent && WAttributeSet)
	{
		const FString ASCText = FString::Printf( TEXT("Owner Actor:%s , AvatarActor:%s"),*WAbilitySystemComponent->GetOwnerActor()->GetActorLabel(), *WAbilitySystemComponent->GetAvatarActor()->GetActorLabel() );

		Debug::print( TEXT("Ability system component valid.") + ASCText ,FColor::Green);
		Debug::print(TEXT("AttributeSet valid.") + ASCText, FColor::Green);
	}*/

	//检查角色数据资产是否为空
	if (!CharcaterStartUpData.IsNull())
	{
		//加载相应的数据资产,并判断数据资产是否有效
		if (UDataAsset_StartUpDataBase* LoadedData = CharcaterStartUpData.LoadSynchronous())
		{
			//启用相应的GameplayAbility
			LoadedData->GiveToAbilitySystemComponent(WAbilitySystemComponent);
		}
	}

}

void AWarriorHeroCharacter::BeginPlay()
{
	Super::BeginPlay();

	//测试打印消息
	/*Debug::print(TEXT("Working"));*/
}

void AWarriorHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//检查数据资产的有效性
	checkf( InputConfigDataAsset , TEXT("Forgot to assign a valid data asset as input config"));

	//获取本地玩家对象
	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	//获取增强输入子系统
	UEnhancedInputLocalPlayerSubsystem* EnhancedSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	//断言检查有效性
	check(EnhancedSubsystem);
	//配置IMC
	EnhancedSubsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext,0);
	//设置InputComponent
	UWarriorInputComponent* WInputComponent = CastChecked<UWarriorInputComponent>(PlayerInputComponent);
	WInputComponent->BindNativeInputAction(InputConfigDataAsset,WarriorGameplayTags::InputTag_Move,ETriggerEvent::Triggered,this, &AWarriorHeroCharacter::W_Move);
	WInputComponent->BindNativeInputAction(InputConfigDataAsset, WarriorGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &AWarriorHeroCharacter::W_Look);

}

void AWarriorHeroCharacter::W_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	//检查移动组件的值是否为零来判断是否移动
	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardDirection , MovementVector.Y);
	}

	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AWarriorHeroCharacter::W_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}

	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
