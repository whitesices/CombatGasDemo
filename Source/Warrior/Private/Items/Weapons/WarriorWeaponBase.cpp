// WSL All Rights Reserved


#include "Items/Weapons/WarriorWeaponBase.h"
#include "Components/BoxComponent.h"

//引入打印头文件
#include "WarriorDebugHelper.h"

// Sets default values
AWarriorWeaponBase::AWarriorWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//给武器网格体赋值
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);

	WeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));
	WeaponCollisionBox->SetupAttachment(GetRootComponent());
	WeaponCollisionBox->SetBoxExtent( FVector(20.f));
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//调用碰撞体的触发方法,通过委托的方式实现的绑定（观察者模式)
	WeaponCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic( this , &AWarriorWeaponBase::OnCollisionBoxBeginOverlap);
	//调用碰撞体的结束方法
	WeaponCollisionBox->OnComponentEndOverlap.AddUniqueDynamic( this , &AWarriorWeaponBase::OnCollisionBoxEndOverlap);
}

void AWarriorWeaponBase::OnCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//获取碰撞的对象,创建一个局部变量存储
	APawn* WeaponOwingPawn = GetInstigator<APawn>();
	//检查武器所有者是否有效
	checkf( WeaponOwingPawn , TEXT("Forgot to assign an instiagtor as the owning pawn for the weapon:%s"),*GetName() );

	//检查发生碰撞的otheractor是否有效
	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		//检查武器所有者是否是友军
		if (WeaponOwingPawn != HitPawn)
		{
			/*Debug::print(GetName() + TEXT(" Begin overlap with ") + HitPawn->GetName() , FColor::Green );*/

			//执行绑定的单播
			OnWeaponHitTarget.ExecuteIfBound(OtherActor);
		}

		//TODO:Implement Hit check for enemy characters

	}
}

void AWarriorWeaponBase::OnCollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//获取碰撞的对象，创建一个局部变量存储
	APawn* WeaponOwingPawn = GetInstigator<APawn>();

	checkf(WeaponOwingPawn, TEXT("Forgot to assign an instigator as the owning pawn for the weapon:%s"), *GetName());

	//检查发生碰撞的otherCharacter是否有效
	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		//检查武器所有者是否互为友军
		if (WeaponOwingPawn != HitPawn)
		{
			/*Debug::print( GetName() + TEXT(" End overlap with ") + HitPawn->GetName(), FColor::Red);*/

			//执行绑定的单播
			OnWeaponPulledFromTarget.ExecuteIfBound(OtherActor);
		}

		//TODO:Implement Hit check for enemy characters
	}
}



