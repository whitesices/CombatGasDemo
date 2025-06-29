// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"

#include "WarriorProjectileBase.generated.h"

//前置声明引入
class UBoxComponent;
class UNiagaraComponent;
class UProjectileMovementComponent;
//struct FGameplayEffectSpecHandle;

//声明一个枚举类型来区别伤害类型
UENUM( BlueprintType )
enum class EProjectilDamagePolicy : uint8
{
	OnHit,
	OnBeginOverlap
};

UCLASS()
class WARRIOR_API AWarriorProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AWarriorProjectileBase();

protected:
	virtual void BeginPlay() override;

protected:
	//声明碰撞盒子属性变量
	UPROPERTY( VisibleDefaultsOnly , BlueprintReadOnly , Category = "Projectile" )
	UBoxComponent* ProjectileCollsionBox;
	//声明创建Niagara组件属性变量
	UPROPERTY( VisibleDefaultsOnly , BlueprintReadOnly , Category = "Projectile")
	UNiagaraComponent* ProjectileNiagaraComponent;
	//声明创建投射系统组件
	UPROPERTY( VisibleDefaultsOnly , BlueprintReadOnly , Category = "Projectile")
	UProjectileMovementComponent* ProjectileMovementComponent;

	//声明伤害类型
	UPROPERTY( EditDefaultsOnly , BlueprintReadOnly , Category = "Projectile" )
	EProjectilDamagePolicy ProjectileDamagePolicy = EProjectilDamagePolicy::OnHit;//默认设置碰撞

	//声明GameplayEffect
	UPROPERTY(BlueprintReadOnly, Category = "Projectile", meta = (ExposeOnSpawn = "true"))
	FGameplayEffectSpecHandle ProjectileDamageEffectSpecHandle;

	UFUNCTION()
	virtual void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
	virtual void OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//蓝图可实现的函数
	UFUNCTION( BlueprintImplementableEvent , meta = (DisplayName = "OnSpawnProjectileHitFX"))
	void BP_OnSpawnProjectileHitFX( const FVector& HitLocation);

private:
	//建立一个私有函数处理引用GameplayEffect的数据处理
	void HandleApplyProjectileDamage(APawn* InHitPawn);
};
