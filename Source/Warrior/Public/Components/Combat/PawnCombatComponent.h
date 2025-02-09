// WSL All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnExtensionComponentBase.h"
//引入Gameplaytagcontainertou头文件
#include "GameplayTagContainer.h"
#include "PawnCombatComponent.generated.h"

//struct FGameplayTag;
class AWarriorWeaponBase;

//创建一个枚举类型
UENUM( BlueprintType )
enum class EToggleDamageType : uint8
{
	CurrentEquippedWeapon,
	LeftHand,
	RightHand
};
/**
 * 
 */
UCLASS()
class WARRIOR_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
	UFUNCTION( BlueprintCallable , Category = "Warrior|Combat")
	void RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister, AWarriorWeaponBase* InWeaponToRegister , bool bResgisterAsEquippedWeapon = false);

	UFUNCTION( BlueprintCallable , Category = "Warrior|Combat")
	AWarriorWeaponBase* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	UPROPERTY( BlueprintReadWrite , Category = "Warrior|Combat" )
	FGameplayTag CurrentEquippedWeaponTag;

	UFUNCTION( BlueprintCallable , Category = "Warrior|Combat")
	AWarriorWeaponBase* GetCharacterCurrentEquippedWeapon() const;

	//声明一个新的触发武器碰撞的方法
	UFUNCTION( BlueprintCallable , Category = "Warrior|Combat")
	void ToggleWeaponCollision( bool bShouldEnable , EToggleDamageType ToggleDamageType = EToggleDamageType::CurrentEquippedWeapon );

	//创建碰撞体单播绑定触发后的回调函数
	virtual void OnHitTargetActor( AActor* HitActor);

	virtual void OnWeaponPulledFromTargetActor(AActor* InteractedActor);

protected:

	//声明一个数组来存储发生碰撞的Actor
	TArray<AActor*> OverlappedActors;


private:
	TMap<FGameplayTag, AWarriorWeaponBase*> CharacterCarriedWeaponMap;
};
