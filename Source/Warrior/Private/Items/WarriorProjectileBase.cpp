// WSL All Rights Reserved


#include "Items/WarriorProjectileBase.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

//引入蓝图函数库头文件
#include "WFunctionLibrary.h"
//引入调试辅助文件
#include "WarriorDebugHelper.h"
#include "WarriorGameplayTags.h"

AWarriorProjectileBase::AWarriorProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;

	ProjectileCollsionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ProjectileCollsionBox"));
	SetRootComponent(ProjectileCollsionBox);//设置根组件
	ProjectileCollsionBox->SetCollisionEnabled( ECollisionEnabled::QueryOnly);//设置碰撞类型
	ProjectileCollsionBox->SetCollisionResponseToChannel( ECC_Pawn , ECR_Block );
	ProjectileCollsionBox->SetCollisionResponseToChannel( ECC_WorldDynamic , ECR_Block );
	ProjectileCollsionBox->SetCollisionResponseToChannel( ECC_WorldStatic , ECR_Block );
	ProjectileCollsionBox->OnComponentHit.AddUniqueDynamic(this , &AWarriorProjectileBase::OnProjectileHit);//多播绑定
	ProjectileCollsionBox->OnComponentBeginOverlap.AddDynamic(this, &AWarriorProjectileBase::OnProjectileBeginOverlap);//发生重叠的多播绑定事件

	ProjectileNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileNiagara"));
	ProjectileNiagaraComponent->SetupAttachment( GetRootComponent() );

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComponent->InitialSpeed = 700.f;
	ProjectileMovementComponent->MaxSpeed = 900.f;
	ProjectileMovementComponent->Velocity = FVector( 1.f , 0.f , 0.f );
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;

	//初始化存在时间
	InitialLifeSpan = 4.f;
}

void AWarriorProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	if ( ProjectileDamagePolicy == EProjectilDamagePolicy::OnBeginOverlap )
	{
		ProjectileCollsionBox->SetCollisionResponseToChannel( ECC_Pawn , ECR_Overlap );
	}
	
}

void AWarriorProjectileBase::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//判断OtherActor是否有效
	/*if (OtherActor)
	{
		Debug::print( OtherActor->GetActorNameOrLabel() );
		Destroy();
	}*/
	//调用蓝图可实现函数
	BP_OnSpawnProjectileHitFX(Hit.ImpactPoint);

	//判断发生碰撞的是否是Pawn
	APawn* HitPawn = Cast<APawn>(OtherActor);

	if (!HitPawn || !UWFunctionLibrary::IsTargetPawnHostile( GetInstigator() , HitPawn) )
	{
		Destroy();
		return;
	}
	bool bIsValidBlock = false;
	const bool bIsPlayerBlocking = UWFunctionLibrary::NativeDoesActorHaveTag( HitPawn , WarriorGameplayTags::Player_Status_Blocking);//检查是否Blocking

	if (bIsPlayerBlocking)
	{
		bIsValidBlock = UWFunctionLibrary::IsValidBlock( this , HitPawn );
	}

	//声明GameplayEventData
	FGameplayEventData Data;
	Data.Instigator = this;
	Data.Target = HitPawn;
	if (bIsValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			HitPawn,
			WarriorGameplayTags::Player_Event_SuccessfullBlock,
			Data
		);
	}
	else
	{
		//Apply projectile damage

	}

	//最终销毁
	Destroy();
}

void AWarriorProjectileBase::OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}



