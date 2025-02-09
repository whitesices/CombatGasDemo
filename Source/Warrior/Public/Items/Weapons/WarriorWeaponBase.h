// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WarriorWeaponBase.generated.h"

class UBoxComponent;

//声明一个单播委托
DECLARE_DELEGATE_OneParam( FOnTargetInteractedDelegate , AActor*);

UCLASS()
class WARRIOR_API AWarriorWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWarriorWeaponBase();

	//声明一个代理
	//触发到目标
	FOnTargetInteractedDelegate OnWeaponHitTarget;
	//离开目标
	FOnTargetInteractedDelegate OnWeaponPulledFromTarget;

protected:

	//声明创建静态网格体变量
	UPROPERTY( VisibleAnywhere , BlueprintReadOnly , Category = "Weapons")
	UStaticMeshComponent* WeaponMesh;

	//声明创建BoxComponent
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	UBoxComponent* WeaponCollisionBox;

	//定义创建绑定的函数方法
	UFUNCTION()
	virtual void OnCollisionBoxBeginOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult );

	//定义创建结束的方法
	UFUNCTION()
	virtual void OnCollisionBoxEndOverlap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	FORCEINLINE UBoxComponent* GetWeaponCollisionBox() const { return WeaponCollisionBox; }

};
